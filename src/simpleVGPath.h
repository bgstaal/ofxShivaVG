/*
 * ofxShivaVGRenderer
 * a 2d renderer for openFrameworks based on the ShivaVG library
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

#ifndef __ofxShivaVGRenderer__simpleVGPath__
#define __ofxShivaVGRenderer__simpleVGPath__

#include "openvg.h"

class simpleVGPath
{
	public:
    
		simpleVGPath();
    	~simpleVGPath();
    
	    VGPath getVGPath();
    
	    void close();
	    void ellipse(float x, float y, float w, float h);
	    void moveTo(float x, float y);
    	void lineTo(float x, float y);
	    void quadTo(float controlX, float controlY, float x, float y);
	    void cubicTo(float controlX1, float controlY1, float controlX2, float controlY2, float x, float y);
    	void arcCWTo(float rx, float ry, float rot, float x, float y);
        void arcCCWTo(float rx, float ry, float rot, float x, float y);
    
	private:
    
    	bool _hasPath;
    	VGPath _path;
    
};

#endif
