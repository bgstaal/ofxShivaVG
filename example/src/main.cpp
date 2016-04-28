#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
int main()
{
	ofAppGLFWWindow window;
	ofGLFWWindowSettings s;
	s.width = 1440;
	s.height = 1024;
	s.stencilBits = 8;
	
	ofCreateWindow(s);
	//ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
	ofRunApp(new ofApp);
}
