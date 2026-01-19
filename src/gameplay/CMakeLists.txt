add_library(gameplay STATIC
    game.cpp game.h
    levels.h
)

target_link_libraries(gameplay
    PUBLIC
        core
        renderer
        EnTT::EnTT
    PRIVATE
        ui
        ecs
)

target_include_directories(gameplay PUBLIC ${PROJECT_SOURCE_DIR}/src)
