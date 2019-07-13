//
// Created by Gandifil on 20.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_INTERPRETER_H
#define CONSOLE_CPU_RENDER_INTERPRETER_H

#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include "IVariable.h"
#include "Command.h"

class Interpreter {
public:
    Interpreter();
    void listen(std::istream& input);

private:
    std::map<std::string, std::unique_ptr<IVariable>> variables;
    std::map<std::string, std::unique_ptr<Command>> commands;

    const std::string TEMP_VARIABLES_NAME = "temp_";

    // create variable with some name and value
    inline void assignment(const std::string& name, IVariable *var){
        variables.insert(std::make_pair(name, std::unique_ptr<IVariable>(var)));
    }

    // call some command using name from commands
    IVariable* call(const std::string& expression);

    // save variable using temp name
    inline IVariable* saveTempVariable(IVariable *var){
        static long long index = 0;
        assignment(TEMP_VARIABLES_NAME + std::to_string(index++), var);
        return var;
    };
};


#endif //CONSOLE_CPU_RENDER_INTERPRETER_H
