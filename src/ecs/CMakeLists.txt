add_library(ecs STATIC 
    entities.cpp entities.h 
    components.h 
    systems.cpp systems.h 
)

target_link_libraries(ecs
    PUBLIC
        EnTT::EnTT
        glm
    PRIVATE 
        renderer
)

target_include_directories(ecs PUBLIC ${PROJECT_SOURCE_DIR}/src)
