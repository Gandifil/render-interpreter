#include "interpreter/Interpreter.h"

Interpreter interpreter;

int main(int argc, char* argv[]) {
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