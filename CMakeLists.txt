cmake_minimum_required(VERSION 3.16)
project(spaceshooter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(spaceshooter src/main.cpp
                            src/Game.cpp
                            src/
                            src/Entity.cpp 
                            src/EntityManager.cpp
                            src/imgui.cpp 
                            src/imgui_widgets.cpp 
                            src/imgui_tables.cpp 
                            src/imgui_draw.cpp 
                            src/imgui_demo.cpp 
                            src/imgui-SFML.cpp
                            src/Vec2.cpp 

                            )
target_link_libraries(spaceshooter PRIVATE sfml-graphics)
target_compile_features(spaceshooter PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET spaceshooter
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:spaceshooter>
        VERBATIM)
endif()

