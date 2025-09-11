cmake_minimum_required(VERSION 3.10)
project(MultiExecutableProject)
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(src)
include_directories(lib)  # Add lib directory to include path

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all .c files in lib/ for the helper library
file(GLOB LIB_SOURCES "lib/*.c")

# Create a static library from helper files
if(LIB_SOURCES)
    add_library(helpers STATIC ${LIB_SOURCES})
    message(STATUS "Created helper library with sources: ${LIB_SOURCES}")
endif()

# Find all .c files in src/
file(GLOB SOURCES "src/*.c")

# Create executable for each .c file in src/
foreach(source_file ${SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)
    add_executable(${exe_name} ${source_file})
    
    # Link the helper library to each executable (if it exists)
    if(LIB_SOURCES)
        target_link_libraries(${exe_name} helpers)
    endif()
    
    message(STATUS "Created executable: ${exe_name}")
endforeach()

# Optional: Create 'all' target
add_custom_target(build_all)
foreach(source_file ${SOURCES})
    get_filename_component(exe_name ${source_file} NAME_WE)
    add_dependencies(build_all ${exe_name})
endforeach()
