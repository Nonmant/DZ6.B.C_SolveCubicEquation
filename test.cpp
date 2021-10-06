#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "catch.hpp"

TEST_CASE("Catch operability", "[simple]"){
    REQUIRE(1+1 == 2);
}

#include "funcs.h"

TEST_CASE("test 1, file", "[simple]"){
    std::ofstream inputPrepare;
    inputPrepare.open ("cubroot.in", std::ofstream::trunc);
    inputPrepare<<"1 -3 3 -1";
    inputPrepare.close();

    std::ifstream input( "cubroot.in", std::ofstream::in);
    std::ofstream output("cubroot.out", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
    
    std::ifstream outputCheck("cubroot.out", std::ofstream::in);
    std::stringstream buffer;
    buffer<<outputCheck.rdbuf();
    outputCheck.close();
    REQUIRE(buffer.str().substr(0,7) == std::string("1.0000036491").substr(0,7));
}

TEST_CASE("test 2", "[simple]"){
    std::stringstream input, output;
    input<<"-1 -6 -12 -7";
    parseFile(input,output);
    REQUIRE(output.str().substr(0,8) == std::string("-1.0000000111").substr(0,8));
}
