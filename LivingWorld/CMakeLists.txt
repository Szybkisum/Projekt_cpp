cmake_minimum_required(VERSION 3.10)
project(LivingWorld LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)
# find_package(SDL2_image REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS} include)
# include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} include)

# Source files
file(GLOB SOURCES src/*.cpp)

# Executable
add_executable(LivingWorld ${SOURCES})

# Link SDL2 libraries
target_link_libraries(LivingWorld ${SDL2_LIBRARIES})
# target_link_libraries(LivingWorld ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})