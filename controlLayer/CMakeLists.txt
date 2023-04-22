add_library(libController
    controller.hpp
    controller.cpp
)
target_link_libraries(libController
    fssimplewindow
    libTexture
    libBase
    libMario
    libMap)
target_include_directories(libController PUBLIC .)

add_executable(controlmain MACOSX_BUNDLE main.cpp)
target_link_libraries(controlmain
    fssimplewindow
    libTexture
    libBase
    libMario
    libMap
    libController)