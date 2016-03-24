project("pargse")

add_executable(client client.c)
target_link_libraries(client pargse)

add_executable(grid grid.c)
target_link_libraries(grid pargse)
