#ifndef STICKERSHEET_H
#define STICKERSHEET_H
#include "Image.h"
namespace cs225
{
	struct ImageInfo
	{
		ImageInfo(Image* Image = nullptr, unsigned x_index = 0, unsigned y_index = 0);
		void _copy(const ImageInfo& other);
		Image* img;
		unsigned x_idx, y_idx;
	};
	class StickerSheet
	{
	public:
		StickerSheet(const Image& picture, unsigned max);
		StickerSheet (const StickerSheet &other);
		~StickerSheet();
		const StickerSheet& operator= (const StickerSheet &other);
		void changeMaxStickers (unsigned max);
		int addSticker (Image &sticker, unsigned x, unsigned y);
		bool translate (unsigned index, unsigned x, unsigned y);
		void removeSticker (unsigned index);
		Image *getSticker (unsigned index) const;
		Image render () const;

		void _copy(const StickerSheet &other);
		void _draw(Image* res, ImageInfo &img_info) const;

		ImageInfo* imageList = nullptr;
		const Image* _base;
		unsigned _max;
	};
} // namespace cs225
#endif