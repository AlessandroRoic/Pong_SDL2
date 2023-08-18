cmake_minimum_required(VERSION 3.23)
project(PingPong_SDL2)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

install(TARGETS PingPong_SDL2 DESTINATION .)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Pong_SDL2")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_GENERATOR "ZIP")
include(CPack)
