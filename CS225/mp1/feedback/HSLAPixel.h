#ifndef HSLAPIXEL_H
#define HSLAPIXEL_H

namespace cs225
{
	class HSLAPixel
	{
	public:
		HSLAPixel();
		HSLAPixel(double, double, double);
		HSLAPixel(double, double, double, double);
		double h, s, l, a;
	};
}

#endif