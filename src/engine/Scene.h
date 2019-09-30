//
// Created by mikopyev on 13.09.2019.
//

#ifndef CONSOLE_CPU_RENDER_SCENE_H
#define CONSOLE_CPU_RENDER_SCENE_H

#include "math/Matrix.h"

namespace Engine
{
    class Scene: public IVariable {
    public:
        class Object : public IVariable
        {
        public:
            const Model& model;
            //Math::Matrix<float, 4, 4> pos;

            Object(const Model& model): model{model}{}

            Object(const Object& obj): model{obj.model}
            {

            }

            const std::string toString() const override
            {
                return "Object";
            }
        };

        void add(Object& object)
        {
            objects.push_back(object);
        }

        std::vector<Object> objects;

        const std::string toString() const override
        {
            return "Scene";
        }
    };
}


#endif //CONSOLE_CPU_RENDER_SCENE_H
