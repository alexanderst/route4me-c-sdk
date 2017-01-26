
#include <json.h>
#include <curl/curl.h>
#include "../include/route4me.h"

enum ReqType {
    REQ_GET,
    REQ_POST,
    REQ_PUT,
    REQ_DELETE
};

enum
{
    ERR_HTTP = -1,
    ERR_PARAM = -2,
    ERR_SYNTAX = -3,
    ERR_PARAM_TP = -4,
    ERR_CURL = -5,
    ERR_CURL_RESP = -6,
    ERR_CURL_EMPTY = -7,
    ERR_JSON = -8,
    ERR_API = -9,

    OPTIMIZATION_STATE_INITIAL = 1,
    OPTIMIZATION_STATE_MATRIX_PROCESSING = 2,
    OPTIMIZATION_STATE_OPTIMIZING = 3,
    OPTIMIZATION_STATE_OPTIMIZED = 4,
    OPTIMIZATION_STATE_ERROR = 5,
    OPTIMIZATION_STATE_COMPUTING_DIRECTIONS = 6,

    ROUTE4ME_METRIC_EUCLIDEAN = 1,
    ROUTE4ME_METRIC_MANHATTAN = 2,
    ROUTE4ME_METRIC_GEODESIC = 3,
    ROUTE4ME_METRIC_MATRIX = 4,
    ROUTE4ME_METRIC_EXACT_2D = 5,

    TSP = 1,
    VRP = 2,
    CVRP_TW_SD = 3,
    CVRP_TW_MD = 4,
    TSP_TW = 5,
    TSP_TW_CR = 6,
    BBCVRP = 7
};

struct http_resp
{
    char *memory;
    size_t size;
};

static char szEmptyResponse[] = "empty http response";
static char szParseError[] = "json parse error(s)\n";
static char szAPIError[] = "route4me api errors:";

static struct response_data current_response = {0};

struct response_data getCurrentResponse()
{
    return current_response;
}

//TODO: Fix segfault
static void setCurrentResponse(int error_code, char* error_message, int error_strlen)
{
    current_response.m_err_code = error_code;
    current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(error_strlen) + 1);
    strcpy(current_response.m_err_msg, error_message);
}

static void cleanCurrentResponse()
{
    if (current_response.m_err_msg != NULL)
    {
        free(current_response.m_err_msg);
    }
    memset(&current_response, 0, sizeof(struct response_data));
}

static char VEHICLES_SERVICE[] = "https://www.route4me.com/api/vehicles/view_vehicles.php";
static char api_key[100];
static void* curl;
static int verbose;

