//
// Created by Gandifil on 28.06.2019.
//

#include "Frame.h"

//constexpr TGAColor red(255, 0, 0, 255);

void Engine::Frame::line(Math::Vector<int, 2> a, Math::Vector<int, 2> b){
    TGAColor color(255, 0, 0, 255);
    constexpr int k =  20;

    bool steep = false;
    if (std::abs(a.x() - b.x()) < std::abs(a.y() - b.y())) {
        std::swap(a.x(), a.y());
        std::swap(b.x(), b.y());
        steep = true;
    }
    if (a.x() > b.x()) {
        std::swap(a, b);
    }

    int dx = b.x() - a.x();
    int dy = b.y() - a.y();

    float derror = std::abs(dy/float(dx));
    float error = 0;
    int y = a.y();
    for (int x=a.x(); x<=b.x(); x++) {
        if (steep) {
            set(y, x, color);
        } else {
            set(x, y, color);
        }
        error += derror;

        if (error>.5) {
            y += (b.y()>a.y()?1:-1);
            error -= 1.;
        }
    }
}

void Engine::Frame::save(const std::string &filename){
    flip_vertically();
    write_tga_file(filename.c_str());
}