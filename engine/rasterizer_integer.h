/**
	\file rasterizer_integer.h
	\brief LightEngine 3D: Triangle rasterizer (fixed point)
	\brief All platforms implementation
	\brief Support textured triangles
	\brief Textures can have an alpha channel and mipmaps
	\author Frederic Meslin (fred@fredslab.net)
	\twitter @marzacdev
	\website http://fredslab.net
	\copyright Frederic Meslin 2015 - 2018
	\version 1.6

	The MIT License (MIT)
	Copyright (c) 2017-2018 Fr�d�ric Meslin

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef LE_RASTERIZER_INTEGER_H
#define LE_RASTERIZER_INTEGER_H

#include "global.h"
#include "config.h"

#include "draw.h"
#include "geometry.h"
#include "trilist.h"

#if LE_USE_SIMD == 1
	#include "simd.h"
#endif

/*****************************************************************************/
/**
	\class LeRasterizer
	\brief Rasterize triangle lists
*/
class LeRasterizer
{
public:
	LeRasterizer(int width = LE_RESOX_DEFAULT, int height = LE_RESOY_DEFAULT);
	~LeRasterizer();

	void rasterList(LeTriList * trilist);
	const void * getPixels() {return pixels;}
	void flush();

	LeBitmap frame;				/**< Frame buffer */ 
	uint32_t background;		/**< Background color */ 
	
private:
	void topTriangleZC(int vt, int vm1, int vm2);
	void bottomTriangleZC(int vm1, int vm2, int vb);

	inline void fillFlatTexZC(int y, int x1, int x2, int w1, int w2, int u1, int u2, int v1, int v2);
	inline void fillFlatTexAlphaZC(int y, int x1, int x2, int w1, int w2, int u1, int u2, int v1, int v2);

	uint32_t color;
	LeBitmap * bmp;

	uint32_t * pixels;
	uint32_t * texPixels;
	uint32_t texSizeU;
	uint32_t texSizeV;
	uint32_t texMaskU;
	uint32_t texMaskV;

#if LE_USE_SIMD == 1 && LE_USE_SSE2 == 1
	__m128i color_4;
#endif // LE_USE_SIMD && LE_USE_SSE2

	int32_t xs[4], ys[4], ws[4];
	int32_t us[4], vs[4];
};

#endif // LE_RASTERIZER_INTEGER_H
