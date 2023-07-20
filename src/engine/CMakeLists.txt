add_library(engine "")

target_link_libraries(engine
        PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
        fmt::fmt
        game
        )

target_sources(engine
        PRIVATE
        Engine.cpp
        DeltaTimer.cpp
        KeyboardManager.cpp
        Timer.cpp
        PUBLIC
        Engine.hpp
        DeltaTimer.hpp
        KeyboardManager.hpp
        Timer.hpp
        )

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_LIST_DIR})
