#include "Image.h"
void cs225::Image::lighten()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->l += 0.1;
			if (pix->l < 0)
				pix->l = 0;
			if (pix->l > 1)
				pix->l = 1;
		}
}
void cs225::Image::lighten(double amount)
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->l += amount;
			if (pix->l < 0)
				pix->l = 0;
			if (pix->l > 1)
				pix->l = 1;
		}
}
void cs225::Image::darken()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->l -= 0.1;
			if (pix->l < 0)
				pix->l = 0;
			if (pix->l > 1)
				pix->l = 1;
		}
}
void cs225::Image::darken(double amount)
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->l -= amount;
			if (pix->l < 0)
				pix->l = 0;
			if (pix->l > 1)
				pix->l = 1;
		}
}
void cs225::Image::saturate()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->s += 0.1;
			if (pix->s < 0)
				pix->s = 0;
			if (pix->s > 1)
				pix->s = 1;
		}
}
void cs225::Image::saturate(double amount)
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->s += amount;
			if (pix->s < 0)
				pix->s = 0;
			if (pix->s > 1)
				pix->s = 1;
		}
}
void cs225::Image::desaturate()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->s -= 0.1;
			if (pix->s < 0)
				pix->s = 0;
			if (pix->s > 1)
				pix->s = 1;
		}
}
void cs225::Image::desaturate(double amount)
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->s -= amount;
			if (pix->s < 0)
				pix->s = 0;
		}
}
void cs225::Image::grayscale ()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->h = 0;
		}
}
void cs225::Image::rotateColor (double degrees)
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			pix->h = (pix->h + degrees);
			if (pix->h > 360)
				pix->h = pix->h - 360;
			if (pix->h < 0)
				pix->h = pix->h + 360;
		}
}
void cs225::Image::illinify ()
{
	unsigned w = width(), h = height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			HSLAPixel* pix = getPixel(i, j);
			double diso = min((pix->h - 11) * (pix->h - 11), (pix->h - 371) * (pix->h - 371)),
						 disb = min((pix->h - 216) * (pix->h - 216), (pix->h + 360 - 216) * (pix->h + 360 - 216));
			if (diso < disb)
				pix->h = 216;
			else
				pix->h = 11;
		}
}
void cs225::Image::scale (double factor)
{
	unsigned w = width(), h = height();
	unsigned new_w = factor * w, new_h = factor * h;
	cs225::PNG org_img = *this;
	resize(new_w, new_h);
	for (unsigned i = 0; i < new_w; ++i)
		for (unsigned j = 0; j < new_h; ++j)
		{
			unsigned org_i = i / factor, org_j = j / factor;
			HSLAPixel* pix = this->getPixel(i, j), *org_pix = org_img.getPixel(org_i, org_j);
			*pix = *org_pix;
		}
}
void cs225::Image::scale (unsigned w, unsigned h)
{
	unsigned org_w = width(), org_h = height();
	double factor_w = w / org_w, factor_h = h / org_h;
	cs225::PNG org_img = *this;
	resize(w, h);
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			unsigned org_i = i / factor_w, org_j = j / factor_h;
			HSLAPixel* pix = this->getPixel(i, j), *org_pix = org_img.getPixel(org_i, org_j);
			*pix = *org_pix;
		}
	resize(w, h);
}