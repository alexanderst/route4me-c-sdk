
ADD_EXECUTABLE(GetVehicles GetVehicles.c)
TARGET_LINK_LIBRARIES(GetVehicles route4me)

ADD_EXECUTABLE(RouteStatus RouteStatus.c)
TARGET_LINK_LIBRARIES(RouteStatus route4me)

ADD_EXECUTABLE(GetRoutes GetRoutes.c)
TARGET_LINK_LIBRARIES(GetRoutes route4me)

ADD_EXECUTABLE(GetRouteById GetRouteById.c)
TARGET_LINK_LIBRARIES(GetRouteById route4me)

ADD_EXECUTABLE(GetRouteByPath GetRouteByPath.c)
TARGET_LINK_LIBRARIES(GetRouteByPath route4me)

ADD_EXECUTABLE(GetRouteDirections GetRouteDirections.c)
TARGET_LINK_LIBRARIES(GetRouteDirections route4me)

ADD_EXECUTABLE(GetRouteQuery GetRouteQuery.c)
TARGET_LINK_LIBRARIES(GetRouteQuery route4me)

ADD_EXECUTABLE(UpdateRoute UpdateRoute.c)
TARGET_LINK_LIBRARIES(UpdateRoute route4me)

ADD_EXECUTABLE(DuplicateRoute DuplicateRoute.c)
TARGET_LINK_LIBRARIES(DuplicateRoute route4me)

ADD_EXECUTABLE(ShareRoute ShareRoute.c)
TARGET_LINK_LIBRARIES(ShareRoute route4me)

