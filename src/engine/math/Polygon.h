//
// Created by mikopyev on 10.09.2019.
//

#ifndef CONSOLE_CPU_RENDER_POLYGON_H
#define CONSOLE_CPU_RENDER_POLYGON_H

namespace Engine::Math {
    template<typename T, size_t N>
    struct ModelPoint {
        Vector<T, N> geometric, texture, normal;
    };

    template<typename T>
    using Polygon = std::array<ModelPoint<T, 3>, 3>;
}


#endif //CONSOLE_CPU_RENDER_POLYGON_H
