cmake_minimum_required(VERSION 3.10)
project(MonkFS)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(network/include)
include_directories(storage/include)

# Source files for the network module
file(GLOB NETWORK_SOURCES
  "network/src/*.cpp"
)

# Source files for the storage module
file(GLOB STORAGE_SOURCES
  "storage/src/*.cpp"
)

# Create the network library
add_library(Network STATIC ${NETWORK_SOURCES})

# Create the storage library
add_library(Storage STATIC ${STORAGE_SOURCES})

# Optionally, create an executable for testing
add_executable(MonkFS main.cpp)

# Link the libraries to the executable
target_link_libraries(MonkFS Network Storage)
