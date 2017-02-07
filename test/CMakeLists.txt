
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

ADD_EXECUTABLE(GetAddress GetAddress.c)
TARGET_LINK_LIBRARIES(GetAddress route4me)

ADD_EXECUTABLE(AddRouteNotes AddRouteNotes.c)
TARGET_LINK_LIBRARIES(AddRouteNotes route4me)

ADD_EXECUTABLE(GetRouteNotes GetRouteNotes.c)
TARGET_LINK_LIBRARIES(GetRouteNotes route4me)

ADD_EXECUTABLE(SetGps SetGps.c)
TARGET_LINK_LIBRARIES(SetGps route4me)

ADD_EXECUTABLE(Reoptimization Reoptimization.c)
TARGET_LINK_LIBRARIES(Reoptimization route4me)

ADD_EXECUTABLE(GetOptimization GetOptimization.c)
TARGET_LINK_LIBRARIES(GetOptimization route4me)

ADD_EXECUTABLE(GetOptimizations GetOptimizations.c)
TARGET_LINK_LIBRARIES(GetOptimizations route4me)

ADD_EXECUTABLE(RemoveOptimization RemoveOptimization.c)
TARGET_LINK_LIBRARIES(RemoveOptimization route4me)

ADD_EXECUTABLE(AddAddressToOptimization AddAddressToOptimization.c)
TARGET_LINK_LIBRARIES(AddAddressToOptimization route4me)

ADD_EXECUTABLE(GetAllActivities GetAllActivities.c)
TARGET_LINK_LIBRARIES(GetAllActivities route4me)

ADD_EXECUTABLE(LogActivity LogActivity.c)
TARGET_LINK_LIBRARIES(LogActivity route4me)

ADD_EXECUTABLE(GetTeamActivities GetTeamActivities.c)
TARGET_LINK_LIBRARIES(GetTeamActivities route4me)

ADD_EXECUTABLE(GetActivityByType GetActivityByType.c)
TARGET_LINK_LIBRARIES(GetActivityByType route4me)







