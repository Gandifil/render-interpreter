//
// Created by Gandifil on 21.07.2019.
//

#ifndef CONSOLE_CPU_RENDER_MODEL_H
#define CONSOLE_CPU_RENDER_MODEL_H

#include <string>
#include "../interpreter/IVariable.h"
#include "../engine/math/Vector.h"
#include "../engine/math/Polygon.h"

namespace Engine{
    class Model: public IVariable{
    private:
        std::vector<Math::Polygon<float>> polygons;

    public:
        explicit Model(const std::string& filename);

		explicit Model(const Model& model)
		{
			// DON"T DO IT
		};

        const std::vector<Math::Polygon<float>>& getPolygons() const
        {
            return polygons;
        }

        const std::string toString() const override
        {
            return "Model";
        }
    };
}


#endif //CONSOLE_CPU_RENDER_MODEL_H
