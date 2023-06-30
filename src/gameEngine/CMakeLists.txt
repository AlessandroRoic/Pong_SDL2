add_library(gameEngine "")

target_sources(gameEngine
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/GameEngine.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/GameEngine.hpp
        )
target_include_directories(gameEngine
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
