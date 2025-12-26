add_library(ui STATIC
    ui-core.cpp ui-core.h
)

target_link_libraries(ui
    PUBLIC
        imgui
    PRIVATE
        glfw
        glad
)

target_include_directories(ui PUBLIC ${PROJECT_SOURCE_DIR}/src)
