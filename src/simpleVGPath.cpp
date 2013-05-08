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

#include "simpleVGPath.h"
#include "vgu.h"


simpleVGPath::simpleVGPath ()
:_hasPath(false)
{
    _path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1,0,0,0, VG_PATH_CAPABILITY_ALL);
    _hasPath = true;
}

VGPath simpleVGPath::getVGPath()
{
    return _path;
}

simpleVGPath::~simpleVGPath()
{
    vgDestroyPath(_path);
}

void simpleVGPath::ellipse(float x, float y, float w, float h)
{
    vguEllipse(_path, x, y, w, h);
}

void simpleVGPath::moveTo(float x, float y)
{
    VGubyte seg = VG_MOVE_TO | VG_ABSOLUTE;
    float data[2];
    
    data[0] = x; data[1] = y;
    vgAppendPathData(_path, 1, &seg, data);
}


void simpleVGPath::lineTo(float x, float y)
{
    VGubyte seg = VG_LINE_TO | VG_ABSOLUTE;
    float data[2];
    
    data[0] = x; data[1] = y;
    vgAppendPathData(_path, 1, &seg, data);
}

void simpleVGPath::quadTo(float controlX, float controlY, float x, float y)
{
    VGubyte seg = VG_QUAD_TO | VG_ABSOLUTE;
    float data[4];
    
    data[0] = controlX; data[1] = controlY;
    data[2] = x; data[3] = y;
    vgAppendPathData(_path, 1, &seg, data);
}

void simpleVGPath::cubicTo(float controlX1, float controlY1, float controlX2, float controlY2, float x, float y)
{
    VGubyte seg = VG_CUBIC_TO | VG_ABSOLUTE;
    float data[6];
    
    data[0] = controlX1; data[1] = controlY1;
    data[2] = controlX2; data[3] = controlY2;
    data[4] = x; data[5] = y;
    vgAppendPathData(_path, 1, &seg, data);
}	

void simpleVGPath::close()
{
    VGubyte seg = VG_CLOSE_PATH;
    float data = 0.0f;
    vgAppendPathData(_path, 1, &seg, &data);
}

/*
void simpleVGPath::ArcTo(float rx, float ry, float rot, float x, float y,
               VGPathSegment type, VGPathAbsRel absrel)
{
    VGubyte seg = type | absrel;
    float data[5];
    
    data[0] = rx; data[1] = ry;
    data[2] = rot;
    data[3] = x;  data[4] = y;
    vgAppendPathData(p, 1, &seg, data);
}
 */



/*

void testSquadTo(VGPath p, float x2, float y2,VGPathAbsRel absrel)
{
    VGubyte seg = VG_SQUAD_TO | absrel;
    float data[2];
    
    data[0] = x2; data[1] = y2;
    vgAppendPathData(p, 1, &seg, data);
}

void testScubicTo(VGPath p, float x2, float y2, float x3, float y3,
                  VGPathAbsRel absrel)
{
    VGubyte seg = VG_SCUBIC_TO | absrel;
    float data[4];
    
    data[0] = x2; data[1] = y2;
    data[2] = x3; data[3] = y3;
    vgAppendPathData(p, 1, &seg, data);
}

void testArcTo(VGPath p, float rx, float ry, float rot, float x, float y,
               VGPathSegment type, VGPathAbsRel absrel)
{
    VGubyte seg = type | absrel;
    float data[5];
    
    data[0] = rx; data[1] = ry;
    data[2] = rot;
    data[3] = x;  data[4] = y;
    vgAppendPathData(p, 1, &seg, data);
}
 */
