
/*
 * OPTICAL FLOW CLASS USING 'ofxCv'
 *
 * Ref:
 * "Optical Flow Test," Adrian Sheerwood, Accessed April 15, 2020. https://aaron-sherwood.com/blog/?p=700
 * "ofxCV", Kyle McDonald. https://github.com/kylemcdonald/ofxCv
 *
 *
*/

#include "ofMain.h"
#include "ThreadedCV.h"


ThreadedCV::ThreadedCV()
{

    startThread();
}

ThreadedCV::~ThreadedCV()
{
    waitForThread(true);
}

void ThreadedCV::setup() {


//    //CAMERA
    camera.setGrabber(std::make_shared<ofxPS3EyeGrabber>()); //COMMENT TO USE INTERNAL CAMERA
//    vidGrabber.setDeviceID(1);                                 //UNCOMMENT TO USE INTERNAL CAMERA
//    vidGrabber.setPixelFormat(OF_PIXELS_NATIVE);
    camera.setDesiredFrameRate(60);
    camera.initGrabber(640, 480);
    camera.getGrabber<ofxPS3EyeGrabber>()->setAutogain(false);
    camera.getGrabber<ofxPS3EyeGrabber>()->setAutoWhiteBalance(false);

    cursorX = 0; //used for controling the treadling ie where the treadling is, influenced by movement in x axis
    counterY = 0; //counter used as lag or small delay to smoothen flip/trigger of bool
    yMotionNeg = true; //toggle decided by negative movement in Y axis
    yMotionPos = true; //toggle decided by positiv movement in Y axis
    motionDetected = false; //checks for movement
    yReset - false; //trigger checking negative Y motion
    prev=vec2(ofGetWidth()/2,ofGetHeight()/2); //previous

    multi = 64;
    damp = 0.05;
    yThresh = -10;
    traction = 2.0;
      currentColor.allocate(640, 480);
      float decimate = 0.25;
      decimatedImage.allocate( currentColor.width * decimate, currentColor.height * decimate );

//    ////GUI TO BE IMPLEMENTED///

//    //    gui.setup();
//    //    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
//    //    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
//    //    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
//    //    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
//    //    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
//    //    gui.add(fbUseGaussian.set("fbUseGaussian", false));
//    //    gui.add(fbWinSize.set("winSize", 32, 4, 64));

    curFlow = &fb;
}


