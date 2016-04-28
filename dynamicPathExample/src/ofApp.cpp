#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(100);
    ofSetVerticalSync(false);
    
    _center = ofPoint();
    _addNewPath();
    _paths[_paths.size()-1].moveTo(_calculateNextPoint());
    
    _defaultRenderer = ofGetCurrentRenderer();
    _useShiva = false;
    _shivaRenderer = ofPtr<ofxShivaVGRenderer>(new ofxShivaVGRenderer);
    _shivaRenderer->setLineCapStyle(VG_CAP_ROUND);
    
    _rotation = _zoom = 0;
    _paused = false;
}

ofPoint ofApp::_calculateNextPoint()
{
    float s = ofGetHeight()/2;
    float t = ofGetElapsedTimef();
    ofPoint p = _center;
    p += ofPoint(cos(t)*(sin(t*(cos(t)/PI))*s), sin(t)*(cos(t*(sin(t)/PI))*s));
    
    return p;
}

void ofApp::_addNewPath()
{
    ofPath p;

    p.setFilled(false);
    p.setStrokeWidth(ofRandom(10.0f, 30.0f));
    
    ofColor c;
    
    if (ofRandom(1.0f) > .85f)	
    {
        c = ofFloatColor(1.0, .2f, ofRandom(.3f, .6f));
    }
    else
    {
        c = ofFloatColor(.3, ofRandom(.9f, 1.0f), ofRandom(.7f, 1.0f));
    }
    
    p.setColor(c);
    
    _paths.push_back(p);
}

//--------------------------------------------------------------
void ofApp::update()
{
    if (!_paused)
    {
        float t = ofGetElapsedTimef();
        _zoom = sin(t) * 500;
        _rotation += .2f;
        
        ofPoint p = _calculateNextPoint();
        
        if (ofRandom(1.0f) > .96f)
        {
            _addNewPath();
            _paths[_paths.size()-1].moveTo(p);
        }
        else
        {
            _paths[_paths.size()-1].curveTo(p);
        }
        
        if (_paths.size() > 20) _paths.erase(_paths.begin());
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackground(30);
    
    glPushMatrix();
    //glTranslatef(-ofGetWidth()/2.0f, ofGetW, _zoom);
   
    glTranslatef(ofGetWidth()/2.0f, ofGetHeight()/2.0f, _zoom);
    glRotatef(_rotation, 0, 0, 1.0f);
    
    
    for (vector<ofPath>::iterator p = _paths.begin(); p != _paths.end(); p++)
    {
        p->draw();
    }
    
    glPopMatrix();
    
    stringstream s;
    s << "FPS: " << (int)ofGetFrameRate();
    s << " | current renderer: ";
    s << (_useShiva ? "SHIVA_VG" : "OPENGL");
    s << " | click to toogle renderer";
    
    ofDrawBitmapString(s.str(), 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == 112) // "p"
    {
        _paused = !_paused;
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
void ofApp::mousePressed(int x, int y, int button)
{
	_useShiva = !_useShiva;
    
    if (_useShiva)
    {
        ofSetCurrentRenderer(_shivaRenderer);
    }
    else
    {
        ofSetCurrentRenderer(_defaultRenderer);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}