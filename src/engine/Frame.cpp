//
// Created by Gandifil on 28.06.2019.
//

#include <iostream>
#include "Frame.h"


void Engine::Frame::i_line(float x1, float y1, float x2, float y2, const TGAColor& color) {
    line({x1, y1}, {x2, y2}, color);
}

void Engine::Frame::line(Math::Vec2i a, Math::Vec2i b, const TGAColor& color){
	constexpr int RESIZE_N = 20;
	constexpr int RESIZE_VALUE = 1ll << RESIZE_N;

    bool steep = false;

	int dx = std::abs(b.x() - a.x());
	int dy = std::abs(b.y() - a.y());

    if (dx < dy) {
        std::swap(a.x(), a.y());
        std::swap(b.x(), b.y());
		std::swap(dx, dy);
        steep = true;
    }

    if (a.x() > b.x()) 
        std::swap(a, b);

	if (!dx)
		return;

	int derror = (dy << RESIZE_N) / dx;
    float error = RESIZE_VALUE / 2;
    int y = a.y();
	int yStep = (b.y() > a.y() ? 1 : -1);
    for (int x=a.x(); x<=b.x(); x++) {
        if (steep) {
            set(y, x, color);
        } else {
            set(x, y, color);
        }
        error += derror;

        if (error > RESIZE_VALUE) {
            y += yStep;
            error -= RESIZE_VALUE;
        }
    }
}

void Engine::Frame::save(const std::string &filename){
    flip_vertically();
    write_tga_file(filename.c_str());
}

void Engine::Frame::i_render(const Engine::Scene &scene) {
    for(const auto& obj: scene.objects)
        render(obj);
}

void Engine::Frame::render(const Engine::Scene::Object &object) {
    // constexpr
    int i = 0;
    TGAColor red{255, 0, 0, 255};
    for(auto &polygon: object.model.getPolygons())
		render(polygon);
}

void Engine::Frame::render(Engine::Math::Polygon<float> polygon) {
	using interpolateVector = Engine::Math::Vector<long long, 7>;
	constexpr int RESIZE_N = 20;
	constexpr int RESIZE_VALUEL = 1 << RESIZE_N;
	constexpr float RESIZE_VALUE = RESIZE_VALUEL;

	static std::vector<long long> zbuffer(width * height, INT64_MIN);

	Engine::Math::Polygon<long long> pol;
	for (size_t i = 0; i < 3; i++)
	{
		pol[i].geometric = worldToScreen(polygon[i].geometric).embed<3>(polygon[i].geometric.z() * RESIZE_VALUE);
		pol[i].geometric.x() *= RESIZE_VALUEL;
		pol[i].texture = polygon[i].texture * RESIZE_VALUE;
		pol[i].normal = polygon[i].normal * RESIZE_VALUE;
	}

	// сортировка точек
	if (pol[0].geometric.y() > pol[1].geometric.y())
		std::swap(pol[0], pol[1]);
	if (pol[0].geometric.y() > pol[2].geometric.y())
		std::swap(pol[0], pol[2]);
	if (pol[1].geometric.y() > pol[2].geometric.y())
		std::swap(pol[1], pol[2]);

	int dy1 = pol[2].geometric.y() - pol[0].geometric.y();
	int dy2 = pol[1].geometric.y() - pol[0].geometric.y();
	int dy3 = pol[2].geometric.y() - pol[1].geometric.y();

	if (!dy1) return;
	interpolateVector main_dx{
		(pol[2].geometric.x() - pol[0].geometric.x()) / dy1,
		(pol[2].geometric.z() - pol[0].geometric.z()) / dy1,

		(pol[2].texture.x() - pol[0].texture.x()) / dy1,
		(pol[2].texture.y() - pol[0].texture.y()) / dy1,

		(pol[2].normal.x() - pol[0].normal.x()) / dy1,
		(pol[2].normal.y() - pol[0].normal.y()) / dy1,
		(pol[2].normal.z() - pol[0].normal.z()) / dy1, 
	};

	interpolateVector natural1_dx{
		pol[1].geometric.x() - pol[0].geometric.x(),
		pol[1].geometric.z() - pol[0].geometric.z(),

		pol[1].texture.x() - pol[0].texture.x(),
		pol[1].texture.y() - pol[0].texture.y(),

		pol[1].normal.x() - pol[0].normal.x(),
		pol[1].normal.y() - pol[0].normal.y(),
		pol[1].normal.z() - pol[0].normal.z(),
	};
	if (dy2)
		natural1_dx /= dy2;

	interpolateVector natural2_dx{
		pol[2].geometric.x() - pol[1].geometric.x(),
		pol[2].geometric.z() - pol[1].geometric.z(),

		pol[2].texture.x() - pol[1].texture.x(),
		pol[2].texture.y() - pol[1].texture.y(),

		pol[2].normal.x() - pol[1].normal.x(),
		pol[2].normal.y() - pol[1].normal.y(),
		pol[2].normal.z() - pol[1].normal.z(),
	};
	if (dy3)
		natural2_dx /= dy3;

	bool isMainOnLeft = dy2 ? 
		main_dx[0] < natural1_dx[0] :
		pol[0].geometric.x() < pol[1].geometric.x();

	interpolateVector left, right, dleft, dright;
	left = right = { 
		pol[0].geometric.x(),
		pol[0].geometric.z(),

		pol[0].texture.x(),
		pol[0].texture.z(),

		pol[0].normal.x(),
		pol[0].normal.y(),
		pol[0].normal.z(),
	};
	dleft = isMainOnLeft ? main_dx : natural1_dx;
	dright = !isMainOnLeft ? main_dx : natural1_dx;

	bool half = true;
    for (int y = pol[0].geometric.y(); y < pol[2].geometric.y(); y++)
    {
		if (half && y == pol[1].geometric.y())
		{
			(isMainOnLeft ? dright : dleft) = natural2_dx;
			(isMainOnLeft ? right : left) = {
				pol[1].geometric.x(),
				pol[1].geometric.z(),

				pol[1].texture.x(),
				pol[1].texture.z(),

				pol[1].normal.x(),
				pol[1].normal.y(),
				pol[1].normal.z(), 
			};
			half = false;
		}
		left += dleft;
		right += dright;

		interpolateVector pixel{ left };
		interpolateVector dpixel{right - left};
		if (dpixel[0] / RESIZE_VALUEL != 0)
			dpixel /= dpixel[0] / RESIZE_VALUEL;

        for (int x = left[0] / RESIZE_VALUEL; x < right[0] / RESIZE_VALUEL; x++) {
			pixel += dpixel;
			int z = (pixel[1] + RESIZE_VALUEL) / 2;
			if (zbuffer[width * x + y] < z)
			{
				zbuffer[width * x + y] = z;
				const Engine::Math::Vector<float, 3> ligth{ .5, .5, .5 };
				Engine::Math::Vector<float, 3> normal{ pixel[4], pixel[5], pixel[6] };
				normal /= RESIZE_VALUE;
				float mz = normal * ligth;
				if (mz > 0)
				{
					unsigned char b = mz * 255;
					set(x, y, TGAColor{ b, b, b, 255 });
				}
			}
        }
    }


}

