#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Draft.h"
//#include "OpticalFlow.h"
#include "ThreadedCV.h"

//addons
#include "ofxOsc.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

//OSC Port
#define PORT 9000

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void updateOSC();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

int numWarps, numShafts, numWeft, offsetX, offsetY, updateRate;

float orgX, orgY, width, height, wWidth, wHeight, tWidth, tHeight, cellSize, numBoxPad, cellPad;

ofColor bg, fg;

Draft draft;
//OpticalFlow optf;
ThreadedCV tCV;

//OSC
ofxOscReceiver oscR;

};

