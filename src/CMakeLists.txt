set(SRC_LIST main.cc)
add_executable(hello_lib ${SRC_LIST})
target_link_libraries(hello_lib config++)