void init(char* szKey, int nVerbose)
{
    strcpy(api_key, szKey);
    verbose = nVerbose;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

void cleanUp()
{
    if (curl)
        curl_easy_cleanup(curl);
    curl_global_cleanup();
    cleanCurrentResponse();
}

static void make_arg(void *curl, char *url, json_object* params)
{
        int first = 1;
        json_object_object_foreach(params, key, val)
        {
            if (first) {
                strcat(url, "?");
                first = 0;
            }
            else
                strcat(url, "&");
            strcat(url, key);
            strcat(url,"=");
            strcat(url, json_object_to_json_string(val));
        }
}

static size_t read_http_resp(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct http_resp *mem = (struct http_resp *)userp;
    mem->memory = (char*) realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) return 0;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

static int request(enum ReqType method, void *curl, const char *url, json_object *props, json_object* body)
{
    long http_code = 0L;
    struct http_resp chunk;
    chunk.memory = (char*) malloc(1);
    chunk.size = 0;
    make_arg(curl, url, props);
    curl_easy_reset(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_http_resp);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    if (verbose)
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    /*if(!content.isNull())
        payload = Json::FastWriter().write(content);*/
    switch(method)
    {
        case REQ_GET:
            break;
        case REQ_DELETE:
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
            break;
        case REQ_PUT:
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            //curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, payload.c_str());
            break;
        case REQ_POST:

            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            /*curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, payload.c_str());
            if (formpost) {
                struct curl_slist *headerlist=NULL;
                static const char buf[] = "Content-Type: multipart/form-data;";
                headerlist = curl_slist_append(headerlist, buf);
                curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headerlist);
                curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, formpost);
            }*/
            break;
    }
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK)
    {
        free(chunk.memory);
        current_response.m_err_code = ERR_CURL_RESP;        
        current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(curl_easy_strerror(res)));
        strcpy(current_response.m_err_msg, curl_easy_strerror(res));
        return ERR_CURL_RESP;
    }
    if(method == REQ_PUT)
    {
        // if server responds with HTTP 303, we should use GET and CURLOPT_FOLLOWLOCATION does not help
        char *redirect_url = 0;
        if(curl_easy_getinfo(curl, CURLINFO_REDIRECT_URL, &redirect_url) == CURLE_OK && redirect_url)
        {
            free(chunk.memory);
            chunk.memory = (char*) malloc(1);
            chunk.size = 0;
            curl_easy_setopt(curl, CURLOPT_URL, redirect_url);
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, NULL);
            CURLcode res = curl_easy_perform(curl);
            if(res != CURLE_OK)
            {
                free(chunk.memory);
                current_response.m_err_code = ERR_CURL_RESP;
                current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(curl_easy_strerror(res)));
                strcpy(current_response.m_err_msg, curl_easy_strerror(res));
                //setCurrentResponse(ERR_CURL_RESP, curl_easy_strerror(res), strlen(curl_easy_strerror(res)));
                return ERR_CURL_RESP;
            }
        }
    }
    if(chunk.size == 0)
    {
        free(chunk.memory);
        current_response.m_err_code = ERR_CURL_EMPTY;
        current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(szEmptyResponse));
        strcpy(current_response.m_err_msg, szEmptyResponse);
        //setCurrentResponse(ERR_CURL_EMPTY, szEmptyResponse, strlen(szEmptyResponse));
        return ERR_CURL_EMPTY;
    }
    current_response.m_raw_resp = realloc(current_response.m_raw_resp, chunk.size+1);
    strcpy(current_response.m_raw_resp, chunk.memory);
    current_response.m_raw_resp[chunk.size] = '\0';
    free(chunk.memory);

    current_response.m_json_resp = json_tokener_parse(current_response.m_raw_resp);
    if(!strcmp(current_response.m_raw_resp, json_object_get_string(current_response.m_json_resp)))
    {
        current_response.m_json_resp = NULL;

        //TODO: Extract error details from JSON-C
        current_response.m_err_code = ERR_JSON;
        current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(szParseError)+1);
        strcpy(current_response.m_err_msg, szParseError);
        //setCurrentResponse(ERR_JSON, szParseError, strlen(szParseError));
        return ERR_JSON;
    }
    char error[100] = "";
    int has_error = 0;

    json_object_object_foreach(current_response.m_json_resp, key, val)
    {
        if (!strcmp(key, "errors"))
        {
            strcpy(error, json_object_to_json_string(val));
            has_error = 1;
            break;
        }
    }
    if (has_error)
    {        
        current_response.m_err_code = ERR_API;
        current_response.m_err_msg = realloc(current_response.m_err_msg, strlen(szAPIError) + strlen(error) + 1);
        strcpy(current_response.m_err_msg, szAPIError);
        strcat(current_response.m_err_msg, error);
        //setCurrentResponse(ERR_API, szAPIError, strlen(szAPIError));
        return ERR_API;
    }
    return CURLE_OK;
}

int get_vehicles(int offset, int limit)
{
    /*TODO: According to RFC-2616 length of URI is not limited.
            This number should be revised.
     */
    char url[2048];
    json_object* props = json_object_new_object();
    json_object_object_add(props, "api_key", json_object_new_string(api_key));
    json_object_object_add(props, "offset", json_object_new_int(offset));
    json_object_object_add(props, "limit", json_object_new_int(limit));

    strcpy(url, VEHICLES_SERVICE);
    return request(REQ_GET, curl, url, props, NULL);
}



