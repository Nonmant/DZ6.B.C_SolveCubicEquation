#include "funcs.h"
#include <fstream>

int main(){
    std::ifstream input( "cubroot.in", std::ofstream::in);
    std::ofstream output("cubroot.out", std::ofstream::trunc);
    parseFile(input,output);
    input.close();
    output.close();
}
