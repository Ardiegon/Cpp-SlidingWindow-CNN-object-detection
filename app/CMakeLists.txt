

add_executable(cppcv main.cpp)

target_link_libraries(cppcv PUBLIC point)
target_link_libraries(cppcv PUBLIC obdet)
target_link_libraries(cppcv PRIVATE ${OpenCV_LIBS})