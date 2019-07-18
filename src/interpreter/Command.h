//
// Created by Gandifil on 20.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_COMMAND_H
#define CONSOLE_CPU_RENDER_COMMAND_H

#include <functional>
#include <winsock.h>
#include "ContainerVariable.h"

class Command final{
public:
    typedef std::vector<IVariable*>& Arguments;
    typedef IVariable* ReturnedValue;
    typedef std::function<ReturnedValue(Arguments)> Delegate;

    Command(Delegate action): action{action}{}

    inline ReturnedValue operator()(Arguments args){
        return action(args);
    }

private:
    Delegate action;
};

#endif //CONSOLE_CPU_RENDER_COMMAND_H
