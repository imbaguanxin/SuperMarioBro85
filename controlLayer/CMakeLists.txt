add_library(libController
    controller.hpp
    controller.cpp
)
target_link_libraries(libController fssimplewindow libTexture libBase libMap)
target_include_directories(libController PUBLIC .)

add_executable(controlmain main.cpp)
target_link_libraries(controlmain libController)