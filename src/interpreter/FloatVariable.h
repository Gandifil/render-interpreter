//
// Created by Gandifil on 24.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_FLOATVARIABLE_H
#define CONSOLE_CPU_RENDER_FLOATVARIABLE_H

#include <string>
#include "IVariable.h"

class FloatVariable: public IVariable
{
public:
    FloatVariable(float value): value{value}{}

    const std::string toString() const{
        return std::to_string(value);
    }

    operator float() const{
        return value;
    }

    operator int() const{
        return value;
    }
private:
    float value;
};
#endif //CONSOLE_CPU_RENDER_FLOATVARIABLE_H
