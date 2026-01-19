add_library(renderer STATIC
    shader.cpp shader.h
    texture2d.cpp texture2d.h
    mesh.cpp mesh.h
    model.cpp model.h
    camera.cpp camera.h
    model-store.cpp model-store.h
    renderer.cpp renderer.h
    material.h
    lighting.h
    gl-call.h
)

target_link_libraries(renderer
    PUBLIC
        glad
        glm
    PRIVATE
        stb_image
        assimp
)

target_include_directories(renderer PUBLIC ${PROJECT_SOURCE_DIR}/src)
