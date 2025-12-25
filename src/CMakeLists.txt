add_executable(game main.cpp)
add_executable(demo demo.cpp)

add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(game)
add_subdirectory(ui)

if (MSVC)
    set(COMPILER_FLAGS /W4)
else ()
    set(COMPILER_FLAGS -Wall -Wextra -Wpedantic)
endif ()

target_compile_options(game PRIVATE ${COMPILER_FLAGS})
target_compile_options(demo PRIVATE ${COMPILER_FLAGS})

target_link_libraries(demo PRIVATE
    glfw
    glad
    glm
    miniaudio
    imgui
    stb_image
    assimp
    nlohmann_json
)

add_custom_target(copy_demo_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:demo>/assets
)
add_dependencies(demo copy_demo_assets)

add_custom_target(copy_game_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game>/assets
)
add_dependencies(game copy_game_assets)
