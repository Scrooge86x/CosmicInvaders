add_library(gameplay STATIC
    game.cpp game.h
)

target_link_libraries(gameplay
    PUBLIC
        core
        renderer
    PRIVATE
        ui
)

target_include_directories(gameplay PUBLIC ${PROJECT_SOURCE_DIR}/src)
