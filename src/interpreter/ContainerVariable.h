//
// Created by Gandifil on 13.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_CONTAINERVARIABLE_H
#define CONSOLE_CPU_RENDER_CONTAINERVARIABLE_H

#include <string>
#include "IVariable.h"
#include "../tgaimage.h"

template<typename T>
class ContainerVariable: public IVariable{
public:
    ContainerVariable(const T& data):value{data}{}

    ContainerVariable(T&& data):value{std::move(data)}{}

    const std::string toString() const {
        if constexpr (std::is_same<T, std::string>::value)
            return value;
        else
            return std::to_string(value);
    }

    operator T() const{
        return value;
    }
private:
    T value;
};

typedef ContainerVariable<float> FloatVariable;
typedef ContainerVariable<std::string> StringVariable;


#endif //CONSOLE_CPU_RENDER_CONTAINERVARIABLE_H