void ThreadedCV::threadedFunction() {
    camera.update();
ofPixels pixels;
  while(isThreadRunning()) {
    if(camera.isFrameNew()) {

//        lock();
////      curFlow = &fb;
//      //To IMPLEMENT GUI CONTROL///
//      //            fb.setPyramidScale(fbPyrScale);
//      //            fb.setNumLevels(fbLevels);
//      //            fb.setWindowSize(fbWinSize);
//      //            fb.setNumIterations(fbIterations);
//      //            fb.setPolyN(fbPolyN);
//      //            fb.setPolySigma(fbPolySigma);
//      //            fb.setUseGaussian(fbUseGaussian);
//      fb.setPyramidScale(.5);
//      fb.setNumLevels(4);
//      fb.setWindowSize(32);
//      fb.setNumIterations(2);
//      fb.setPolyN(7);
//      fb.setPolySigma(1.5);
//      fb.setUseGaussian(false);

//      //Reading pixles and convert to ofxCVImage
      pixels = camera.getPixels();
      currentColor.setFromPixels( pixels );
//camera.setUseTexture(false);

      //Decimate images to 25%, a lot less expensive and lets you keep higher resolution camera input. Ref: Theo Papatheodorou see readme
      decimatedImage.scaleIntoMe( currentColor, CV_INTER_AREA );
//      decCamera = decimatedImage;

//      // reference: Aaron Sherwood, see readme
      curFlow->calcOpticalFlow(decimatedImage);
      flow=fb.getAverageFlow() * multi; ///*~30?
      flow=vec2(flow.x,flow.y) ;
      dampenedflow+=(flow-dampenedflow)*damp; //~.05
      prev+=dampenedflow;

      vec2 midZone=vec2(ofGetWidth()/2,ofGetHeight()/2);
      vec2 returnToMid = midZone-prev;
      vec2 norm = glm::normalize(returnToMid);
      float dist = glm::distance(prev, midZone);

      prev.x = ofClamp(prev.x, -100, ofGetWidth()+100);


      //slight controllable traction/current
      if(dist > 3) {
        prev+=norm*(traction);
      }

      //if to far beyond the limit, additional traction to smoothly take the "cursor" back
      if(prev.x < -10 ) {
        prev+=norm*traction; //~10
      }
      if(prev.x > ofGetWidth()+10) {
        prev+=norm*traction; //~10
      }

      int x = ofClamp(prev.x, 0, ofGetWidth());

      //a virtual cursor that gets positioned by the optical flow.x
      if (x < ofGetWidth()*0.25) {
        cursorX = 0;
      } else if (x > ofGetWidth()*0.25 && x < ofGetWidth()*0.5) {
        cursorX = 1;
      } else if (x > ofGetWidth()*0.5 && x < ofGetWidth()*0.75) {
        cursorX = 2;
      } else if (x > ofGetWidth()*0.75) {
        cursorX = 3;
      }


      //DETECT Y MOTION WITH SMALL LAG, ie counterY > lagNumber
      if (dampenedflow.y < yThresh && counterY > 30) {   //~-20
        yMotionNeg = !yMotionNeg;
        yReset = !yReset;
        counterY = 0; //RESETTING COUNTER ADDING LAG
      }

      //RESETS yReset TO USE AS TRIGGER
      if(counterY > 31) {
        yReset = 0;
      }



      //DETECT MOTION
      if (dampenedflow.x < -5. || dampenedflow.x > 5.) {
        motionDetected = true;
      } else {
        motionDetected = false;
      }
                cout << "motionDetected" << motionDetected << endl;
//      unlock()*/;
    }

    counterY++;
    }
}

void ThreadedCV::update(float _multi, float _damp, float _yThresh, float _traction) {

    camera.update();

    if(camera.isFrameNew()) {

        curFlow = &fb;
        //To IMPLEMENT GUI CONTROL///
        //            fb.setPyramidScale(fbPyrScale);
        //            fb.setNumLevels(fbLevels);
        //            fb.setWindowSize(fbWinSize);
        //            fb.setNumIterations(fbIterations);
        //            fb.setPolyN(fbPolyN);
        //            fb.setPolySigma(fbPolySigma);
        //            fb.setUseGaussian(fbUseGaussian);
        fb.setPyramidScale(.5);
        fb.setNumLevels(4);
        fb.setWindowSize(32);
        fb.setNumIterations(2);
        fb.setPolyN(7);
        fb.setPolySigma(1.5);
        fb.setUseGaussian(false);

        //Reading pixles and convert to ofxCVImage
        ofxCvColorImage currentColor;
        currentColor.allocate(640, 480);
        ofPixels & pixels = camera.getPixels();
        currentColor.setFromPixels( pixels );

        //Decimate images to 25%, a lot less expensive and lets you keep higher resolution camera input. Ref: Theo Papatheodorou see readme
        float decimate = 0.25;
        ofxCvColorImage decimatedImage;
        decimatedImage.allocate( currentColor.width * decimate, currentColor.height * decimate );
        decimatedImage.scaleIntoMe( currentColor, CV_INTER_AREA );
        decCamera = decimatedImage;

        // reference: Aaron Sherwood, see readme
        curFlow->calcOpticalFlow(decCamera);
           flow=fb.getAverageFlow() * _multi; //~30?
          flow=vec2(flow.x,flow.y) ;
          dampenedflow+=(flow-dampenedflow)*_damp; //~.05
          prev+=dampenedflow;

          vec2 midZone=vec2(ofGetWidth()/2,ofGetHeight()/2);
           vec2 returnToMid = midZone-prev;
           vec2 norm = glm::normalize(returnToMid);
           float dist = glm::distance(prev, midZone);

           prev.x = ofClamp(prev.x, -100, ofGetWidth()+100);


           //slight controllable traction/current
           if(dist > 3) {
               prev+=norm*(_traction);
           }

           //if to far beyond the limit, additional traction to smoothly take the "cursor" back
           if(prev.x < -10 ) {
               prev+=norm*_traction; //~10
           }
           if(prev.x > ofGetWidth()+10) {
               prev+=norm*_traction; //~10
           }

          int x = ofClamp(prev.x, 0, ofGetWidth());

        //a virtual cursor that gets positioned by the optical flow.x
          if (x < ofGetWidth()*0.25) {
              cursorX = 0;
          } else if (x > ofGetWidth()*0.25 && x < ofGetWidth()*0.5) {
              cursorX = 1;
          } else if (x > ofGetWidth()*0.5 && x < ofGetWidth()*0.75) {
              cursorX = 2;
          } else if (x > ofGetWidth()*0.75) {
              cursorX = 3;
          }


          //DETECT Y MOTION WITH SMALL LAG, ie counterY > lagNumber
          if (dampenedflow.y < _yThresh && counterY > 30) {   //~-20
              yMotionNeg = !yMotionNeg;
              yReset = !yReset;
              counterY = 0; //RESETTING COUNTER ADDING LAG
          }

          //RESETS yReset TO USE AS TRIGGER
          if(counterY > 31) {
              yReset = 0;
          }



          //DETECT MOTION
          if (dampenedflow.x < -5. || dampenedflow.x > 5.) {
              motionDetected = true;
          } else {
              motionDetected = false;
          }
//          cout << "motionDetected" << motionDetected << endl;
    }

    counterY++;
}

