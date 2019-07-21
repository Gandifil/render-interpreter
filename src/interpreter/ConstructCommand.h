//
// Created by Gandifil on 21.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_CONSTRUCTCOMMAND_H
#define CONSOLE_CPU_RENDER_CONSTRUCTCOMMAND_H

#include "Command.h"

template<class T, typename... Args>
class ConstructCommand: public Command{
public:
    template<size_t... Indexes>
    inline ReturnedValue create(const std::index_sequence<Indexes...>&, Arguments args){
        return new T(_expand<Args>(args[Indexes])...);
    }

    inline ReturnedValue operator()(Arguments args){
        return create(std::index_sequence_for<Args...>{}, args);
    }
};

#endif //CONSOLE_CPU_RENDER_CONSTRUCTCOMMAND_H
