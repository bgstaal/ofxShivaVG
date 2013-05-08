#ifndef __ofxShivaVGRendererTest__SimpleVG__
#define __ofxShivaVGRendererTest__SimpleVG__

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

#endif /* defined(__ofxShivaVGRendererTest__SimpleVG__) */
