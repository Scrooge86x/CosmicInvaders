add_executable(game main.cpp)
add_executable(demo demo.cpp)
set_target_properties(demo PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(gameplay)
add_subdirectory(ui)

if (MSVC)
    set(COMPILER_FLAGS /W4)
else ()
    set(COMPILER_FLAGS -Wall -Wextra -Wpedantic)
endif ()

target_compile_options(game PRIVATE ${COMPILER_FLAGS})
target_compile_options(demo PRIVATE ${COMPILER_FLAGS})

target_link_libraries(game
    PRIVATE
        core
        renderer
        ui
        glad
        glfw
)
target_link_libraries(demo
    PRIVATE
        core
        renderer
        ui
        glad
        glfw
        glm
)

add_custom_target(copy_game_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game>/assets
)
add_dependencies(game copy_game_assets)

add_custom_target(copy_demo_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:demo>/assets
)
add_dependencies(demo copy_demo_assets)
