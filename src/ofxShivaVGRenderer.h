//
//  ofxShivaVGRenderer.h
//  ofxShivaVGRendererTest
//
//  Created by Staal, Bjørn Gunnar (OSL-SDG) on 07.05.13.
//
//

#ifndef __ofxShivaVGRendererTest__ofxShivaVGRenderer__
#define __ofxShivaVGRendererTest__ofxShivaVGRenderer__

#include "ofMain.h"
#include "simpleVGContext.h"

class ofxShivaVGRenderer : public ofGLRenderer
{
    public:
    
	    ofxShivaVGRenderer();
    
	    void background(const ofColor & c);
	    void draw(ofPolyline & poly);
	    void draw(ofPath &path);
    	void drawCircle(float x, float y, float z,  float radius);
    	void drawEllipse(float x, float y, float z, float width, float height);
    	void drawLine(float x1, float y1, float z1, float x2, float y2, float z2);
    	void setLineCapStyle(VGCapStyle cap);
    	void setLineJoinStyle(VGJoinStyle join);
	    VGCapStyle getLineCapStyle();
	    VGJoinStyle getLineJoinStyle();
    
        bool rendersPathPrimitives()
    	{
            return true;
        }
    
	private:
    
	    simpleVGContext _vg;
        deque<ofPoint> _curvePoints;
	    ofFloatColor _bgColor;
    
    	void _draw(ofSubPath &path, simpleVGPath &toPath);
    
};

#endif /* defined(__ofxShivaVGRendererTest__ofxShivaVGRenderer__) */
