add_library(libMario
    mario.hpp
    mario.cpp
)
target_link_libraries(libMario libBase)
target_include_directories(libMario PUBLIC .)