void ThreadedCV::draw() {

    ofSetColor(255);
    ofPushMatrix();
//    ofTranslate(250, 100);
    ofScale(0.5, 0.5);
    decCamera.draw(0,220,640,480);
    curFlow->draw(0,220,640,480);
  //  ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps", 10, 20);

    ofPopMatrix();

    // DRAW DEBUG UI
    ofPushMatrix();
    ofSetColor(255,0,255);
    ofDrawBitmapStringHighlight("prevX: " + ofToString(prev.x), 0, 0);
    ofDrawBitmapStringHighlight("prevY: " + ofToString(prev.y), 150, 0);
    ofDrawBitmapStringHighlight("flowx: " + ofToString(dampenedflow.x), 0, 25);
    ofDrawBitmapStringHighlight("flowY: " + ofToString(dampenedflow.y), 150, 25);
    ofDrawBitmapStringHighlight("Y-: " + ofToString(yMotionNeg), 0, 75);
    ofDrawBitmapStringHighlight("Motion: " + ofToString(motionDetected), 150, 75);
    ofDrawBitmapStringHighlight("cursorX: " + ofToString(cursorX), 0, 100);

    //draw cursor position indicator
    ofPushMatrix();
    ofTranslate(90, 90);
    ofSetColor(255);
    ofDrawRectangle(0,0, 40, 10);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            ofSetColor(0);
            ofDrawLine(0, i * 10, 40, i * 10);
            ofDrawLine(j*10, 0, j*10, 10);
        }
    }
    ofSetColor(0);
    ofDrawRectangle(cursorX*10, 0, 10, 10);

    //draw cursor flow line
    ofSetColor(0);
    float testX = ofMap(prev.x, 0, ofGetWidth(), 0, 200);
    ofSetLineWidth(3);
    ofDrawLine(50,0, 250, 0);
    ofDrawRectangle(testX+50-5, -5, 10, 10);
    ofPopMatrix();

    ofPopMatrix();
}

///GETTER FUNCTIONS///
/////////////////////j
int ThreadedCV::getCursor() {
    return cursorX;
}

glm::vec2 ThreadedCV::getDampenedFlow() {
    return dampenedflow;
}

bool ThreadedCV::getYmotionNeg() {
    return yMotionNeg;
}

bool ThreadedCV::getYreset() {
    return yReset;
}

bool ThreadedCV::getMotionDetected() {
    return motionDetected;
}
