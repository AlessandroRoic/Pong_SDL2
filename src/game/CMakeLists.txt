add_library(game "")

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)

target_sources(game
        PUBLIC
        Player.cpp
        GameState.cpp
        Net.cpp
        Ball.cpp
        PlayerScore.cpp
        Engine.cpp
        DeltaTimer.cpp
        KeyboardManager.cpp
        Timer.cpp
        )

install(TARGETS game DESTINATION game)
