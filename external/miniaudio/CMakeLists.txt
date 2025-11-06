add_library(miniaudio STATIC miniaudio.cpp)
target_include_directories(miniaudio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
