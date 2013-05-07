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
	    void ellipse(VGfloat x, VGfloat y, VGfloat w, VGfloat h);
	    void moveTo(VGfloat x, VGfloat y);
    	void lineTo(VGfloat x, VGfloat y);
    
	private:
    
    	bool _hasPath;
    	VGPath _path;
    
};

#endif /* defined(__ofxShivaVGRendererTest__simpleVGPath__) */
