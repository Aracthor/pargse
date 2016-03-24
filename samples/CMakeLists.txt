project("pargse")

add_executable(client client.c)
target_link_libraries(client pargse)

add_executable(grids grids.c)
target_link_libraries(grids pargse)
