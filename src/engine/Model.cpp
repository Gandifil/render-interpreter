//
// Created by Gandifil on 21.07.2019.
//

#include <fstream>
#include <algorithm>
#include "Model.h"

using namespace std;

Engine::Model::Model(const string &filename) {
    ifstream file(filename);
    string line;
    vector<Engine::Math::Vec3f> vertices, textures, normals;
    // Engine::Math::Triangle empty{{{0., 0., 0.}, {0., 0., 0.}, {0., 0., 0.}}};

    while (getline(file, line))
        if (!line.empty())//
        {
            stringstream stream(line);
            stream.seekg(2);// >> ch >> ch;
            switch (line[0])
            {
                case 'v':
                    float x, y, z;
                    stream >> x >> y >> z;
                    switch (line[1])
                    {
                        case ' ':
                            vertices.emplace_back(x, y, z);
                            break;
                        case 't':
                            textures.emplace_back(x, y, z);
                            break;
                        case 'n':
                            normals.emplace_back(x, y, z);
                            break;
                    }
                    break;

                case 'f':
                    std::array<size_t, 3> v;
                    std::array<size_t, 3> t;
                    std::array<size_t, 3> n;

                    for (int i = 0; i < 3; ++i)
                    {
                        string number;
                        getline(stream, number, '/');
                        v[i] = stoi(number);
                        getline(stream, number, '/');
                        t[i] = stoi(number);
                        getline(stream, number, ' ');
                        n[i] = stoi(number);
                    }

                    Engine::Math::Polygon<float> polygon;
                    for (int i = 0; i < 3; ++i) {
                        assert((v[i] - 1) < vertices.size());
                        polygon[i].geometric = vertices[v[i] - 1];

                        assert((t[i] - 1) < textures.size());
                        polygon[i].texture = textures[t[i] - 1];

                        assert((n[i] - 1) < normals.size());
                        polygon[i].normal = normals[n[i] - 1];
                    }
                    polygons.push_back(move(polygon));
                    break;
            }
        }
}
