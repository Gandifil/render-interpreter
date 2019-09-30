//
// Created by Gandifil on 28.06.2019.
//

#ifndef CONSOLE_CPU_RENDER_FRAME_H
#define CONSOLE_CPU_RENDER_FRAME_H


#include "../tgaimage.h"
#include "math/Vector.h"
#include "../interpreter/IVariable.h"
#include "Model.h"
#include "Scene.h"

namespace Engine{

    class Frame: public TGAImage, public IVariable {
        public:
            Frame(int w, int h):
                    TGAImage{w, h, TGAImage::RGB}
            {
            }

            void line(Math::Vec2i a, Math::Vec2i b, const TGAColor& color);

            void i_line(float x1, float y1, float x2, float y2, const TGAColor& color);

            // render
            void i_render(const Scene& scene);
            void render(const Scene::Object& object);
            void render(Math::Polygon<float> polygon);

            void save(const std::string& filename);

            inline Engine::Math::Vector<int, 2> worldToScreen(const Engine::Math::Vec3f& vector) const
            {
                return {static_cast<int>((vector.x() + 1.) * width) / 2,
                        static_cast<int>((vector.y() + 1.) * width) / 2};
            }

            const std::string toString() const override {
                return "Frame";
            };
        };
    }


#endif //CONSOLE_CPU_RENDER_FRAME_H
