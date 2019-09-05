//
// Created by Gandifil on 21.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_MODEL_H
#define CONSOLE_CPU_RENDER_MODEL_H

#include <string>
#include "../interpreter/IVariable.h"
#include "../engine/math/Vector.h"

namespace Engine{
    class Model: public IVariable{
    public:
        Model(const std::string& filename);

        const std::vector<Math::Vec3f> v, vn;
        const std::vector<Math::Vector<float, float>> vt;

    };
}


#endif //CONSOLE_CPU_RENDER_MODEL_H
