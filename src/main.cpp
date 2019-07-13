#include <iostream>
#include "interpreter/Interpreter.h"

int main(int argc, char* argv[]) {
    Interpreter interpreter;
    if (argc > 1){
        if (!freopen(argv[1], "r", stdin)){
            std::cout << "Incorrect filename " << argv[1]  <<"!" << std::endl
                <<" Write actual filename on first position!";
            return 0;
        }
    }

    interpreter.listen(std::cin);
    return 0;
}