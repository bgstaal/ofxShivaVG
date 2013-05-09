# ofxShivaVG

ofxShivaVG is a 2d-renderer for openFrameworks based on the ShivaVG OpenVG implementation. It provides improved rendering quality of 2d paths/curves, polylines and shapes, with optional line capping/joining.

Everything is rendered through openGL wich makes it much more performant than other cpu based 2d graphics libraries (Cairo, Quartz etc). It also makes it easy to render 2d and 3d graphics interchangeably.

##Usage

* Clone into openframeworks/addons
* Add src & lib folders to your project

###Example


First, you **MUST** enable a stencil buffer in your ofProject. This is done by passing in "stencil" as part of the glut display string. See example below:


```c
#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main()
{
	ofAppGlutWindow window; // create a window
	
	// THIS IS THE IMPORTANT PART:
    window.setGlutDisplayString("rgba alpha double stencil samples>=4");
    
    
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(&window, 1024, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
```

Then switch to the ofxShivaRenderer in your setup method

```c
void testApp::setup()
{
    _shivaVGRenderer = ofPtr<ofxShivaVGRenderer>(new ofxShivaVGRenderer);
    ofSetCurrentRenderer(_shivaVGRenderer);
}
```

Now all your ofPath's and ofPolylines should look delicious!

See examples for more details.

##Screenshots

Default oF renderer:

![Imgur](http://i.imgur.com/hMSeaZu.png)

ofxShivaVGRenderer:

![Imgur](http://i.imgur.com/hsh4HzM.png)

##Roadmap

* Implement arc drawing
* make ofPath subclass to add cap/join props pr. path
* support gradient fills



