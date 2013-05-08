#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main()
{
	ofAppGlutWindow window; // create a window
	window.setGlutDisplayString("rgba alpha double stencil samples=16");
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1440, 1024, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
