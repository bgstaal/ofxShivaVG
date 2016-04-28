#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
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

void ofApp::_createPolygon()
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

void ofApp::_createStar()
{
    float s = _shapeSize;
    float r = _shapeSize/2;
    float r2 = r/2;
   	int numPoints = 5;
    numPoints *= 2;
    float angleStep = TWO_PI/numPoints;
    
    _star.setFillColor(ofColor(255, 255, 255));
    _star.setStrokeColor(ofColor(129, 174, 186));
    _star.setStrokeWidth(20.0f);
    
    for (int i = 0; i < numPoints; i++)
    {
        float rad = i % 2 == 0 ? r2 : r;
        
        ofPoint p(cos(angleStep*i)*rad, sin(angleStep*i)*rad);
        
        if (i == 0)
        {
            _star.moveTo(p);
        }
        else
        {
            _star.lineTo(p);
        }
        
    }
    
    _star.close();
}


void ofApp::_createCurvedPath ()
{
    _curvedPath.setFilled(false);
    _curvedPath.setStrokeColor(ofColor::white);
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
void ofApp::update()
{
    
}



//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackground(30);
    
    float w = _shapeSize;
    float s = 40.0f;
    float x = s;
    float y = s;
    
    ofSetColor(ofColor::fromHex(0xFF7B87));
    ofRect(x, y, 0, w, w);
    
    x += w + s;
    ofSetColor(ofColor::fromHex(0x475887));
    ofCircle(x + w/2, y + w/2, w/2);
    
    x += w + s;
    ofSetColor(220, 222, 121);
    ofSetLineWidth(30.0f);
    ofLine(x + s, y + s, x + w - s, y + w - s);
    
    x += w + s;
    ofSetColor(255, 232, 183);
    ofEllipse(x + w, y + w/2, w*2, w);
    
    x = s;
    y = s + w + s;
    
    ofSetLineWidth(20.0f);
    ofSetColor(100, 255, 255);
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
    
    ofSetColor(255, 255, 255);
    
    stringstream m;
    m << "FPS: " << (int)ofGetFrameRate();
    m << " | current renderer: ";
    m << (ofGetCurrentRenderer() == _defaultRenderer ? "DEFAULT" : "OFX_SHIVA_VG");
    m << " | click to toogle renderer";
    m << " | hit 'c' to toggle line-cap style";
    
    ofDrawBitmapString(m.str(), s, ofGetHeight() - s);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
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
void ofApp::keyPressed(int key)
{
    if (key == 99) // c letter
    {
        if (_shivaVGRenderer->getLineCapStyle() == VG_CAP_ROUND)
        {
            cout << "cap square" << endl;
            _shivaVGRenderer->setLineCapStyle(VG_CAP_SQUARE);
            _shivaVGRenderer->setLineJoinStyle(VG_JOIN_MITER);
        }
        else
        {
            cout << "cap round" << endl;
            _shivaVGRenderer->setLineCapStyle(VG_CAP_ROUND);
            _shivaVGRenderer->setLineJoinStyle(VG_JOIN_ROUND);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}