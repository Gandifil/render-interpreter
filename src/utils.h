//
// Created by Gandifil on 05.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_UTILS_H
#define CONSOLE_CPU_RENDER_UTILS_H

#include <string>
#include <vector>
#include <sstream>

std::vector<std::string> split_by_delimiter(const std::string& source, char delimiter = ' '){
    std::vector<std::string> tokens;
    std::istringstream ss(source);
    std::string token;

    while(std::getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

#endif //CONSOLE_CPU_RENDER_UTILS_H
