#include <string>
#include "cs225/PNG.h"
typedef cs225::PNG PNG;
typedef cs225::HSLAPixel HSLAPixel;

void rotate(std::string inputFile, std::string outputFile) {
	PNG input_png;
	input_png.readFromFile(inputFile);
	unsigned w = input_png.width(), h = input_png.height();
	PNG output_png = PNG(w, h);
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix_in = input_png.getPixel(i, j), *pix_out = output_png.getPixel(w - 1 - i, h - 1 - j);
			pix_out->a = pix_in->a, pix_out->h = pix_in->h, pix_out->l = pix_in->l, pix_out->s = pix_in->s;
		}
	/*
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h / 2; ++j)
		{
			HSLAPixel* pix1 = png.getPixel(i, j), *pix2 = png.getPixel(w - 1 - i, h - 1 - j);
			HSLAPixel tmp(pix1->h, pix1->s, pix1->l, pix1->a);
			pix1->h = pix2->h, pix1->s = pix2->s, pix1->l = pix2->l, pix1->a = pix2->a;
			pix2->h = tmp.h, pix2->s = tmp.s, pix2->l = tmp.l, pix2->a = tmp.a;
			//pix1->h = 0;
		}
	if (h % 2 == 1)
	{
		unsigned row = h / 2;
		for (unsigned i = 0; i < w; ++i)
		{
			HSLAPixel* pix1 = png.getPixel(i, row), *pix2 = png.getPixel(w - 1 - i, row);
			HSLAPixel tmp(pix1->h, pix1->s, pix1->l, pix1->a);
			pix1->h = pix2->h, pix1->s = pix2->s, pix1->l = pix2->l, pix1->a = pix2->a;
			pix2->h = tmp.h, pix2->s = tmp.s, pix2->l = tmp.l, pix2->a = tmp.a;
		}
	}
		*/
	output_png.writeToFile(outputFile);
}