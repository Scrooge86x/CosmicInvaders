add_library(ui STATIC
    ui-core.cpp ui-core.h
    main-menu.cpp main-menu.h
    pause-menu.cpp pause-menu.h
    hud.cpp hud.h
    game-over-screen.cpp game-over-screen.h
    victory-screen.cpp victory-screen.h
    settings-menu.cpp settings-menu.h
)

target_link_libraries(ui
    PUBLIC
        imgui
    PRIVATE
        ecs
        gameplay
        glfw
        glad
)

target_include_directories(ui PUBLIC ${PROJECT_SOURCE_DIR}/src)
