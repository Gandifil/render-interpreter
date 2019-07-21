//
// Created by Gandifil on 20.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_COMMAND_H
#define CONSOLE_CPU_RENDER_COMMAND_H

#include <functional>
#include <winsock.h>
#include "ContainerVariable.h"

class Command{
public:
    typedef IVariable* ReturnedValue;
    typedef std::vector<ReturnedValue>& Arguments;
    typedef std::function<ReturnedValue(Arguments)> Delegate;

    inline virtual ReturnedValue operator()(Arguments args) = 0;
protected:
    template<typename T>
    inline static T _expand(ReturnedValue var){
        using need_type =
                std::remove_cv_t<
                std::remove_reference_t<
                std::remove_pointer_t<T>>>;

        using pointer_type = typename std::conditional<std::is_base_of_v<IVariable, need_type>,
                        need_type*,
                        ContainerVariable<need_type>*>::type;

        auto value = dynamic_cast<pointer_type>(var);

        if constexpr (std::is_pointer<T>::value)
            return value;
        else
            return *value;
    }
};

#endif //CONSOLE_CPU_RENDER_COMMAND_H
