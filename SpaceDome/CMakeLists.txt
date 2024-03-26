cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

#
#
# @TODO: Change this project to the name of your project
#
#
project("SpaceDome")

#
# Add the libraries that this application depends on,
#  1. SGCT (https://github.com/sgct/sgct) for window handling and cluster support
#  2. libwebsockets (https://libwebsockets.org) for support for WebSockets

# Disable SSL requirement as it requires another library
set(LWS_WITH_SSL OFF CACHE BOOL "" FORCE)
set(LWS_WITHOUT_TESTAPPS ON CACHE BOOL "" FORCE)
add_subdirectory(ext/libwebsockets)
set_property(TARGET dist PROPERTY FOLDER "Dependencies")
set_property(TARGET websockets PROPERTY FOLDER "Dependencies")
set_property(TARGET websockets_shared PROPERTY FOLDER "Dependencies")

add_subdirectory(ext/sgct)
set_property(TARGET sgct PROPERTY FOLDER "Dependencies")

add_subdirectory(ext/assimp)
set_property(TARGET assimp PROPERTY FOLDER "Dependencies")
set_property(TARGET assimp PROPERTY CXX_STANDARD 17)
set_property(TARGET assimp PROPERTY CXX_STANDARD_REQUIRED ON)

# Models folder path fix!
set(MODELS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/models")

find_package(glm REQUIRED)


#
# Adding the source files here that are compiled for this project
#
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/websockethandler.h
  src/websockethandler.cpp
  src/AssimpLoader.h 
  src/AssimpLoader.cpp 
  src/mesh.cpp
  src/mesh.h
  src/utility.h
  src/utility.cpp
  src/objectValues.h
  src/shader.h
  src/globals.h
  src/player.cpp
  src/player.h
  src/game.h
  src/game.cpp
  src/bullets.h
  src/bullets.cpp
  src/stars.cpp
  src/stars.h
  src/skybox.cpp
  src/skybox.h
)
#---------- MAC
#include_directories(/opt/homebrew/Cellar/libpng/1.6.43/include)
#link_directories(/opt/homebrew/Cellar/libpng/1.6.43/lib)

#-----------END MAC


target_include_directories(${PROJECT_NAME} PRIVATE
  src
  ext/sgct/include
  ext/libwebsockets/include
  ext/assimp/include
  ${LIBWEBSOCKETS_INCLUDE_DIRS}
)
target_link_libraries(${PROJECT_NAME} PRIVATE sgct websockets glm::glm assimp)


# Models folder path fix! 
target_compile_definitions(${PROJECT_NAME} PRIVATE
    MODELS_DIRECTORY="${MODELS_DIRECTORY}"
)

#
# Setting some compile settings for the project
#
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if (MSVC)
  # Microsoft Visual Studio related compile options
  target_compile_options(${PROJECT_NAME} PRIVATE
    "/MP"       # Multi-threading support
    "/W4"       # Highest warning level
    "/wd4201"   # nonstandard extension used : nameless struct/union
    "/permissive-"
    "/Zc:__cplusplus" # Correctly set the __cplusplus macro
  )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # When compiling on Clang.  This most likely means compiling on MacOS
  target_compile_options(${PROJECT_NAME} PRIVATE
    "-stdlib=libc++"
    "-Wall"
    "-Wextra"
  )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  # Probably compiling on Linux
  target_compile_options(${PROJECT_NAME} PRIVATE
    "-ggdb"
    "-Wall"
    "-Wextra"
    "-Wpedantic"
  )
endif ()
