/*
 * Copyright (c) 2007 Ivan Leben
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

#define VG_API_EXPORT
#include "openvg.h"
#include "vgu.h"
#include "shDefs.h"
#include "shContext.h"
#include <math.h>

static VGUErrorCode shAppend(VGPath path, SHint commSize, const VGubyte *comm,
                             SHint dataSize, const VGfloat *data)
{
  VGErrorCode err = VG_NO_ERROR;
  VGfloat typeFloat = vgGetParameterf(path, VG_PATH_DATATYPE);
  // How to cast VGfloat to VGPathDatatype?
  VGPathDatatype type = VG_PATH_DATATYPE_S_8;   // Hack so it compiles
  VGfloat scale = vgGetParameterf(path, VG_PATH_SCALE);
  VGfloat bias = vgGetParameterf(path, VG_PATH_BIAS);
  SH_ASSERT(dataSize <= 26);
  
  switch(type)
  {
  case VG_PATH_DATATYPE_S_8: {
      
      SHint8 data8[26]; int i;
      for (i=0; i<dataSize; ++i)
        data8[i] = (SHint8)SH_FLOOR((data[i] - bias) / scale + 0.5f);
      vgAppendPathData(path, commSize, comm, data8);
      
      break;}
  case VG_PATH_DATATYPE_S_16: {
      
      SHint16 data16[26]; int i;
      for (i=0; i<dataSize; ++i)
        data16[i] = (SHint16)SH_FLOOR((data[i] - bias) / scale + 0.5f);
      vgAppendPathData(path, commSize, comm, data16);
      
      break;}
  case VG_PATH_DATATYPE_S_32: {
      
      SHint32 data32[26]; int i;
      for (i=0; i<dataSize; ++i)
        data32[i] = (SHint32)SH_FLOOR((data[i] - bias) / scale + 0.5f);
      vgAppendPathData(path, commSize, comm, data32);
      
      break;}
  default: {
      
      VGfloat dataF[26]; int i;
      for (i=0; i<dataSize; ++i)
        dataF[i] = (data[i] - bias) / scale;
      vgAppendPathData(path, commSize, comm, dataF);
      
      break;}
  }
  
  err = vgGetError();
  if (err == VG_PATH_CAPABILITY_ERROR)
    return VGU_PATH_CAPABILITY_ERROR;
  else if (err == VG_BAD_HANDLE_ERROR)
    return VGU_BAD_HANDLE_ERROR;
  else if (err == VG_OUT_OF_MEMORY_ERROR)
    return VGU_OUT_OF_MEMORY_ERROR;
  
  return VGU_NO_ERROR;
}

VGU_API_CALL VGUErrorCode vguLine(VGPath path,
                                  VGfloat x0, VGfloat y0,
                                  VGfloat x1, VGfloat y1)
{
  VGUErrorCode err = VGU_NO_ERROR;
  const VGubyte comm[] = {VG_MOVE_TO_ABS, VG_LINE_TO_ABS};
  
  VGfloat data[4];
  data[0] = x0; data[1] = y0;
  data[2] = x1; data[3] = y1;
  
  err = shAppend(path, 2, comm, 4, data);
  return err;
}

VGU_API_CALL VGUErrorCode vguPolygon(VGPath path,
                                     const VGfloat * points, VGint count,
                                     VGboolean closed)
{
  VGint i;
  VGubyte *comm = NULL;
  VGUErrorCode err = VGU_NO_ERROR;
  
  if (points == NULL || count <= 0)
    return VGU_ILLEGAL_ARGUMENT_ERROR;
  /* TODO: check points array alignment */
  
  comm = (VGubyte*)malloc( (count+1) * sizeof(VGubyte) );
  if (comm == NULL) return VGU_OUT_OF_MEMORY_ERROR;
  
  comm[0] = VG_MOVE_TO_ABS;
  for (i=1; i<count; ++i)
    comm[i] = VG_LINE_TO_ABS;
  comm[count] = VG_CLOSE_PATH;
  
  if (closed) err = shAppend(path, count+1, comm, count*2, points);
  else        err = shAppend(path, count, comm, count*2, points);
  
  free(comm);
  return err;
}

