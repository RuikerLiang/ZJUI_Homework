#include "HSLAPixel.h"

cs225::HSLAPixel::HSLAPixel() {}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance)
{
	this->h = hue;
	this->s = saturation;
	this->l = luminance;
}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha)
{
	this->h = hue;
	this->s = saturation;
	this->l = luminance;
	this->a = alpha;
}