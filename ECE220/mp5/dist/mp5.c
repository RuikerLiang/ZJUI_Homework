/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp5.h
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */
#include "mp5.h"
#include <stdio.h>

/*
	You must write all your code only in this file, for all the functions!
*/



/* 
 *  near_horizontal
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t ret = 1;
	if (x_start > x_end)
	{
		int tmp = x_end;
		x_end = x_start;
		x_start = tmp;

		tmp = y_end;
		y_end = y_start;
		y_start = tmp;
	}
	for (int i = x_start; i <= x_end; ++i)
	{
		int sgn = 0;
		if (y_end > y_start)
			sgn = 1;
		int32_t yi = (2 * (y_end - y_start) * (i - x_start) + (x_end - x_start) * sgn) / (2 * (x_end - x_start)) + y_start;
		ret = ret & draw_dot(i, yi);
	}
	return ret;
}


/* 
 *  near_vertical
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t ret = 1;
	if (y_start > y_end)
	{
		int tmp = x_end;
		x_end = x_start;
		x_start = tmp;

		tmp = y_end;
		y_end = y_start;
		y_start = tmp;
	}
	for (int i = y_start; i <= y_end; ++i)
	{
		int sgn = 0;
		if (x_end > x_start)
			sgn = 1;
		int32_t xi = (2 * (x_end - x_start) * (i - y_start) + (y_end - y_start) * sgn) / (2 * (y_end - y_start)) + x_start;
		ret = ret & draw_dot(xi, i);
	}
	return ret;
}

/* 
 *  draw_line
 *	 
 *	 
 *	
 *	
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t ret = 1;
	if (x_start == x_end && y_start == y_end)
	{
		ret = ret & draw_dot(x_start, y_start);
		return ret;
	}
	else if (x_start == x_end)
	{
		ret = ret & near_vertical(x_start, y_start, x_end, y_end);
		return ret;
	}
	double slope = (double)(y_end - y_start) / (x_end - x_start);
	if (-1 <= slope && slope <= 1)
		ret = ret & near_horizontal(x_start, y_start, x_end, y_end);
	else
		ret = ret & near_vertical(x_start, y_start, x_end, y_end);
	return ret;
}


/* 
 *  draw_rect
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	/* Your code goes here! */
	if (w < 0 || h < 0)
		return 0;
	int32_t ret = 1;
	ret = ret & draw_line(x, y, x + w, y);
	ret = ret & draw_line(x, y, x, y + h);
	ret = ret & draw_line(x + w, y, x + w, y + h);
	ret = ret & draw_line(x, y + h, x + w, y + h);
	return ret;
}


/* 
 *  draw_triangle
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int32_t ret = 1;
	ret = ret & draw_line(x_A, y_A, x_B, y_B);
	ret = ret & draw_line(x_B, y_B, x_C, y_C);
	ret = ret & draw_line(x_A, y_A, x_C, y_C);
	return ret;
}

/* 
 *  draw_parallelogram
 *	 
 *	 
 *	
 *	
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	int32_t ret = 1;
	int32_t x_D = x_C - x_B + x_A, y_D = y_C - y_B + y_A;
	ret = ret & draw_line(x_B, y_B, x_A, y_A);
	ret = ret & draw_line(x_C, y_C, x_B, y_B);
	ret = ret & draw_line(x_D, y_D, x_A, y_A);
	ret = ret & draw_line(x_D, y_D, x_C, y_C);
	return ret;
}


/* 
 *  draw_circle
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
	/* Your code goes here!*/
	if (inner_r < 0)
		return 0;
	if (outer_r < inner_r)
		return 0;
	int32_t ret = 1;
	for (int delta_x = 0; delta_x <= outer_r; ++delta_x)
	{
		for (int delta_y = 0; delta_y * delta_y + delta_x * delta_x <= outer_r * outer_r; ++delta_y)
		{
			if (delta_x * delta_x + delta_y * delta_y < inner_r * inner_r)
				continue;
			ret = ret & draw_dot(x + delta_x, y + delta_y);
			ret = ret & draw_dot(x + delta_x, y - delta_y);
			ret = ret & draw_dot(x - delta_x, y + delta_y);
			ret = ret & draw_dot(x - delta_x, y - delta_y);
		}
	}
	return ret;
}


/* 
 *  rect_gradient
 *	 
 *	 
 *	
 *	
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
	if (h < 0 || w < 1)
		return 0;
	int32_t ret = 1;
	int32_t start_level[3], end_level[3];
		for (int i = 0; i < 3; ++i)
			start_level[i] = (255 << (i * 8)) & start_color,
			end_level[i] = (255 << (i * 8)) & end_color,
			start_level[i] = start_level[i] >> (i * 8),
			end_level[i] = end_level[i] >> (i * 8);
	for (int i = 0; i <= w; ++i)
	{
		int32_t current_level[3], current_color = 0;
		for (int j = 0; j < 3; ++j)
		{
			int32_t sgn = 0;
			if (end_level[j] - start_level[j] > 0)
				sgn = 1;
			else if (end_level[j] - start_level[j] < 0)
				sgn = -1;
			current_level[j] = (2 * i * (end_level[j] - start_level[j]) + w * sgn) / (2 * w) + start_level[j];
			current_color = current_color | (current_level[j] << (j * 8));
		}
		set_color(current_color);
		ret = ret & draw_line(x + i, y, x + i, y + h);
	}
	return ret;
}


/* 
 *  draw_picture
 *	 
 *	 
 *	
 *	
 * INPUTS: none
 * OUTPUTS: alters the image by calling any of the other functions in the file
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
draw_picture(){
	/* Your code goes here! */


	return 0;
}
