#ifndef __ofxShivaVGRendererTest__simpleVGPath__
#define __ofxShivaVGRendererTest__simpleVGPath__

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
    
	private:
    
    	bool _hasPath;
    	VGPath _path;
    
};

#endif /* defined(__ofxShivaVGRendererTest__simpleVGPath__) */
