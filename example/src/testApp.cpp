#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(100.0f);
    ofSetCurveResolution(100);
    
    _shapeSize = 160;
    
    _defaultRenderer = ofGetCurrentRenderer();
    _shivaVGRenderer = ofPtr<ofxShivaVGRenderer>(new ofxShivaVGRenderer);
    ofSetCurrentRenderer(_shivaVGRenderer);
    
    _shivaVGRenderer->setLineJoinStyle(VG_JOIN_ROUND);
    _shivaVGRenderer->setLineCapStyle(VG_CAP_ROUND);
    
    _createPolygon();
    _createStar();
    _createCurvedPath();
}

void testApp::_createPolygon()
{
    float s = _shapeSize;
    float r = _shapeSize/2;
   	int numPoints = 6;
    float angleStep = TWO_PI/numPoints;
    
    for (int i = 0; i < numPoints; i++)
    {
    	ofPoint p(cos(angleStep*i)*r, sin(angleStep*i)*r);
        _polygon.addVertex(p);
    }
    
    _polygon.close();
}

void testApp::_createStar()
{
    float s = _shapeSize;
    float r = _shapeSize/2;
    float r2 = r/2;
   	int numPoints = 5;
    numPoints *= 2;
    float angleStep = TWO_PI/numPoints;
    
    _star.setStrokeColor(ofColor(255, 0, 0));
    _star.setFillColor(ofColor(255, 255, 255));
    _star.setStrokeWidth(20.0f);
    
    for (int i = 0; i < numPoints; i++)
    {
        float rad = i % 2 == 0 ? r2 : r;
        
        ofPoint p(cos(angleStep*i)*rad, sin(angleStep*i)*rad);
        _star.lineTo(p);
    }
    
    _star.close();
}


void testApp::_createCurvedPath ()
{
    _curvedPath.setFilled(false);
    _curvedPath.setStrokeColor(ofColor(255, 255, 255));
    _curvedPath.setStrokeWidth(20.0f);
    
    for (int i = 0; i < 20; i++)
    {
        float s = _shapeSize*1.5;
        float t = (i*100)/PI;
        ofPoint p = ofPoint(cos(t)*(sin(t*(cos(t)/PI))*s), sin(t)*(cos(t*(sin(t)/PI))*s));
        
        if (i == 0) _curvedPath.moveTo(p);
        else _curvedPath.curveTo(p);
    }
}

//--------------------------------------------------------------
void testApp::update()
{
    
}



//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(20);
    glPushMatrix();
    
    float w = _shapeSize;
    float s = 40.0f;
    float x = s;
    float y = s;
    
    ofSetColor(255, 0, 0);
    ofRect(x, y, 0, w, w);
    
    x += w + s;
    ofSetColor(ofFloatColor(0.0f, 0.0f, 1.0f));
    ofCircle(x + w/2, y + w/2, w/2);
    
    x += w + s;
    ofSetColor(ofFloatColor(0.0f, 1.0f, 0.0f));
    ofSetLineWidth(30.0f);
    ofLine(x + s, y + s, x + w - s, y + w - s);
    
    x += w + s;
    ofSetColor(ofFloatColor(1.0f, 0.0f, 1.0f));
    ofEllipse(x + w, y + w/2, w*2, w);
    
    x = s;
    y = s + w + s;
    
    ofSetLineWidth(20.0f);
    ofSetColor(0, 255, 255);
    ofPushMatrix();
    ofTranslate(x + (w/2), y + (w/2));
    	_polygon.draw();
    ofPopMatrix();
    
    x += w + s;
    
    ofPushMatrix();
    ofTranslate(x + (w/2), y + (w/2));
    	_star.draw();
    ofPopMatrix();
    
    x += w + w + s;
    y += w;
    
    ofPushMatrix();
    ofTranslate(x + (w/2), y + (w/2));
    	_curvedPath.draw();
    ofPopMatrix();
    
    glPopMatrix();
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    cout << "change renderer" << endl;
    
    if (ofGetCurrentRenderer() == _defaultRenderer)
    {
        ofSetCurrentRenderer(_shivaVGRenderer);
    }
    else
    {
        ofSetCurrentRenderer(_defaultRenderer);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    if (key == 99) // c letter
    {
        if (_shivaVGRenderer->getLineCapStyle() == VG_CAP_ROUND)
        {
            _shivaVGRenderer->setLineCapStyle(VG_CAP_SQUARE);
            _shivaVGRenderer->setLineJoinStyle(VG_JOIN_MITER);
        }
        else
        {
            _shivaVGRenderer->setLineCapStyle(VG_CAP_ROUND);
            _shivaVGRenderer->setLineJoinStyle(VG_JOIN_ROUND);
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}