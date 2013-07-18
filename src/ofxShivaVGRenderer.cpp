/*
 * ofxShivaVG
 * A 2d rendering library for openFrameworks, based on the ShivaVG library
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

#include "ofxShivaVGRenderer.h"
#include "vgu.h"
#include "simpleVGPath.h"

// TODO: Implement resize!

ofxShivaVGRenderer::ofxShivaVGRenderer ()
{
   	_vg.create(ofGetWidth(), ofGetHeight());
}

void ofxShivaVGRenderer::setLineCapStyle(VGCapStyle cap)
{
    _vg.setStrokeCapStyle(cap);
}

void ofxShivaVGRenderer::setLineJoinStyle(VGJoinStyle join)
{
    _vg.setStrokeJoinStyle(join);
}

VGCapStyle ofxShivaVGRenderer::getLineCapStyle()
{
    return _vg.getStrokeCapStyle();
}

VGJoinStyle ofxShivaVGRenderer::getLineJoinStyle()
{
    return _vg.getStrokeJoinStyle();
}

void ofxShivaVGRenderer::background(const ofColor & c)
{
    cout << "bakground" << endl;
    _bgColor = c;
	glClearColor(_bgColor[0],_bgColor[1],_bgColor[2], _bgColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ofxShivaVGRenderer::clear(float r, float g, float b, float a)
{
    cout << "clear" << endl;
	glClearColor(r / 255., g / 255., b / 255., a / 255.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ofxShivaVGRenderer::clear(float brightness, float a)
{
	clear(brightness, brightness, brightness, a);
}


// --------------------------------------------
// DRAWING
// --------------------------------------------

void ofxShivaVGRenderer::draw(ofPolyline & poly)
{
	ofStyle style = ofGetStyle();
    
    _vg.setStrokeWidth(style.lineWidth);
    ofColor c = style.color;
    _vg.setStrokeColor(c.r, c.g, c.b, c.a);
    
    simpleVGPath p;
    
    vector<ofVec3f> &verts = poly.getVertices();
    
    p.moveTo(verts[0].x, verts[0].y);
    
    for (vector<ofVec3f>::iterator v = verts.begin()+1; v != verts.end(); ++v)
    {
        p.lineTo(v->x, v->y);
    }
    
    if(poly.isClosed())
    {
        p.close();
    }
    
    _vg.strokePath(p);
}

void ofxShivaVGRenderer::draw(ofPath &path)
{
    ofStyle style = ofGetStyle();
    
    // TODO: fill or stroke?
    
//	vector<ofSubPath> & paths = path.getSubPaths();
    
    simpleVGPath p;
	_doDrawPath(path, p);
    
    ofColor prevColor;
	if(path.getUseShapeColor()) prevColor = style.color;
    
    ofColor c = style.color;
    
    
    if (path.isFilled())
    {
        if (path.getUseShapeColor())
        {
            c = path.getFillColor();
        }
        
        _vg.setFillColor(c.r, c.g, c.b, c.a);
        _vg.fillPath(p);
    }
    
    if (path.hasOutline())
    {
        if (path.getUseShapeColor())
        {
            c = path.getStrokeColor();
        }
        
        _vg.setStrokeColor(c.r, c.g, c.b, c.a);
        _vg.setStrokeWidth(path.getStrokeWidth());
        
        _vg.strokePath(p);
    }
    
	if(path.getUseShapeColor()) setColor(prevColor);
}

void ofxShivaVGRenderer::_doDrawPath(ofPath &path, simpleVGPath &p)
{
    const vector<ofPath::Command> &commands = path.getCommands();
    
    int i = 0;
    
    for(vector<ofPath::Command>::const_iterator c = commands.begin(); c != commands.end(); ++c)
    {
        switch(c->type)
        {
        	case ofPath::Command::moveTo:
                p.moveTo(c->to.x, c->to.y);
                _curvePoints.push_back(c->to);
                break;
                
            case ofPath::Command::lineTo:
                
                _curvePoints.clear();
                p.lineTo(c->to.x, c->to.y);
                
                break;
                
            case ofPath::Command::curveTo:
                
                _curvePoints.push_back(c->to);
                
                //code from ofCairoRenderer to convert from catmull rom to bezier
                if(_curvePoints.size() == 4)
                {
                    ofPoint p1=_curvePoints[0];
                    ofPoint p2=_curvePoints[1];
                    ofPoint p3=_curvePoints[2];
                    ofPoint p4=_curvePoints[3];
                    
                    ofPoint cp1 = p2 + ( p3 - p1 ) * (1.0/6);
                    ofPoint cp2 = p3 + ( p2 - p4 ) * (1.0/6);
                    
                    p.cubicTo(cp1.x, cp1.y, cp2.x, cp2.y, p3.x, p3.y);
                    
                    //cairo_curve_to( cr, cp1.x, cp1.y, cp2.x, cp2.y, p3.x, p3.y );
                    _curvePoints.pop_front();
                }

                break;
                
            case ofPath::Command::bezierTo:
                _curvePoints.clear();
                p.cubicTo(c->cp1.x, c->cp1.y, c->cp2.x, c->cp2.y, c->to.x, c->to.y);
                break;
                
            case ofPath::Command::quadBezierTo:
                _curvePoints.clear();
                p.cubicTo(c->cp1.x, c->cp1.y, c->cp2.x, c->cp2.y, c->to.x, c->to.y);
                break;
                
            case ofPath::Command::arc:
                ofLog(OF_LOG_WARNING, "Arcs are not implemented in the ofxShivaRenderer yet. Sorry :-(");
                break;
                
            case ofPath::Command::arcNegative:
                ofLog(OF_LOG_WARNING, "Arcs are not implemented in the ofxShivaRenderer yet. Sorry :-(");
                break;
                
            case ofPath::Command::close:
                p.close();
                break;
        }
        
        i++;
    }
}


void ofxShivaVGRenderer::drawCircle(float x, float y, float z, float radius)
{
    drawEllipse(x, y, z, radius*2, radius*2);
}

void ofxShivaVGRenderer::drawEllipse(float x, float y, float z, float width, float height)
{
    ofColor c = ofGetStyle().color;
    _vg.setFillColor(c.r, c.g, c.b, c.a);
    
    simpleVGPath p;
    p.ellipse(x, y, width, height);
    
    if (z != 0.0f)
    {
    	pushMatrix();
        translate(0, 0, z);
    }
    
    _vg.fillPath(p);
    
    if (z != 0.0f)
    {
    	pushMatrix();
    }
}

void ofxShivaVGRenderer::drawLine(float x1, float y1, float z1, float x2, float y2, float z2)
{
    ofStyle style = ofGetStyle();
    
    _vg.setStrokeWidth(style.lineWidth);
    ofColor c = style.color;
    _vg.setStrokeColor(c.r, c.g, c.b, c.a);
    
    simpleVGPath p;
    p.moveTo(x1, y1);
    p.lineTo(x2, y2);
    
    _vg.strokePath(p);
}
