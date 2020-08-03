#pragma once

#include "ofMain.h"
#include "ofApp.h"
#include "Draft.h"
//#include "OpticalFlow.h"
#include "ThreadedCV.h"

//addons
#include "ofxThermalPrinter.h"
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

    void exit();

    void updateOSC();
    void setupPrinter();
    void printString(string inputString);
    void printImg(ofImage inputImg);
    void printFullDraft();

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

    //VARIABLES
    int numWarps, numShafts, numWeft, offsetX, offsetY, updateRate;
    float orgX, orgY, width, height, wWidth, wHeight, tWidth, tHeight, cellSize, numBoxPad, cellPad;
    bool print, runDraft;

    //COLOURS
    ofColor bg, fg;

    ofFbo patternFbo;

    //OBJECTS
    Draft draft;
    //OpticalFlow optf;
    ThreadedCV tCV;

    //PRINTER
    ofxThermalPrinter printer;
    //OSC
    ofxOscReceiver oscR;

};

