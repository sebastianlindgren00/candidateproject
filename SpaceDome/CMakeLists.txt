cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("SpaceDome")

#-----------FOR MAC APPLE SILICON------------------------------------------------------
if(APPLE)
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-macro-redefined")

set(CMAKE_PREFIX_PATH "/opt/homebrew")
endif()
#--------------END OF MAC--------------------------------------------------------------

# Add the libraries that this application depends on,
#  1. SGCT (https://github.com/sgct/sgct) for window handling and cluster support
#  2. libwebsockets (https://libwebsockets.org) for support for WebSockets

# Disable SSL requirement as it requires another library
#set(LWS_WITH_SSL OFF CACHE BOOL "" FORCE)
#set(LWS_WITHOUT_TESTAPPS ON CACHE BOOL "" FORCE)
#add_subdirectory(ext/libwebsockets)
#set_property(TARGET dist PROPERTY FOLDER "Dependencies")
#set_property(TARGET websockets PROPERTY FOLDER "Dependencies")
#set_property(TARGET websockets_shared PROPERTY FOLDER "Dependencies")

add_subdirectory(ext/sgct)
set_property(TARGET sgct PROPERTY FOLDER "Dependencies")

add_subdirectory(ext/assimp)
set_property(TARGET assimp PROPERTY FOLDER "Dependencies")
set_property(TARGET assimp PROPERTY CXX_STANDARD 17)
set_property(TARGET assimp PROPERTY CXX_STANDARD_REQUIRED ON)

# Models folder path fix!
set(MODELS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/models")
#set(MODELS_DIRECTORY "./")

find_package(glm REQUIRED)
#MAC
if(APPLE)
find_package(PNG REQUIRED)
endif()
# Debug messages
message(STATUS "PNG include dir: ${PNG_INCLUDE_DIR}") # Fixed variable name
message(STATUS "PNG libraries: ${PNG_LIBRARIES}") # Correct variable name
#ENDMAC

#
# Adding the source files here that are compiled for this project
#
add_executable(${PROJECT_NAME}
  src/main.cpp
  ###NEW FILES FOR OMNI
  src/exception.cpp
  src/exception.h
  src/socket.cpp
  src/socket.h
  src/tcpsocket.cpp
  src/tcpsocket.h
  src/tcpsocket.inl
  ###
  #src/websockethandler.h
  #src/websockethandler.cpp
  src/AssimpLoader.h 
  src/AssimpLoader.cpp 
  src/mesh.cpp
  src/mesh.h
  src/utility.h
  src/utility.cpp
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
  src/shaderManager.h
  src/backgroundObjects.cpp
  src/backgroundObjects.h
  src/text.cpp
  src/text.h
  src/TextItem.h
  src/booster.h
  src/booster.cpp
)
#---------- MAC
#include_directories(/opt/homebrew/Cellar/libpng/1.6.43/include)
#link_directories(/opt/homebrew/Cellar/libpng/1.6.43/lib)

#-----------END MAC


target_include_directories(${PROJECT_NAME} PRIVATE
  src
  ext/sgct/include
  ext/sgct/ext/json/include
  #ext/libwebsockets/include
  ext/assimp/include
 # ${LIBWEBSOCKETS_INCLUDE_DIRS}
  #MAC
  ${PNG_INCLUDE_DIR} # Use the variable set by find_package
  #ENDMAC
)

#target_link_libraries(${PROJECT_NAME} PRIVATE sgct websockets glm::glm assimp)

#----------MAC
target_link_libraries(${PROJECT_NAME} PRIVATE sgct glm::glm assimp ${PNG_LIBRARIES}) # Was "websockets" between sgct and glm but removed for testing
#-----------END MAC

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
