#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofSetupOpenGL(800,480,OF_FULLSCREEN);			// <-------- setup the GL context

   // ofGLFWWindowSettings msettings;
   // msettings.setSize(800,420);
   // msettings.numSamples;
   // auto mainWin = ofCreateWindow(msettings);

   // auto app = make_shared<ofApp>();
   // ofRunApp(mainWin, app);
   
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());

}
