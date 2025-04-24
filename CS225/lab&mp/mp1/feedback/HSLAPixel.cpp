#include "HSLAPixel.h"

cs225::HSLAPixel::HSLAPixel()
{
	this->a = 1;
	this->l = 1;
}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance)
{
	this->h = hue;
	this->s = saturation;
	this->l = luminance;
	this->a = 1;
}

cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha)
{
	this->h = hue;
	this->s = saturation;
	this->l = luminance;
	this->a = alpha;
}