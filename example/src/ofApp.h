#pragma once

#include "ofMain.h"
#include "ofxShivaVGRenderer.h"

class ofApp : public ofBaseApp
{
	public:
    
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
	private:
    
		ofPtr<ofBaseRenderer> _defaultRenderer;
		ofPtr<ofxShivaVGRenderer> _shivaVGRenderer;
    
	    ofPolyline _polygon;
    	ofPath _star;
	    ofPath _curvedPath;
	    float _shapeSize;
    
		void _createPolygon();
    	void _createStar();
	    void _createCurvedPath();

};
