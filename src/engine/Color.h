//
// Created by Gandifil on 30.09.2019.
//

#ifndef CONSOLE_CPU_RENDER_COLOR_H
#define CONSOLE_CPU_RENDER_COLOR_H

#include <sstream>

namespace Engine{
    struct Color {
        union {
            struct {
                unsigned char b, g, r, a;
            };
            unsigned char raw[4];
            unsigned int val;
        };

        constexpr Color(unsigned char R, unsigned char G, unsigned char B)
                : b(B), g(G), r(R), a(255){}

        constexpr Color(unsigned char R, unsigned char G, unsigned char B, unsigned char A)
            : b(B), g(G), r(R), a(A){}

        Color(int v) : val(v){}

        Color(const Color &c) : val(c.val) {
        }

        Color & operator =(const Color &c) {
            if (this != &c)
                val = c.val;
            return *this;
        }

        const static Color RED;
        const static Color GREEN;
        const static Color BLUE;
    };

}

namespace std{
    inline string to_string(const Engine::Color& color){
        stringstream stream{};
        stream << '(' << std::to_string(color.r) << ", ";
        stream << std::to_string(color.g) << ", ";
        stream << std::to_string(color.b) << ")";
        return stream.str();
    }
}
#endif //CONSOLE_CPU_RENDER_COLOR_H
