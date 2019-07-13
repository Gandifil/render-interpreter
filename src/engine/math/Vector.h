//
// Created by Gandifil on 21.06.2019.
//

#include <array>
#include <string>
#include <assert.h>
#include <iterator>
#include <vector>
#include <sstream>


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


    template<typename T, int N>
    struct Vector{
    private:
        std::array<T, N> values;

    public:
        Vector(std::array<T, N>&& values):values{std::move(values)}{};

        //Vector(std::initializer_list<T> list):values{{list}}{
        //}

        template <typename... D>
        Vector(D... ts) : values{{ts...}} {
        }

        Vector(std::string line){
            std::istringstream iss(line);
            std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                             std::istream_iterator<std::string>());
            for(int i = 0; i < N; i++)
                values[i] = fromString<T>(results[i]);
        }

        inline T& operator[](int index){
            return values[index];
        }

        inline T& x(){
            return values[0];
        }

        inline typename std::enable_if<(N > 1), T&>::type y(){
            return values[1];
        }

        inline typename std::enable_if<(N > 2), T&> z(){
            return values[2];
        }

        inline T& w(){
            constexpr int M = N - 1;
            return values[M];
        }

        // overload adding

        template<typename K>
        Vector<T, N>& operator+=(const Vector<K, N>& a){
            for(int i = N; i--;)
                values[i] += a.values[i];
            return this;
        }

        // overload multiply

        template<typename K>
        Vector<T, N>& operator*=(const K& a){
            for(int i = N; i--;)
                values[i] *= a;
            return this;
        }
    };

    template<typename T, typename K, int N>
    Vector<T, N>& operator+(const Vector<T, N>& a, const Vector<K, N>& b){
        std::array<T, N> newValues;
        for(int i = N; i--;)
            newValues[i] = a.values[i] + b.values[i];
        return {newValues};
    }

    template<typename T, typename K, int N>
    Vector<T, N>& operator*(const Vector<T, N>& a, const K& b){
        std::array<T, N> newValues;
        for(int i = N; i--;)
            newValues[i] = a.values[i] * b;
        return {newValues};
    }

    typedef Vector<float, 4> Vec4f;
    typedef Vector<float, 3> Vec3f;
    typedef Vector<int, 4> Vec4i;
}