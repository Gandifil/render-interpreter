//
// Created by Gandifil on 21.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_FUNCTIONCOMMAND_H
#define CONSOLE_CPU_RENDER_FUNCTIONCOMMAND_H

#include "Command.h"

template<typename R, typename C, typename... Args>
class _impl_FunctionCommand: public Command{
public:
    const static bool is_memfunc = !std::is_same_v<C, void>;
    using F = std::conditional_t<is_memfunc, R (C::*)(Args...), R(Args...)>;

    _impl_FunctionCommand(F value):f{value}{}

    inline ReturnedValue operator()(Arguments args) override{
        return fill(args);
    }

private:
    F f;

    template<size_t... Indexes>
    R invoke_helper(Arguments args, std::index_sequence<Indexes...> const &){
        if constexpr(is_memfunc)
            return (_expand<C*>(args[0])->*f)(_expand<Args>(args[Indexes+1])...);
        else
            return f(_expand<Args>(args[Indexes])...);
    }

    R invoke(Arguments args){
        return invoke_helper(args, std::index_sequence_for<Args...> {});
    }

    inline ReturnedValue fill(Arguments args){
        if constexpr (std::is_same_v<R, void>)
        {
            invoke(args);
            return new StringVariable{"OK!"};
        }
        else
            return invoke(args);
    }
};

template<typename F>
class FunctionCommand{
public:
    FunctionCommand(F f);
};

template<typename R, typename C, typename...Args>
class FunctionCommand<R(C::*)(Args...)>: public _impl_FunctionCommand<R, C, Args...>{
public:
    FunctionCommand(R(C::* value)(Args...)):_impl_FunctionCommand<R, C, Args...>(value){}
};

template<typename R, typename...Args>
class FunctionCommand<R(Args...)>: public _impl_FunctionCommand<R, void, Args...>{
public:
    FunctionCommand(R *value(Args...)):_impl_FunctionCommand<R, void, Args...>{value}{}
};

#endif //CONSOLE_CPU_RENDER_FUNCTIONCOMMAND_H
