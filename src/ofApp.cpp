#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //    ofBackground(0);
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);

    //OSC
    oscR.setup(PORT);

    //VARS
    bg = ofColor(255); //background colour draft
    fg = ofColor(0); //foreground colour draft

    print = false;
    runDraft = true;

    numShafts = 5;
    numWarps = 29; //number of warps
    offsetX = 10; //offset where to begin drawing draft
    offsetY = 10;
    orgX = offsetX; //origin of draft ie translated 0
    orgY = offsetY;
    width = 800 - (offsetX * 2); //temporary size
    height = 480 - (offsetY * 2);
    numBoxPad = 1; //padding between drawnBoxes, calculated as a number of cells ie n*cellSize
    updateRate = 30;

    cellSize = width / (numWarps+numShafts + numBoxPad); //size of cells in draft

    setupPrinter();
    draft.setup(numShafts, numWarps, orgX, orgY, width, height, numBoxPad, cellSize, bg, fg);
//    optf.setup();
    tCV.setup(numShafts);

    //pattern fbo
    patternFbo.allocate(800, 480);
    patternFbo.begin();
    ofClear(0);
    patternFbo.end();

}

// EXIT FUNCTION TO CLOSE DOWN PRINTER AND OPTIONALLY PRINT EMPTY LINE
void ofApp::exit(){
//    printer.println("\n"); //UNCOMMENT TO ADD EXTRA EMPTY SPACE WHEN EXIT
    printer.close();
}

//--------------------------------------------------------------
void ofApp::update(){
    updateOSC();
  if (runDraft && ofGetFrameNum() % 5 == 0) {
    draft.pushTreadling(tCV.getCursor());
    draft.update();
  if(print) {
//      printString(draft.getCurrentString());
      ofColor(255);
//      printImg(draft.getCurrentImg());
//      printFullDraft();
  }
  }
  //tCV.update(63., .05, -10., 2.0);
//  cout << draft.getCurrentString() << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(0);
  ofFill();
  ofDrawRectangle(0,0, 800, 480);

  draft.draw();

  ofSetColor(0);
  ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps"    , 20, 20);

  draft.drawPattern(0,500, 800, 480);


}

//--------------------------------------------------------------

void ofApp::updateOSC(){
    while (oscR.hasWaitingMessages()) {
        ofxOscMessage m;
        oscR.getNextMessage(&m);

        if (m.getAddress() == "/updateWarp") {
            draft.updateWarp = m.getArgAsBool(0);
        }
        if (m.getAddress() == "/updateWeft") {
            draft.updateWeft = m.getArgAsBool(0);
        }
        if (m.getAddress() == "/treadleSin1") {
            draft.treadlingSin1 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/treadleSin2") {
            draft.treadlingSin2 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/treadleNoise1") {
            draft.treadlingNoise1 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/threadingSin1") {
            draft.threadingSin1 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/threadingSin2") {
            draft.threadingSin2 = m.getArgAsFloat(0);
        }
        if (m.getAddress() == "/threadingNoise1") {
            draft.threadingNoise1 = m.getArgAsFloat(0);
        }
    }

}

//--------------------------------------------------------------
//set up thermal printer
void ofApp::setupPrinter(){
  //PRINTER SEETTINGS
  printer.open("/dev/ttyUSB0");
  printer.setReverse(false);
  printer.setBold(true);
  printer.setAlign(MIDDLE);
  //    printer.setUnderline(true); // to use if prints are generated as texts
  printer.setControlParameter(7,160,0);

}
//--------------------------------------------------------------
//print line with thermal printer
void ofApp::printString(string inputString){
  printer.println(inputString);

}
//--------------------------------------------------------------
//print image with thermalPrinter
void ofApp::printImg(ofImage inputImg){
  printer.print(inputImg);

}
//--------------------------------------------------------------
//print fullDraft with thermalPrinter
void ofApp::printFullDraft(){
  runDraft = false;  //pausing the update
  draft.setupDrawDown(); //calculating the full pattern (ie with the same threading)
  printImg(draft.draftToImg()); //printing full draft
  print = false;  //stopping the printing

  runDraft = true; //resuming the draft
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') { draft.pushTreadling(0);}
    if (key == '2') { draft.pushTreadling(1);}
    if (key == '3') { draft.pushTreadling(2);}
    if (key == '4') { draft.pushTreadling(3);}

    //runDrafts
    if (key == 'r'){
        runDraft = !runDraft;
    }

    //THERMAL PRINTER /////
    if (key == 'p'){
//        print = !print;
        printFullDraft();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
