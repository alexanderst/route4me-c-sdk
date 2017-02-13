
#include <stdio.h>
#include <json.h>
#include "../include/route4me.h"

static char key[] = "11111111111111111111111111111111";

int main(int argc, char* argv[])
{
    init(key, 1);
    const char file_name[] = "addr.json";
    char* data = NULL;

    if (!deserialize(file_name, &data))
    {
        printf("File addr.json is not found!\n");
        return -1;
    }

    json_object* params = json_object_new_object();
    json_object_object_add(params, "route_name", json_object_new_string("Single Driver Round Trip"));
    json_object_object_add(params, "algorithm_type", json_object_new_int(TSP));
    json_object_object_add(params, "remote_ip", json_object_new_int(0));
    json_object_object_add(params, "member_id", json_object_new_int(1));
    json_object_object_add(params, "route_time", json_object_new_int(0));
    json_object_object_add(params, "route_max_duration", json_object_new_int(86400));
    json_object_object_add(params, "optimize", json_object_new_string("Distance"));
    json_object_object_add(params, "distance_unit", json_object_new_string("mi"));
    json_object_object_add(params, "travel_mode", json_object_new_string("Driving"));
    json_object_object_add(params, "store_route", json_object_new_int(1));
    json_object_object_add(params, "device_type", json_object_new_string("web"));
    json_object_object_add(params, "vehicle_capacity", json_object_new_int(1));
    json_object_object_add(params, "vehicle_max_distance_mi", json_object_new_int(10000));
    json_object_object_add(params, "directions", json_object_new_int(1));        

    if (!run_optimization(data, json_object_to_json_string(params)))
    {
       json_object* opt_lst = getJSONResponse();
       printf("%s\n", json_object_to_json_string(opt_lst));
    }

    struct response_data response = getCurrentResponse();
    printf("Return code: %d\n Response: %s\n", response.m_err_code, response.m_raw_resp);

    cleanUp();
	return 0;
}

