//
// Created by Gandifil on 20.02.2019.
//

#ifndef CONSOLE_CPU_RENDER_IVARIABLE_H
#define CONSOLE_CPU_RENDER_IVARIABLE_H

class IVariable{
public:
    virtual ~IVariable(){};

    virtual const std::string toString() const = 0;
};
#endif //CONSOLE_CPU_RENDER_IVARIABLE_H
