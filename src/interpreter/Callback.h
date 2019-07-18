//
// Created by Gandifil on 16.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_CALLBACK_H
#define CONSOLE_CPU_RENDER_CALLBACK_H

#include "IVariable.h"
#include "ContainerVariable.h"
#include "Command.h"

template<typename T>
static T _expand(IVariable* var){
    using need_type = typename std::remove_const<typename std::remove_reference<T>::type>::type;
    auto container = dynamic_cast<ContainerVariable<need_type> *>(var);
    assert(container);
    //assert(res);
    return *container;
}

template<typename R, typename T, typename... Args>
IVariable* callback(R(T::* func)(Args...), Command::Arguments args){
    int i = 1;
    if constexpr (std::is_same<R, void>::value)
    {
        std::bind(func, args[0], _expand<Args>(args[i++])...);
        return new StringVariable{"OK!"};
    }
    else
        return std::bind(func, args[0], _expand<Args>(args[i++])...);
}

template<typename R, typename... Args>
IVariable* callback(R func(Args...), Command::Arguments args){
    int i = 0;
    if constexpr (std::is_same<R, void>::value)
    {
        std::bind(func, _expand<Args>(args[i++])...);
        return new StringVariable{"OK!"};
    }
    else
        return std::bind(func, _expand<Args>(args[i++])...)();
}

template<typename T, typename... Args>
IVariable* ctor_reference(Args... args){
    return new T(args...);
}

#endif //CONSOLE_CPU_RENDER_CALLBACK_H
