//
// Created by Gandifil on 20.02.2019.
//

#include <algorithm>
#include <sstream>
#include <iterator>
#include "Interpreter.h"
#include "../engine/Frame.h"
#include "../utils.h"
#include "ContainerVariable.h"
#include "Callback.h"

constexpr auto consolePrefix = "cpu-render> ";

using namespace std;

Interpreter::Interpreter()
{
    commands["command-list"] = make_unique<Command>([](std::vector<IVariable*>& args) -> IVariable*{
        return new StringVariable{"Test"};
    });
    commands["check-vector"] = make_unique<Command>([](std::vector<IVariable*>& args) -> IVariable*{
        return new StringVariable{"Test"};
    });
    commands["create-frame"] = make_unique<Command>([](std::vector<IVariable*>& args) -> IVariable*{
        return callback(&ctor_reference<Engine::Frame, float, float>, args);
    });
    commands["line"] = make_unique<Command>([](std::vector<IVariable*>& args) -> IVariable*{
        return callback(&Engine::Frame::i_line, args);
    });
    commands["save"] = make_unique<Command>([](std::vector<IVariable*>& args) -> IVariable*{
        return callback(&Engine::Frame::save, args);
    });
}

void Interpreter::listen(istream& input){
    string line;
    cout << consolePrefix;
    while (std::getline(input, line))
    {
        line.erase(std::remove(line.begin(), line.end(), ' '),
                   line.end());

        if (line == "exit")
            break;

        string target, callExpr;
        auto foundedEqualSymbol = line.find('=');
        if (foundedEqualSymbol == string::npos)
        {
            cout << call(line)->toString() << endl;
        }
        else
        {
            target = line.substr(0, foundedEqualSymbol);
            callExpr = line.substr(foundedEqualSymbol + 1);
            assignment(target, call(callExpr));
        }

        cout << consolePrefix;
    }
}

inline IVariable* Interpreter::call(const string& expression){
    auto  foundedBegin = expression.find('(');
    auto  foundedEnd = expression.find(')');

    if (foundedBegin == std::string::npos && foundedEnd == std::string::npos){
        // checking of containing variable
        auto value = variables.find(expression);
        if (value != variables.end())
            return value->second.get();

        // checking float
        try {
            float x = stof(expression);
            return saveTempVariable(new FloatVariable{x});
        }
        catch (invalid_argument& e)
        {}

        // checking string variable
        if (expression[0] == '"' && expression[expression.length() - 1] == '"')
            return saveTempVariable(new StringVariable{expression.substr(1, expression.length() - 2)});
    }
    else {
        // call of command
        if (foundedBegin >= foundedEnd)
            return nullptr;

        auto tokens = split_by_delimiter(
                expression.substr(foundedBegin + 1, foundedEnd - foundedBegin - 1), ',');

        std::vector<IVariable*> args{tokens.size()};
        std::transform(tokens.begin(), tokens.end(), args.begin(),
                       [&](const std::string& str){ return this->call(str); } );

        IVariable* result = (*commands[expression.substr(0, foundedBegin)].get())(args);
        return result;
    }
    return nullptr;
}