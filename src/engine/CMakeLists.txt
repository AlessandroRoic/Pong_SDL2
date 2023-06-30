add_library(engine "")

target_link_libraries(engine PRIVATE SDL2::SDL2)
target_link_libraries(engine PRIVATE SDL2_image::SDL2_image)
target_link_libraries(engine PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(engine PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(engine PRIVATE fmt::fmt)

target_sources(engine
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/Engine.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Engine.hpp
        )
target_include_directories(engine
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        )
