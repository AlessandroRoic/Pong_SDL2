find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

file(COPY ${CMAKE_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(engine)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE engine)
