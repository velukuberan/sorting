cmake_minimum_required(VERSION 3.10)
project(MultiExecutableProject)

set(CMAKE_CXX_STANDARD 17)

# Include src directory
include_directories(src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all .cpp files in src/
file(GLOB SOURCES "src/*.c")

# Create executable for each .cpp file
foreach(source_file ${SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)
    add_executable(${exe_name} ${source_file})
    message(STATUS "Created executable: ${exe_name}")
endforeach()

# Optional: Create 'all' target
add_custom_target(build_all)
foreach(source_file ${SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)
    add_dependencies(build_all ${exe_name})
endforeach()
