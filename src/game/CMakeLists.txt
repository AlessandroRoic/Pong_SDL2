add_library(game "")

target_link_libraries(game PRIVATE SDL2::SDL2 SDL2_image::SDL2_image engine)

target_sources(game
        PRIVATE
        Player.cpp
        GameState.cpp
        Net.cpp
        Ball.cpp
        PlayerScore.cpp
        PUBLIC
        Player.hpp
        GameState.hpp
        Net.hpp
        Ball.hpp
        PlayerScore.hpp
        )

target_include_directories(game PUBLIC ${CMAKE_CURRENT_LIST_DIR})
