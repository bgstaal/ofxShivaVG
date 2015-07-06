#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
int main()
{
    ofPtr<ofAppGLFWWindow> win = ofPtr<ofAppGLFWWindow>(new ofAppGLFWWindow());
    win->setStencilBits(8);
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(win, 1440, 1024, OF_WINDOW);
	ofRunApp(new ofApp()); // start the app
}
