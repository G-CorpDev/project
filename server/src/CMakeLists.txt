find_library(LIB_NET net)
find_library(LIB_JWT jwt)
find_library(LIB_JANSSON jansson)

file(GLOB SRC_FILES "*.cpp")

add_executable(Server ${SRC_FILES})

target_link_libraries(Server "${LIB_NET}")
target_link_libraries(Server "${LIB_JWT}")
target_link_libraries(Server "${LIB_JANSSON}")