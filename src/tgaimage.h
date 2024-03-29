#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <fstream>
#include "engine/Color.h"

#pragma pack(push,1)
struct TGA_Header {
	char idlength;
	char colormaptype;
	char datatypecode;
	short colormaporigin;
	short colormaplength;
	char colormapdepth;
	short x_origin;
	short y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
};
#pragma pack(pop)

struct TGAColor: public Engine::Color {
	int bytespp;

    TGAColor(const Engine::Color& color):
            Engine::Color{color}, bytespp(1) {}

	TGAColor() : Engine::Color{0}, bytespp(1) {
	}

	constexpr TGAColor(unsigned char R, unsigned char G, unsigned char B, unsigned char A) : Engine::Color{R, G, B, A}, bytespp(4) {
	}

	TGAColor(int v, int bpp) : Engine::Color(v), bytespp(bpp) {
	}

	TGAColor(const TGAColor &c) : Engine::Color(c.val), bytespp(c.bytespp) {
	}

	TGAColor(const unsigned char *p, int bpp) : Engine::Color(0), bytespp(bpp) {
		for (int i=0; i<bpp; i++) {
			raw[i] = p[i];
		}
	}

	TGAColor & operator =(const TGAColor &c) {
		if (this != &c) {
			bytespp = c.bytespp;
			val = c.val;
		}
		return *this;
	}
};

class TGAImage {
protected:
	unsigned char* data;
	int width;
	int height;
	int bytespp;

	bool   load_rle_data(std::ifstream &in);
	bool unload_rle_data(std::ofstream &out);
public:
	enum Format {
		GRAYSCALE=1, RGB=3, RGBA=4
	};

	TGAImage();
	TGAImage(int w, int h, int bpp);
	TGAImage(const TGAImage &img);
	bool read_tga_file(const char *filename);
	bool write_tga_file(const char *filename, bool rle=true);
	bool flip_horizontally();
	bool flip_vertically();
	bool scale(int w, int h);
	TGAColor get(int x, int y);
	bool set(int x, int y, TGAColor c);
	~TGAImage();
	TGAImage & operator =(const TGAImage &img);
	int get_width();
	int get_height();
	int get_bytespp();
	unsigned char *buffer();
	void clear();
};

#endif //__IMAGE_H__
