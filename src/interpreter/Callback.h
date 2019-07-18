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

template<typename T, typename... Args>
static IVariable* callback(void(T::* func)(Args...), Command::Arguments args){
    int i = 1;
    std::bind(func, args[0], _expand<Args>(args[i++])...);///(ExpandedList<1, Args...>::open(args)));
    return new StringVariable{"OK!"};
}

#endif //CONSOLE_CPU_RENDER_CALLBACK_H
