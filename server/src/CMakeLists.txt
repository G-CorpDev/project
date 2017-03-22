find_library(LIB_NET net)
find_library(LIB_JWT jwt)

file(GLOB SRC_FILES "*.cpp")

add_executable(Server ${SRC_FILES})

target_link_libraries(Server "${LIB_NET}")
target_link_libraries(Server "${LIB_JWT}")