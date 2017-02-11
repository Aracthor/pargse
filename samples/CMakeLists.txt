project("pargse")

add_executable(client_c client.c)
target_link_libraries(client_c pargse)

add_executable(client_cpp client.cpp)
target_link_libraries(client_cpp pargse)

add_executable(grids grids.c)
target_link_libraries(grids pargse)
