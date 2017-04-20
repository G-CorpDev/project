#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    if(argc>1){
        if(std::string(argv[1])=="-s"){
            std::cout<<"Running tests silently."<<std::endl;
            ::testing::InitGoogleTest(&argc, argv);
            RUN_ALL_TESTS();
            return 0;
        }
    }
    ::testing::InitGoogleTest(&argc, argv);
    auto res = RUN_ALL_TESTS();
    std::cin.get();
    return res;
}