VGU_API_CALL VGUErrorCode vguRect(VGPath path,
                                  VGfloat x, VGfloat y,
                                  VGfloat width, VGfloat height)
{
  VGUErrorCode err = VGU_NO_ERROR;
  
  VGubyte comm[5] = {
    VG_MOVE_TO_ABS, VG_HLINE_TO_REL,
    VG_VLINE_TO_REL, VG_HLINE_TO_REL,
    VG_CLOSE_PATH };
  
  VGfloat data[5];
  
  if (width <= 0 || height <= 0)
    return VGU_ILLEGAL_ARGUMENT_ERROR;
  
  data[0] =  x;     data[1] = y;
  data[2] =  width; data[3] = height;
  data[4] = -width;
  
  err = shAppend(path, 5, comm, 5, data);
  return err;
}

VGU_API_CALL VGUErrorCode vguRoundRect(VGPath path,
                                       VGfloat x, VGfloat y,
                                       VGfloat width, VGfloat height,
                                       VGfloat arcWidth, VGfloat arcHeight)
{
  VGUErrorCode err = VGU_NO_ERROR;
  
  VGubyte comm[10] = {
    VG_MOVE_TO_ABS,
    VG_HLINE_TO_REL, VG_SCCWARC_TO_REL,
    VG_VLINE_TO_REL, VG_SCCWARC_TO_REL,
    VG_HLINE_TO_REL, VG_SCCWARC_TO_REL,
    VG_VLINE_TO_REL, VG_SCCWARC_TO_REL,
    VG_CLOSE_PATH };
  
  VGfloat data[26];
  VGfloat rx, ry;
  
  if (width <= 0 || height <= 0)
    return VGU_ILLEGAL_ARGUMENT_ERROR;
  
  SH_CLAMP(arcWidth, 0.0f, width);
  SH_CLAMP(arcHeight, 0.0f, height);
  rx = arcWidth/2;
  ry = arcHeight/2;
  
  data[0]  =  x + rx; data[1] = y;
  
  data[2]  =  width - arcWidth;
  data[3]  =  rx; data[4]  =  ry; data[5]  = 0;
  data[6]  =  rx; data[7]  =  ry;
  
  data[8]  =  height - arcHeight;
  data[9]  =  rx; data[10] =  ry; data[11] = 0;
  data[12] = -rx; data[13] =  ry;
  
  data[14] = -(width - arcWidth);
  data[15] =  rx; data[16] =  ry; data[17] = 0;
  data[18] = -rx; data[19] = -ry;
  
  data[20] = -(height - arcHeight);
  data[21] =  rx; data[22] =  ry; data[23] = 0;
  data[24] =  rx; data[25] = -ry;
  
  err = shAppend(path, 10, comm, 26, data);
  return err;
}

VGU_API_CALL VGUErrorCode vguEllipse(VGPath path,
                                     VGfloat cx, VGfloat cy,
                                     VGfloat width, VGfloat height)
{
  VGUErrorCode err = VGU_NO_ERROR;
  
  const VGubyte comm[] = {
    VG_MOVE_TO_ABS, VG_SCCWARC_TO_REL,
    VG_SCCWARC_TO_REL, VG_CLOSE_PATH};
  
  VGfloat data[12];
  
  if (width <= 0 || height <= 0)
    return VGU_ILLEGAL_ARGUMENT_ERROR;
  
  data[0] = cx + width/2; data[1] = cy;
  
  data[2] = width/2; data[3] = height/2; data[4] = 0;
  data[5] = -width; data[6] = 0;
  
  data[7] = width/2; data[8] = height/2; data[9] = 0;
  data[10] = width; data[11] = 0;
  
  err = shAppend(path, 4, comm, 12, data);
  return err;
}

#include <stdio.h>

