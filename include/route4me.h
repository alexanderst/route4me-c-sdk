
#ifndef croute4me route4me
#define croute4me route4me

#include <json.h>

void init(char*, int);

void cleanUp();

struct response_data
{
    char* m_raw_resp;    
    json_object* m_json_resp;
    char* m_err_msg;
    int m_err_code;
};

struct response_data getCurrentResponse();

/*Vehicles functionality */
int get_vehicles(int offset, int limit);

#endif
