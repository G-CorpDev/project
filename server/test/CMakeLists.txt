find_library(LIB_NET net)
find_library(LIB_JWT jwt)
find_library(LIB_JANSSON jansson)
find_library(LIB_GTEST gtest)
find_library(LIB_PTHREAD pthread)


file(GLOB TEST_SRC_FILES "*.cpp")
file(GLOB SRC_FILES "../src/*.cpp")
list(REMOVE_ITEM SRC_FILES "/home/mate/Projects/project/server/test/../src/main.cpp")

add_executable(Test ${TEST_SRC_FILES} ${SRC_FILES})

target_link_libraries(Test "${LIB_NET}")
target_link_libraries(Test "${LIB_JWT}")
target_link_libraries(Test "${LIB_JANSSON}")
target_link_libraries(Test "${LIB_GTEST}")
target_link_libraries(Test "${LIB_PTHREAD}")