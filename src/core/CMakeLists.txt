add_library(core STATIC
    gl-window.cpp gl-window.h
    fps-counter.cpp fps-counter.h
    input-manager.cpp input-manager.h
    settings.cpp settings.h
    audio-engine.cpp audio-engine.h
    timer.cpp timer.h
)

target_link_libraries(core
    PUBLIC
        miniaudio
    PRIVATE
        glad
        glfw
        glm
        nlohmann_json
)

target_include_directories(core PUBLIC ${PROJECT_SOURCE_DIR}/src)
