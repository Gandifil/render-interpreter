//
// Created by Gandifil on 28.06.2019.
//

#ifndef CONSOLE_CPU_RENDER_FRAME_H
#define CONSOLE_CPU_RENDER_FRAME_H


#include "../tgaimage.h"
#include "math/Vector.h"
#include "../interpreter/IVariable.h"

namespace Engine{

    class Frame: public TGAImage, public IVariable {
        public:
            Frame(int w, int h):
                    TGAImage{w, h, TGAImage::RGB}
            {
            }

            void line(Math::Vector<int, 2> a, Math::Vector<int, 2> b, const TGAColor& color);

            void i_line(float x1, float y1, float x2, float y2, const TGAColor& color);

            void save(const std::string& filename);

            const std::string toString() const {
                return "Frame";
            };
        };
    }


#endif //CONSOLE_CPU_RENDER_FRAME_H
