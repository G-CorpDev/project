cmake_minimum_required(VERSION 3.0)

project(Server)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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