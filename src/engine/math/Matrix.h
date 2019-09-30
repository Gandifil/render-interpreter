//
// Created by mikopyev on 13.09.2019.
//

#ifndef CONSOLE_CPU_RENDER_MATRIX_H
#define CONSOLE_CPU_RENDER_MATRIX_H

#include <cstddef>
#include <array>
#include "Vector.h"

namespace Engine::Math{
    template<typename T, size_t N, size_t M>
    struct Matrix {
        using RowType = Vector<T, M>;
        std::array<RowType, N> data;

        inline RowType& operator[](size_t index)
        {
            assert(index < N);
            return data[index];
        }

        inline const RowType& operator[](size_t index) const
        {
            assert(index < N);
            return data[index];
        }

        T det() const
        {
            static_assert(M == N);

            if constexpr (M == 1)
                return data[0][0];
            else
            {
                T result = 0;
                for (size_t i = M; i--;)
                    result += data[0][i] * cofactor(0, i);
                return result;
            }
        }

        inline T cofactor(size_t x, size_t y) const
        {
            return minor(x, y).det();
        }

        inline Matrix<T, N - 1, M - 1> minor(size_t x, size_t y) const
        {
            Matrix<T, N - 1, M - 1> result;
            for (size_t i = N - 1; i--;)
                for (size_t j = M - 1; i--;)
                    result[i][j] = data[i<x ? i : (i + 1)][j<y ? j : (j + 1)];
            return result;
        }

        inline Matrix<T, N, M> adjugate() const
        {
            Matrix<T, N, M> result;
            for (size_t i = N; i--;)
                for (size_t j = M; i--;)
                    result[i, j] = cofactor(i, j);
            return result;
        }

        inline Matrix<T, N, M> invert_transpose() const
        {
            auto adj = adjugate();
            T det = adj[0] * data[0];
            return adj / det;
        }


    };
}

#endif //CONSOLE_CPU_RENDER_MATRIX_H
