cmake_minimum_required(VERSION 3.0)

project(Server)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

subdirs(src)
subdirs(test)

include_directories(./inc)

add_custom_target(doc
WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../doc
COMMAND echo "Generating documentation."
COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/../doc/
COMMAND echo ${PROJECT_SOURCE_DIR}
COMMAND doxygen
)
set_target_properties(doc PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)

add_custom_target(cleanup
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
COMMAND find . ! \\\( -name 'Server' -o -name 'Test' \\\) -type f -exec rm -f {} +
COMMAND find . ! \\\( -name bin -o -name . -o -name .. \\\) -type d -exec rm -rf {} +
)