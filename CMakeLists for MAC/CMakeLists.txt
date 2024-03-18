cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

#
#
# @TODO: Change this project to the name of your project
#
#
project("SpaceDome")

#-----------FOR MAC APPLE SILICON------------------------------------------------------
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-macro-redefined")

set(CMAKE_PREFIX_PATH "/opt/homebrew")
#--------------END OF MAC--------------------------------------------------------------

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

find_package(glm REQUIRED)
#MAC
find_package(PNG REQUIRED)

# Debug messages
message(STATUS "PNG include dir: ${PNG_INCLUDE_DIR}") # Fixed variable name
message(STATUS "PNG libraries: ${PNG_LIBRARIES}") # Correct variable name
#ENDMAC

#
# Adding the source files here that are compiled for this project
#
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/websockethandler.h
  src/websockethandler.cpp
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
  #MAC
  ${PNG_INCLUDE_DIR} # Use the variable set by find_package
  #ENDMAC
)

#target_link_libraries(${PROJECT_NAME} PRIVATE sgct websockets glm::glm assimp)

#----------MAC
target_link_libraries(${PROJECT_NAME} PRIVATE sgct websockets glm::glm assimp ${PNG_LIBRARIES})
#-----------END MAC

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
