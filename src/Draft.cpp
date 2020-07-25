
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

  bg = _bg;
  fg = _fg;

  threading.resize(numShafts, vector<int>(numWarps));
  tieUp.resize(numShafts, vector<int>(numShafts));
  treadling.resize(numWeft);
  drawDown.resize(numWeft, vector<int>(numWarps));

  setupThreading();
  setupTieUp();
  setupTreadling();
  setupDrawDown();

  vector<int> testShed = calcShed(3);
    cout << vectorToString(testShed) << endl;
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
       int randVal = (int)ofRandom(numShafts);
       treadling[i] = randVal;
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
  //draw background of box
  ofFill();
  ofSetLineWidth(8);
  ofSetColor(bg);
  ofDrawRectangle(threadingX-2, threadingY-2, wWidth+4, tHeight+4);
  //draw edge
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(fg);
  ofDrawRectangle(threadingX, threadingY, wWidth, tHeight);

  //draw cells
  for(int i = 0; i  < threading.size(); i++) {
      for(int j = 0; j < threading[i].size(); j++) {
//        float x = orgX + wWidth - cellSize - (cellSize * j); //uncomment to draw from top left
//        float y = orgY + tHeight - cellSize - (cellSize * i);//uncomment to draw from top left
        float x = orgX + (cellSize * j);//uncomment to draw from bottom right, the draft way
        float y = orgY + (cellSize * i);//uncomment to draw from bottom right

        //if current index is 1 colour is fg, else bg
        ofColor c = threading[i][j]==1?fg:bg;
        ofFill();
        ofSetColor(c);

        ofDrawRectangle(x, y, cellSize, cellSize);
      }
  }

  //draw grid
  for(int i = 0; i < threading.size(); i++) {
      for(int j = 0; j < threading[i].size(); j++) {
        ofSetColor(fg);
        float x1 = orgX + (j * cellSize);
        float y1 = orgY + (i * cellSize);

        ofDrawLine(x1, orgY, x1, orgY+tWidth);
        ofDrawLine(orgX, y1, orgX + wWidth, y1);
      }
  }

}

//--------------------------------------------------------------

void Draft::drawTieUp() {
  //draw background of box
  ofFill();
  ofSetLineWidth(8);
  ofSetColor(bg);
  ofDrawRectangle(tieUpX-2, tieUpY-2, tWidth+4, tHeight+4);
  //draw edge
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(fg);
  ofDrawRectangle(tieUpX, tieUpY, tWidth, tHeight);

  //draw cells, loop through tieUp arrayy
  for(int i = 0; i < tieUp.size(); i++) {
      for(int j = 0; j < tieUp[0].size(); j++) {
         float x = tieUpX + (i * cellSize); //draw from top left, better for code
         float y = tieUpY + (j * cellSize); //draw from top left
//         float x = tieUpX + (i * cellSize); //draw form bottom left, the draft way
//         float y = tieUpY + tWidth - cellSize - (j * cellSize); //draw form bottom left, the draft way

        ofFill();
        //if current index is 1 colour is fg, else bg
        ofColor c = tieUp[i][j]==1?fg:bg;
        ofSetColor(c);

        ofDrawRectangle(x, y, cellSize, cellSize);
      }
  }

  //draw grid
  for(int i = 0; i < tieUp.size(); i++) {
      for(int j = 0; j < tieUp[i].size(); j++) {
        ofSetColor(fg);
        float x1 = tieUpX + (j * cellSize);
        float y1 = tieUpY + (i * cellSize);

        ofDrawLine(x1, tieUpY, x1, tieUpY+tWidth);
        ofDrawLine(tieUpX, y1, tieUpX + tWidth, y1);
      }
  }

}

//--------------------------------------------------------------

void Draft::drawTreadling() {
  //draw background of box
  ofFill();
  ofSetLineWidth(8);
  ofSetColor(bg);
  ofDrawRectangle(treadlingX-2, treadlingY-2, tWidth+4, wHeight+4);
  //draw edge
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(fg);
  ofDrawRectangle(treadlingX, treadlingY, tWidth, wHeight);

//draw treadling, looping over the deque + number of shafts as to calculate cells in grid
  for(int i = 0; i < treadling.size(); i++) {
      for(int j = 0; j < numShafts; j++) {
         float x = treadlingX + (j * cellSize);
         float y = treadlingY + (i * cellSize);

        ofFill();
        //if check if val at index (ie 0-numShafts-1) is the same as j, ie x index
        //set colour to fg if so
        ofColor c = treadling[i] == j?fg:bg;
        ofSetColor(c);

        ofDrawRectangle(x, y, cellSize, cellSize);
      }

  }

  //draw grid
  for(int i = 0; i < numShafts; i++) {
      for(int j = 0; j < treadling.size(); j++) {
        ofSetColor(fg);
        float x1 = treadlingX + (i * cellSize);
        float y1 =treadlingY + (j * cellSize);

        ofDrawLine(x1,treadlingY, x1, treadlingY+wHeight);
        ofDrawLine(treadlingX, y1, treadlingX + tWidth, y1);
      }
  }
}

//--------------------------------------------------------------

vector<int> Draft::calcShed(int _treadle) {
  vector<int> tempVec;
  for(int i = 0; i < threading[0].size(); i++) {
    int tempVal = 0;
    for(int j = 0; j < tieUp[0].size(); j++) {
        int tieUpVal = tieUp[_treadle][j];
        int threadingVal = threading[j][i];
        tempVal += tieUpVal * threadingVal;
//        converting to binary 0/1
        tempVal = tempVal>0?1:0;
    }
    tempVec.push_back(tempVal);
  }

  return tempVec;


}

//--------------------------------------------------------------
