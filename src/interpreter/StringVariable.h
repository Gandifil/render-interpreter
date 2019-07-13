//
// Created by Gandifil on 24.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_STRINGVARIABLE_H
#define CONSOLE_CPU_RENDER_STRINGVARIABLE_H

#include <string>
#include "IVariable.h"

class StringVariable: public IVariable
{
public:
    StringVariable(const std::string& value): value{value}{}


    const std::string toString() const{
        return value;
    }

private:
    std::string value;
};
#endif //CONSOLE_CPU_RENDER_STRINGVARIABLE_H
