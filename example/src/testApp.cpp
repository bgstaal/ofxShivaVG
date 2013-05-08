#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetFrameRate(100.0f);
    ofSetCurveResolution(100);
    
    _defaultRenderer = ofGetCurrentRenderer();
    _shivaVGRenderer = ofPtr<ofxShivaVGRenderer>(new ofxShivaVGRenderer);
    ofSetCurrentRenderer(_shivaVGRenderer);
    
    _shivaVGRenderer->setLineJoinStyle(VG_JOIN_ROUND);
    _shivaVGRenderer->setLineCapStyle(VG_CAP_ROUND);
    
    float s = ofGetWidth()*.25f;
    
    for (int i = 0; i < 6; i++)
    {
        _jaggedPath.lineTo(ofRandom(-s, s), ofRandom(-s, s));
    }
    
    _jaggedPath.close();
    
    _curvedPath.setFilled(false);
    _curvedPath.setStrokeWidth(20.0f);
    
    //_curvedPath.lineTo(-s, 0);
    //_curvedPath.quadBezierTo(-s, -s, s, -s, s, 0);
    _curvedPath.arc(0, 0, 100.0f, 100.0f, -90, 90);
    
    /*
    for (int i = 0; i <5; i++)
    {
        _curvedPath.lineTo(ofRandom(-s, s), ofRandom(-s, s));
    }
    
    //_curvedPath.moveTo(ofRandom(-s, s), ofRandom(-s, s));
    
    for (int i = 0, num = 10; i <num; i++)
    {
		_curvedPath.curveTo(ofRandom(-s, s), ofRandom(-s, s));
    }
     */
}

//--------------------------------------------------------------
void testApp::update()
{
    
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(20);
    
    float w = 100.0f;
    float s = 20.0f;
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
    
    
    ofPushMatrix();
    ofSetColor(0, 255, 255);
    ofTranslate(ofGetWidth()*.25f, ofGetHeight()*.5f);
    _jaggedPath.draw();
    ofPopMatrix();
    
    _curvedPath.draw(ofGetWidth()*.75f, ofGetWidth()*.25f);
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
    cout << key << endl;
    
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