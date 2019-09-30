//
// Created by Gandifil on 21.06.2019.
// based on https://habr.com/ru/post/248909/
//

#pragma once

#include <array>
#include <string>
#include <assert.h>
#include <iterator>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>

namespace Engine::Math{
    template<typename T>
    inline T fromString(std::string str);

    template<>
    inline float fromString<float>(std::string str){
        return std::stof(str);
    }

    template<>
    inline int fromString<int>(std::string str){
        return std::stoi(str);
    }


    template<typename T, size_t N>
    struct Vector{
        std::array<T, N> values;

        template<typename K>
        explicit Vector(const Vector<K, N>& vec){
            for (size_t i = N; i--; values[i] = vec.values[i]) ;
        }

        Vector(const Vector<T, N>& values):values{values.values}{}

        Vector(std::array<T, N>&& values):values{std::forward(values)}{};

        template <typename... D>
		Vector(D... ts) : values{ static_cast<T>(ts)... } {
        }

        Vector(std::string line){
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            for(int i = 0; i < N; i++)
                values[i] = fromString<T>(results[i]);
        }

        template<typename K>
        inline Vector<T, N>& operator=(const Vector<K, N>& vec)
        {
            for (size_t i = N; i--; values[i] = vec.values[i]) ;
            return *this;
        }

        inline T& operator[](size_t index){
            assert(index < N);
            return values[index];
        }

        inline T& x(){
            return values[0];
        }

        inline std::enable_if_t<(N > 1), T&> y(){
            return values[1];
        }

        template<typename T1 = T>
        inline std::enable_if_t<(N > 2), T1&> z(){
            return values[2];
        }

        inline T& w(){
            constexpr int M = N - 1;
            return values[M];
        }

        // const version

        inline const T& operator[](size_t index) const{
            assert(index < N);
            return values[index];
        }

        inline const T& x() const{
            return values[0];
        }

        inline std::enable_if_t<(N > 1), const T&> y() const{
            return values[1];
        }

        template<typename T1 = T>
        inline std::enable_if_t<(N > 2), const T1&> z() const{
            return values[2];
        }

        inline const T& w() const{
            constexpr int M = N - 1;
            return values[M];
        }

        // with scalar

        template<typename K>
        Vector<T, N>& operator+=(const K& a){
            for(size_t i = N; i--; values[i] += a);
            return this;
        }

        template<typename K>
        Vector<T, N>& operator-=(const K& a){
            for(size_t i = N; i--; values[i] -= a);
            return this;
        }

        template<typename K>
        Vector<T, N>& operator*=(const K& a){
            for(size_t i = N; i--; values[i] *= a);
            return this;
        }

        template<typename K>
        Vector<T, N>& operator/=(const K& a){
            for(size_t i = N; i--; values[i] /= a);
            return *this;
        }

        // with vector

        template<typename K>
        Vector<T, N>& operator+=(const Vector<K, N>& a){
            for(size_t i = N; i--; values[i] += a.values[i]);
            return *this;
        }

        template<typename K>
        Vector<T, N>& operator-=(const Vector<K, N>& a){
            for(size_t i = N; i--; values[i] -= a.values[i]);
            return *this;
        }

        // methods
        inline T length() const
        {
            return std::sqrt((*this) * (*this));
        }

        inline Vector<T, N> normalize(){
            return *this / length();
        }

        template<size_t M>
        inline std::enable_if_t<(M > N), Vector<T, M>> embed(T fillValue) const
        {
            Vector<T, M> result;
            // may be optimize
            for (size_t i = M; i--; result[i] = fillValue);
            for (size_t i = N; i--; result[i] = values[i]);
            return result;
        }

        template<size_t M>
        inline std::enable_if_t<(M < N), Vector<T, M>> projection() const
        {
            Vector<T, M> result;
            for (size_t i = 0; i < M; i++)
				result[i] = values[i];
            return result;
        }
    };

    // scalar
    template<typename T, size_t N>
    inline Vector<T, N> operator+(Vector<T, N> a, const T& b){
        for(size_t i = N; i--; a.values[i] += b);
        return a;
    }

    template<typename T, size_t N>
    inline Vector<T, N> operator*(Vector<T, N> a, const T& b){
        for(size_t i = N; i--; a.values[i] *= b);
        return a;
    }

    template<typename T, size_t N>
    inline Vector<T, N> operator-(Vector<T, N> a, const T& b){
        for(size_t i = N; i--; a.values[i] -= b);
        return a;
    }

    template<typename T, size_t N>
    inline Vector<T, N> operator/(Vector<T, N> a, const T& b){
        for(size_t i = N; i--; a.values[i] /= b);
        return a;
    }

    // vectors

    template<typename T, size_t N>
    inline T operator*(const Vector<T, N>& a, const Vector<T, N>& b){
        T res = 0;
        for(size_t i = N; i--; res+= a.values[i] * b.values[i]);
        return res;
    }

    template<typename T, size_t N>
    inline Vector<T, N> operator+(const Vector<T, N>& a, const Vector<T, N>& b){
        Vector<T, N> newValues;
        for(size_t i = N; i--;)
            newValues[i] = a.values[i] + b.values[i];
        return newValues;
    }

    template<typename T, size_t N>
    inline Vector<T, N> operator-(const Vector<T, N>& a, const Vector<T, N>& b){
        Vector<T, N> newValues;
        for(size_t i = N; i--;)
            newValues[i] = a.values[i] - b.values[i];
        return newValues;
    }

    template<size_t N, typename T>
    std::ostream& operator<<(std::ostream& out,const Vector<T, N>& v) {
        out<<"{ ";
        for (size_t i=0; i < N; i++)
            out<<std::setw(6)<<v[i]<<" ";
        out<<"} ";
        return out;
    }
    // add multiply between vector and vector

    typedef Vector<float, 4> Vec4f;
    typedef Vector<float, 3> Vec3f;
    typedef Vector<int, 4> Vec4i;
	typedef Vector<int, 2> Vec2i;
}