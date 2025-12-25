add_library(core STATIC
    gl-window.cpp gl-window.h
    fps-counter.cpp fps-counter.h
    input-manager.cpp input-manager.h
    model-store.cpp model-store.h
    settings.cpp settings.h
    audio-engine.cpp audio-engine.h
)

target_link_libraries(core PUBLIC
    renderer

    glad
    glfw
    glm
    miniaudio
    nlohmann_json
)
