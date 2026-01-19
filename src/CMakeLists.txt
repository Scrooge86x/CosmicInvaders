add_executable(game main.cpp)
add_executable(demo demo.cpp)
set_target_properties(demo PROPERTIES EXCLUDE_FROM_ALL TRUE)

add_subdirectory(core)
add_subdirectory(renderer)
add_subdirectory(gameplay)
add_subdirectory(ui)
add_subdirectory(ecs)

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
        gameplay
        renderer
        ui
        ecs
        glad
        glfw
)
target_link_libraries(demo
    PRIVATE
        core
        renderer
        ui
        ecs
        glad
        glfw
        glm
)

function(copy_assets_for_target target)
    add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:${target}>/assets
    )
endfunction()

copy_assets_for_target(game)
copy_assets_for_target(demo)

install(
    TARGETS game
    RUNTIME DESTINATION .
)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/assets
    DESTINATION .
)

set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION .)
include(InstallRequiredSystemLibraries)
