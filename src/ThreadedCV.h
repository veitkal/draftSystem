/* THREADED COMPUTER VISION CLASS USING OPTICAL FLOW */

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxKinect.h"

//Namespaces for cleaner code
using namespace ofxCv;
using namespace cv;
using namespace glm;

class ThreadedCV: public ofThread  {

public:
    ThreadedCV();
    ~ThreadedCV();

    void setup(int _numShafts, int _numWarps);
    void threadedFunction();
    void update(float _multi, float _damp, float _yThresh, float _traction);
    void draw();

    int getCursor();
    glm::vec2 getDampenedFlow();
    bool getYmotionNeg();
    bool getYreset();
    bool getMotionDetected();


    ofVideoGrabber camera;
    ofxCvColorImage decCamera;

    ofxCv::FlowFarneback fb;
    ofxCv::FlowPyrLK lk;
    ofxCv::Flow* curFlow;

    ///GUI TO IMPLEMENT IN ofApp ///
//    ofxPanel gui;
//    ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma;
//    ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
//    ofParameter<bool> fbUseGaussian, usefb;


    vec2 flow;
    vec2 dampenedflow;
    vec2 prev;
    ofxCvColorImage currentColor;
    ofxCvColorImage decimatedImage;

    int numShafts, numWarps;
    float cursorX, counterY;
    bool yMotionPos, yMotionNeg, motionDetected, yReset;
    float multi, damp, yThresh, traction;
};
