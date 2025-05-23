#ifndef IMAGE_H
#define IMAGE_H
#include "cs225/PNG.h"
namespace cs225{
	class Image : public PNG
	{
	public:
		void lighten();
		void lighten(double amount);
		void darken();
		void darken(double amount);
		void saturate();
		void saturate(double amount);
		void desaturate();
		void desaturate(double amount);
		void grayscale ();
		void rotateColor (double degrees);
		void illinify ();
		void scale (double factor);
		void scale (unsigned w, unsigned h);
	};
}
#endif