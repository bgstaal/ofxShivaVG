//
//  ofxShivaVGRenderer.cpp
//  ofxShivaVGRendererTest
//
//  Created by Staal, Bjørn Gunnar (OSL-SDG) on 07.05.13.
//
//

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
    // TODO: multiply colors with current color?
    
    ofColor c = path.getStrokeColor();
    
    _vg.setStrokeColor(c.r, c.g, c.b, c.a);
    _vg.setStrokeWidth(path.getStrokeWidth());
    
	vector<ofSubPath> & paths = path.getSubPaths();
    
    simpleVGPath p;
    
	for(int i=0;i<(int)paths.size();i++)
    {
		_draw(paths[i], p);
	}
    
    _vg.strokePath(p);
}

void ofxShivaVGRenderer::_draw(ofSubPath &path, simpleVGPath &p)
{
    const vector<ofSubPath::Command> & commands = path.getCommands();
    
    if (commands.size() > 1)
    {
        int i = 0;
        
        for(vector<ofSubPath::Command>::const_iterator c = commands.begin(); c != commands.end(); ++c)
        {
            switch(c->type)
            {
                case ofSubPath::Command::lineTo:
                    
                    _curvePoints.clear();
                    
                    if (i == 0)
                    {
                        // if the first command in a subPath is a lineTo it should be
                        // interpeted as a moveTo command
                        // this makes up for the lack of a moveTo command in ofSubPath
                        
                        p.moveTo(c->to.x, c->to.y);
                        _curvePoints.push_back(c->to);
                    }    
                    else
                    {
                        p.lineTo(c->to.x, c->to.y);
                    }
                    
                	break;
                    
                case ofSubPath::Command::curveTo:
                    
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
            }
            
            i++;
        }
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
