
#ifndef croute4me
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

struct MapPoint
{
    double lat;
    double lng;
};

struct response_data getCurrentResponse();
int getErrorCode();
char* getErrorMessage();
char* getRawResponse();
json_object* getJSONResponse();

/* Routes functionality */

/** \brief Get single route
 * \param offset
 * \param limit
 * \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_q(int offset, int limit);

/** \brief Gets a status update on all
* optimization problems for a specific API key.
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_multiple_routes();

/** \brief Gets a Route by ID.
* \param route_id route ID
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_by_id(const char *route_id);

/** \brief Gets info about a Route.
* \param props api call parameters
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route(json_object* props);

/** \brief Gets routes by path points
* \param route id
* \param route_path_output
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_path_points(const char* route_id, const char* route_path_output);

/** \brief Gets routes by directions
* \param route id
* \param directions - 1 or 0
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_directions(const char* route_id, int directions);

/** \brief Gets routes by query
* \param route id
* \param query - text pattern
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_query(const char* route_id, const char* query);

/** \brief Add address to specific route
* \param route id
* \param address as JSON object
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int add_route_destinations(const char*, json_object*);

/** \brief Remove address from system
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int remove_address_from_route(const char* route_id, const char* destination_id);

/** \brief Update route with JSON data
* \param route id
* \param destination id
* \param JSON object
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int update_route(const char* route_id, const char* dest_id, char* data);

/** \brief Clone the route
* \param route id
* \param to - redirect to page or return JSON for "none"
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int duplicate_route(const char* route_id, const char* to);

/** \brief Delete a Route by ID.
* \param route_id route ID
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int delete_route(const char *route_id);

/** \brief Merge routes
* \param route_ids - comma separated list of routes
* \param depot_address
* \param point - lattitide and longtitude of depot
* \param remove_origin
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int merge_routes(const char* route_ids, const char* depot_address, struct MapPoint point, int remove_origin);

/** \brief Share route
* \param route_id route ID
* \param email - send route data there
* \param format
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int share_routes(const char* route_id, const char* email, const char* format);

/** \brief Returns route destination details.
* \param route_id
* \param destination id
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_address(const char* route_id, const char* destination_id);

/** \brief Add route notes
* \param route_id
* \param destination id
* \param text notes
* \param point on map
* \param device type
* \param JSON data to be added
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int add_route_notes(const char *route_id, const char *destination_id, const char *notes, const char* device_type,
                    const struct MapPoint* point, const char *data);

/** \brief Get route notes
* \param route_id
* \param destination id
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_route_notes(const char* route_id, const char* destination_id);

/** \brief Set GPS point.
* \param props api call parameters
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int set_gps(json_object* props);

/** \brief Reoptimize the problem.
* \param opt_id optimization problem ID
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int reoptimize(const char *opt_id);

/** \brief Returns optimization problem.
* \param optimization problem id
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_optimization(const char* optimization_problem_id);

/** \brief Returns optimization problem.
* \param states list of addresses for the optimization problem
* \param offset
* \param limit
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int get_optimizations(const char* states, int offset, int limit);

/** \brief Removes optimization problem.
* \param fields
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int remove_optimization(const char* fields);

/** \brief Removes address from optimization problem.
* \param address - id of the address
* \param opt_id - id of the problem
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int remove_address_from_optimization(const char* address, const char* opt_id);

/** \brief Adds address to optimization problem.
 * * \param opt_id - id of the problem
* \param body - address data in JSON format
* \param reoptimize
* \return \c 0 if the response was successfully received, \c error code if an error occurred.
*/
int add_address_to_optimization(const char* body, const char* opt_id, int reoptimize);

/*Vehicles functionality */
int get_vehicles(int offset, int limit);

int deserialize(const char*, char**);

#endif

