
#include "ofMain.h"
#include "Draft.h"
#include "ofApp.h"


Draft::Draft()
{

}

void Draft::setup(int _numShafts, int _numWarps, float _orgX,
                  float _orgY, float _width, float _height, float _numBoxPad, float _cellSize, ofColor _bg, ofColor _fg){

  numShafts = _numShafts;
  numWarps = _numWarps;
  orgX = _orgX;
  orgY = _orgY;
  width = _width;
  height = _height;
  cellSize = _cellSize;

  boxPad = _numBoxPad * cellSize; //box padding
  wWidth = numWarps * cellSize; //width of warp and pattern box
  tWidth = numShafts * cellSize; // width of tieUp box
  tHeight = numShafts* cellSize; //height of tieUpBox
//  wHeight = height - (tHeight+boxPad); //height of draw down and treadling box
  numWeft = floor((height - (tHeight+boxPad))/cellSize);
  wHeight = numWeft*cellSize;
  cout << numWeft << endl;

  //Corners of boxes from top right
  threadingX = orgX;
  threadingY = orgY;
  tieUpX = orgX+wWidth+boxPad;
  tieUpY = orgY;
  treadlingX = orgX+wWidth+boxPad;
  treadlingY = orgY + boxPad + tHeight;
  drawDownX = orgX;
  drawDownY = orgY + boxPad+ tHeight;

  threading.resize(numShafts, vector<int>(numWarps));
  tieUp.resize(numShafts, vector<int>(numShafts));
  treadling.resize(numWeft);
  drawDown.resize(numWeft, vector<int>(numWarps));

  setupThreading();
  setupTieUp();
  setupTreadling();
  setupDrawDown();

}

//--------------------------------------------------------------


void Draft::update(){
    updateThreading();
    updateTieUp();
    updateTreadling();


}

//--------------------------------------------------------------

void Draft::draw(){

  ofFill();

  ofSetColor(110,20,110);
  ofDrawRectangle(threadingX, threadingY, wWidth, tHeight);

  ofSetColor(10,20,110);
  ofDrawRectangle(tieUpX, tieUpY, tWidth, tHeight);

  ofSetColor(10,110,110);
  ofDrawRectangle(drawDownX, drawDownY,  wWidth, wHeight);

  ofSetColor(75,90,50);
  ofDrawRectangle(treadlingX, treadlingY,  tWidth, wHeight);

  drawThreading();
  drawTieUp();
  drawTreadling();

}

//--------------------------------------------------------------

void Draft::setupThreading() {

    for(int i = 0; i < threading.size(); i++) {
        for(int j = 0; j < threading[0].size(); j++) {
            int randVal = (int)ofRandom(2);
            threading[i][j] = randVal;
        }
    }

    for(int i = 0; i < threading.size(); i++) {
    cout << vectorToString(threading[i]) << endl;
    }




}

//--------------------------------------------------------------

void Draft::setupTieUp() {
    for(int i = 0; i < tieUp.size(); i++) {
      for(int j = 0; j < tieUp[0].size(); j++) {
        int randVal = (int)ofRandom(2);
        tieUp[i][j] = randVal;
      }
    }

    for(int i = 0; i < tieUp.size(); i++) {
      cout << vectorToString(tieUp[i]) << endl;
    }

}

//--------------------------------------------------------------

void Draft::setupTreadling() {
    for(int i = 0; i < treadling.size(); i++) {
       int randVal = (int)ofRandom(numShafts + 1);
       cout << randVal << endl;
    }

}

//--------------------------------------------------------------

void Draft::setupDrawDown() {

}

//--------------------------------------------------------------
//--------------------------------------------------------------


void Draft::updateThreading() {
}

//--------------------------------------------------------------

void Draft::updateTieUp() {
}

//--------------------------------------------------------------

void Draft::updateTreadling() {
}

//--------------------------------------------------------------
//--------------------------------------------------------------


void Draft::drawThreading() {
}

//--------------------------------------------------------------

void Draft::drawTieUp() {
}

//--------------------------------------------------------------

void Draft::drawTreadling() {
}

//--------------------------------------------------------------
