cmake_minimum_required(VERSION 3.10)
project(PhysicsSim)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_executable(${PROJECT_NAME} 
               src/Main.cpp
               src/AlignedAlloc.h
               src/Camera.h
               src/Clipping.cpp
               src/Clipping.h
               src/Framebuffer.cpp
               src/Framebuffer.h
               src/Light.h
               src/Matrix.h
               src/Model.cpp
               src/Model.h
               src/Renderer.cpp
               src/Renderer.h
               src/Scene.h
               src/Shader.h
               src/Texture.cpp
               src/Texture.h
               src/Triangle.h
               src/Utilities.h
               src/Vector.h
               src/Window.cpp
               src/Window.h)

find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_MAIN_LIBRARY SDL2main)
find_path(SDL2_HEADER_DIR SDL.h PATH_SUFFIXES SDL2)

find_library(SDL2_IMG_LIBRARY SDL2_image)
find_path(SDL2_IMG_HEADER_DIR SDL_image.h PATH_SUFFIXES SDL2)

target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY} ${SDL2_MAIN_LIBRARY} ${SDL2_IMG_LIBRARY})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_IMG_HEADER_DIR} ${SDL2_HEADER_DIR})

if (WIN32)
    find_file(SDL2_DLL SDL2.dll)
    find_file(SDL2_IMG_DLL SDL2_image.dll)
    # SDL_Image dependencies
    find_file(ZLIB_DLL zlib1.dll)
    find_file(PNG_DLL libpng16-16.dll)

    # copy dll files to exe directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                       ${SDL2_DLL} ${SDL2_IMG_DLL} ${ZLIB_DLL} ${PNG_DLL}
                       $<TARGET_FILE_DIR:PhysicsSim>
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/assets")

endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	# SSE 4.1 flag needed for GCC
	target_compile_options(${PROJECT_NAME} -msse4.1)
endif()
