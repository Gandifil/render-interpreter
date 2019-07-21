//
// Created by Gandifil on 21.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_CONSTANTCOMMAND_H
#define CONSOLE_CPU_RENDER_CONSTANTCOMMAND_H

#include "ContainerVariable.h"
#include "Command.h"

template<typename T>
class ConstantCommand: public Command, private ContainerVariable<T>{
public:
    ConstantCommand(const T& value):ContainerVariable<T>{value}{}

    ConstantCommand(T&& value):ContainerVariable<T>{std::move(value)}{}

    inline ReturnedValue operator()(Arguments args){
        //It must copy itself, because copy will be destroyed
        return new ContainerVariable<T>(*this);
    }
};

#endif //CONSOLE_CPU_RENDER_CONSTANTCOMMAND_H
