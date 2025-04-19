#include "StickerSheet.h"
cs225::ImageInfo::ImageInfo(Image* Image, unsigned x_index, unsigned y_index)
{
	img = Image;
	x_idx = x_index;
	y_idx = y_index;
}
void cs225::ImageInfo::_copy(const cs225::ImageInfo& other)
{
	img = other.img;
	x_idx = other.x_idx;
	y_idx = other.y_idx;
}
cs225::StickerSheet::StickerSheet(const Image& picture, unsigned max)
{
	imageList = new ImageInfo[max];
	_base = &picture;
	for (unsigned i = 0; i < max; ++i)
		imageList[i] = ImageInfo(nullptr, -1, -1);
	_max = max;
}
void cs225::StickerSheet::_copy(const StickerSheet &other)
{
	_max = other._max;
	if (imageList != nullptr)
		delete[] imageList;
	imageList = new ImageInfo[_max];
	for (unsigned i = 0; i < _max; ++i)
		imageList[i]._copy(other.imageList[i]);
}
cs225::StickerSheet::StickerSheet(const StickerSheet &other)
{
	_copy(other);
}
cs225::StickerSheet::~StickerSheet()
{
	delete imageList;
}
const cs225::StickerSheet& cs225::StickerSheet::operator= (const StickerSheet &other)
{
	_copy(other);
	return *this;
}
void cs225::StickerSheet::changeMaxStickers(unsigned max)
{
	cs225::ImageInfo* tmp = new cs225::ImageInfo[max];
	for (unsigned i = 0; i < min(max, this->_max); ++i)
		tmp[i]._copy(imageList[i]);
	for (unsigned i = this->_max; i < max; ++i)
		tmp[i] = ImageInfo(nullptr, -1, -1);
	delete[] imageList;
	_max = max;
	imageList = tmp;
}
int cs225::StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
	for (unsigned i = 0; i < _max; ++i)
		if (imageList[i].img == nullptr)
		{
			imageList[i] = ImageInfo(&sticker, x, y);
			return i;
		}
	return -1;
}
bool cs225::StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
	if (imageList[index].img == nullptr)
		return false;
	imageList[index].x_idx = x, imageList[index].y_idx = y;
	return true;
}
void cs225::StickerSheet::removeSticker(unsigned index)
{
	imageList[index] = ImageInfo(nullptr, -1, -1);
}
cs225::Image* cs225::StickerSheet::getSticker(unsigned index) const
{
	if (imageList[index].img == nullptr)
		return NULL;
	return imageList[index].img;
}
void cs225::StickerSheet::_draw(Image* res, ImageInfo &img_info) const
{
	unsigned w = img_info.img->width(), h = img_info.img->height();
	for (unsigned i = 0; i < w; ++i)
		for (unsigned j = 0; j < h; ++j)
		{
			cs225::HSLAPixel* pix = img_info.img->getPixel(i, j);
			if (pix->a == 0)
				continue;
			cs225::HSLAPixel* org_pix = res->getPixel(i + img_info.x_idx, j + img_info.y_idx);
			org_pix->a = pix->a, org_pix->h = pix->h, org_pix->l = pix->l, org_pix->s = pix->s;
		}
}
cs225::Image cs225::StickerSheet::render() const
{
	Image res = *_base;
	unsigned x_max = _base->width(), y_max = _base->height();
	for (unsigned i = 0; i < _max; ++i)
	{
		if (imageList[i].img == nullptr)
			continue;
		unsigned x_tmp = imageList[i].img->width() + imageList[i].x_idx;
		unsigned y_tmp = imageList[i].img->height() + imageList[i].y_idx;
		x_max = max(x_max, x_tmp), y_max = max(y_max, y_tmp);
	}
	res.resize(x_max, y_max);
	for (unsigned i = 0; i < _max; ++i)
		if (imageList[i].img != nullptr)
			_draw(&res, imageList[i]);
	return res;
}