#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //    ofBackground(0);
    ofSetFrameRate(30);

    bg = ofColor(255); //background colour draft
    fg = ofColor(0); //foreground colour draft

    numShafts = 4;
    numWarps = 30; //number of warps
    offsetX = 10; //offset where to begin drawing draft
    offsetY = 10;
    orgX = offsetX; //origin of draft ie translated 0
    orgY = offsetY;
    width = 800 - (offsetX * 2); //temporary size
    height = 480 - (offsetY * 2);
    numBoxPad = 1; //padding between drawnBoxes, calculated as a number of cells ie n*cellSize
    updateRate = 30;

        cellSize = width / (numWarps+numShafts + numBoxPad); //size of cells in draft

    draft.setup(numShafts, numWarps, orgX, orgY, width, height, numBoxPad, cellSize, bg, fg);

}

//--------------------------------------------------------------
void ofApp::update(){
//  if (ofGetFrameNum() % 30 == 0) {
    draft.update();
//  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofSetColor(0);
  ofFill();
  ofDrawRectangle(0,0, 800, 480);

  draft.draw();

  ofSetColor(0);
  ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps"    , 20, 20);


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