VGU_API_CALL VGUErrorCode vguArc(VGPath path,
                                 VGfloat x, VGfloat y,
                                 VGfloat width, VGfloat height,
                                 VGfloat startAngle, VGfloat angleExtent,
                                 VGUArcType arcType)
{
  VGUErrorCode err = VGU_NO_ERROR;
  
  VGubyte commStart[1] = {VG_MOVE_TO_ABS};
  VGfloat dataStart[2];
  
  VGubyte commArcCCW[1] = {VG_SCCWARC_TO_ABS};
  VGubyte commArcCW[1]  = {VG_SCWARC_TO_ABS};
  VGfloat dataArc[5];
  
  VGubyte commEndPie[2] = {VG_LINE_TO_ABS, VG_CLOSE_PATH};
  VGfloat dataEndPie[2];
  
  VGubyte commEndChord[1] = {VG_CLOSE_PATH};
  VGfloat dataEndChord[1] = {0.0f};
  
  VGfloat alast, a = 0.0f;
  VGfloat rx = width/2, ry = height/2;
  
  if (width <= 0 || height <= 0)
    return VGU_ILLEGAL_ARGUMENT_ERROR;
  
  if (arcType != VGU_ARC_OPEN &&
      arcType != VGU_ARC_CHORD &&
      arcType != VGU_ARC_PIE)
      return VGU_ILLEGAL_ARGUMENT_ERROR;
  
  startAngle = SH_DEG2RAD(startAngle);
  angleExtent = SH_DEG2RAD(angleExtent);
  alast = startAngle + angleExtent;
  
  dataStart[0] = x + SH_COS(startAngle) * rx;
  dataStart[1] = y + SH_SIN(startAngle) * ry;
  err = shAppend(path, 1, commStart, 2, dataStart);
  if (err != VGU_NO_ERROR) return err;
  
  dataArc[0] = rx;
  dataArc[1] = ry;
  dataArc[2] = 0.0f;
  
  if (angleExtent > 0) {
    
    a = startAngle + PI;
    while (a < alast) {
      dataArc[3] = x + SH_COS(a) * rx;
      dataArc[4] = y + SH_SIN(a) * ry;
      err = shAppend(path, 1, commArcCCW, 5, dataArc);
      if (err != VGU_NO_ERROR) return err;
      a += PI; }
    
    dataArc[3] = x + SH_COS(alast) * rx;
    dataArc[4] = y + SH_SIN(alast) * ry;
    err = shAppend(path, 1, commArcCCW, 5, dataArc);
    if (err != VGU_NO_ERROR) return err;
    
  }else{
    
    a = startAngle - PI;
    while (a > alast) {
      dataArc[3] = x + SH_COS(a) * rx;
      dataArc[4] = y + SH_SIN(a) * ry;
      err = shAppend(path, 1, commArcCW, 5, dataArc);
      if (err != VGU_NO_ERROR) return err;
      a -= PI; }
    
    dataArc[3] = x + SH_COS(alast) * rx;
    dataArc[4] = y + SH_SIN(alast) * ry;
    err = shAppend(path, 1, commArcCW, 5, dataArc);
    if (err != VGU_NO_ERROR) return err;
  }
  
  
  if (arcType == VGU_ARC_PIE) {
    dataEndPie[0] = x; dataEndPie[1] = y;
    err = shAppend(path, 2, commEndPie, 2, dataEndPie);
  }else if (arcType == VGU_ARC_CHORD) {
    err = shAppend(path, 1, commEndChord, 0, dataEndChord);
  }
  
  return err;
}

VGU_API_CALL VGUErrorCode vguComputeWarpQuadToSquare(VGfloat sx0, VGfloat sy0,
                                                    VGfloat sx1, VGfloat sy1,
                                                    VGfloat sx2, VGfloat sy2,
                                                    VGfloat sx3, VGfloat sy3,
                                                    VGfloat * matrix)
{
  return VGU_NO_ERROR;
}

VGU_API_CALL VGUErrorCode vguComputeWarpSquareToQuad(VGfloat dx0, VGfloat dy0,
                                                    VGfloat dx1, VGfloat dy1,
                                                    VGfloat dx2, VGfloat dy2,
                                                    VGfloat dx3, VGfloat dy3,
                                                    VGfloat * matrix)
{
  return VGU_NO_ERROR;
}

VGU_API_CALL VGUErrorCode vguComputeWarpQuadToQuad(VGfloat dx0, VGfloat dy0,
                                                  VGfloat dx1, VGfloat dy1,
                                                  VGfloat dx2, VGfloat dy2,
                                                  VGfloat dx3, VGfloat dy3,
												                          VGfloat sx0, VGfloat sy0,
                                                  VGfloat sx1, VGfloat sy1,
                                                  VGfloat sx2, VGfloat sy2,
                                                  VGfloat sx3, VGfloat sy3,
                                                  VGfloat * matrix)
{
  return VGU_NO_ERROR;
}
