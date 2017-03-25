/**
	\file rasterizer.h
	\brief LightEngine 3D: Triangle rasterizer (textured and textured with alpha channel)
	\brief All platforms implementation
	\author Frederic Meslin (fred@fredslab.net)
	\twitter @marzacdev
	\website http://fredslab.net
	\copyright Frederic Meslin 2015 - 2017
	\version 1.0

	The MIT License (MIT)
	Copyright (c) 2017 Fr�d�ric Meslin

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


#ifndef LE_RASTERIZER_H
#define LE_RASTERIZER_H

#include "global.h"
#include "draw.h"
#include "geometry.h"
#include "trilist.h"

/*****************************************************************************/
class LeRasterizer
{
public:
	LeRasterizer(int width, int height);
	~LeRasterizer();

	void setBackground(uint32_t color);
	void rasterList(TriList * trilist);
	void flush();

	LeBitmap frame;

private:
	typedef struct {
		int32_t x[2];
		int32_t u[2];
		int32_t v[2];
	}ScanStr;

	void calcScans(int vt, int vb, int side);
	void fillScansFlatTex(int t, int b);
	void fillScansFlatTexAlpha(int t, int b);

	ScanStr * scansAlloc;
	ScanStr * scans;

	uint32_t color;
	uint32_t * texPixels;
	uint32_t texSizeU;
	uint32_t texSizeV;
	uint32_t texMaskU;
	uint32_t texMaskV;

	int32_t xs[4], ys[4];
	int32_t us[4], vs[4];

	uint32_t background;

};

#endif // LE_RASTERIZER_H
