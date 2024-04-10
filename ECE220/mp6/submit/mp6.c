#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "mp6.h"
//
// extract_watermark -- Given a file containing eight watermark images, 
//                      extract the image corresponding to a given bit (0 to 7)
//                      and write it into the output image using only values 0/255.
// INPUTS: width -- width of both input and output channels
//         height -- height of both input and output channels
//         data -- watermark image red channel
//         bit -- bit to extract from input (0 to 7)
// OUTPUT: output -- output image red channel (copied by calling code to green 
//                   and blue to make a black and white image)
// NOTES: bit 0 means value 1, bit 1 means value 2, and so forth.  Extract the bit
//        from the input array using a bitwise AND.  Write only 0/255 into each
//        output pixel, depending on whether the bit is clear/set, respectively,
//        in the data.
//
void 
extract_watermark (int32_t width, int32_t height, const uint8_t* data, int32_t bit, uint8_t* output)
{
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
		{
			int32_t index = i + j * width;
			if (data[index] & (1 << bit))
				output[index] = 255;
			else
				output[index] = 0;
		}
}

//
// add_watermark -- Given the red channel for an image and a watermark image, scale
//                  the watermark and then apply it to each pixel in the image 
//                  (replace bit 0 in each pixel, and set those outside the scaled
//                  watermark to 0).
// INPUTS: width -- width of input channel
//         height -- height of input channel
//         data -- image red channel to which watermark should be applied
//         markwidth -- width of watermark
//         markheight -- height of watermark
//         watermark -- watermark image data
// OUTPUT: output -- output image red channel (image green and blue channels remain untouched)
// NOTES: the watermark data are produced by calling extract_watermark, so be sure that your
//        implementation of that function is correct before trying to debug this function
//
void 
add_watermark (int32_t width, int32_t height, const uint8_t* data, 
	       int32_t markwidth, int32_t markheight, const uint8_t* watermark, uint8_t* output)
{
	int32_t scale_w = width / markwidth, scale_h = height / markheight;
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			output[i + j * width] = data[i + j * width] ^ (data[i + j * width] & 1);
	for (int i = 0; i < scale_w * markwidth; ++i)
		for (int j = 0; j < scale_h * markheight; ++j)
		{
			int32_t index = i + j * width, marki = i / scale_w, markj = j / scale_h, markindex = marki + markj * markwidth;
			if (watermark[markindex])
				output[index] = data[index] | 1;
			else
				output[index] = data[index] ^ (data[index] & 1);
		}
}
//
// reconstruct_watermark -- Reconstruct a watermark from an image.  First, compute the scale
//                          factors for the watermark (based on the image sizes), then
//                          count the number of 1s in bit 0 of pixels in each rectangular
//                          region corresponding to a watermark pixel.  If the count is at
//                          least half the number of pixels in the rectangle, set the 
//                          watermark pixel to 255.  If not, set it to 0.
// INPUTS: width -- width of input channel
//         height -- height of input channel
//         data -- image red channel from which watermark should be reconstructed
//         markwidth -- width of watermark
//         markheight -- height of watermark
// OUTPUT: output -- output watermark image red channel (copied by calling code to green 
//                   and blue to make a black and white image)
// NOTES: the watermark image passed into the main code is used only to size the watermark; the
//        data in that file are not provided to this function
void 
reconstruct_watermark (int32_t width, int32_t height, const uint8_t* data, 
	       	       int32_t markwidth, int32_t markheight, uint8_t* output)
{
	int scale_w = width / markwidth, scale_h = height / markheight;
	for (int i = 0; i < markwidth; ++i)
		for (int j = 0; j < markheight; ++j)
		{
			int cnt[2] = { 0, 0 };
			for (int x = i * scale_w; x < (i + 1) * scale_w; ++x)
				for (int y = j * scale_h; y < (j + 1) * scale_h; ++y)
					cnt[data[x + y * width] & 1]++;
			output[i + j * markwidth] = (cnt[1] >= cnt[0]) * 255;
		}
}
