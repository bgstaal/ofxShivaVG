/*
 * ofxShivaVGRenderer
 * A 2d renderer for openFrameworks based on the ShivaVG library
 * by Bjørn Gunnar Staal
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library in the file COPYING;
 * if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef __ofxShivaVGRenderer__SimpleVG__
#define __ofxShivaVGRenderer__SimpleVG__

#include "openvg.h"
#include "simpleVGPath.h"

class simpleVGContext
{
    public:
        simpleVGContext();
        ~simpleVGContext();
    
		void create(VGint w, VGint h);
    
		void setFillColor(VGint r, VGint g, VGint b, VGint a);
		void setFillColor(VGfloat r, VGfloat g, VGfloat b, VGfloat a);
		void setStrokeWidth(VGfloat w);
		void setStrokeCapStyle(VGCapStyle cap);
		void setStrokeJoinStyle(VGJoinStyle join);
		void setStrokeColor(VGint r, VGint g, VGint b, VGint a);
		void setStrokeColor(VGfloat r, VGfloat g, VGfloat b, VGfloat a);
		VGfloat getStrokeWidth();
		VGCapStyle getStrokeCapStyle();
		VGJoinStyle getStrokeJoinStyle();
    
		void fillPath(simpleVGPath &path);
		void strokePath(simpleVGPath &path);
    
	private:
    
		bool _hasContext;
		VGPaint _fillPaint = 0;
		VGPaint _strokePaint = 0;
		VGfloat _strokeWidth;
		VGCapStyle _strokeCapStyle;
		VGJoinStyle _strokeJoinStyle;
};

#endif
