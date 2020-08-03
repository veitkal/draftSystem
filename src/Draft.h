

#pragma once
#include "ofMain.h"
#include "helpers.h"

class Draft {

public:
  Draft();

  void setup(int _numShafts, int _numWarps, float _orgX,
             float _orgY, float _width, float _height, float _numBoxPad, float _cellSize, ofColor _bg, ofColor _fg);
  void update();
  void draw();
  void setupThreading();
  void setupTieUp();
  void setupTreadling();
  void setupDrawDown();
  void calculateFullPattern();
  vector<int> calcShed(int _treadle);
  void updateThreading();
  void updateTieUp();
  void updateTreadling();
void pushTreadling(int _tempTreadle);
  void updateDrawDown();
  void drawThreading();
  void drawTieUp();
  void drawTreadling();
  void drawDrawDown();
  void drawCurrentRow();
  void drawPattern(float _px, float _py, float _pw, float _ph);
  ofImage draftToImg();
  string getCurrentString();
  ofImage getCurrentImg();




  int numWarps, numShafts, numWeft;
  float orgX, orgY, width, height, wWidth, wHeight, tWidth, tHeight, cellSize, boxPad, cellPad, printWidth, printSize;

  //Corners of boxes from top right
  float threadingX, threadingY, treadlingX, treadlingY, tieUpX, tieUpY, drawDownX, drawDownY, t, noiseSeed1, noiseSeed2;

  //update params
  bool updateWarp, updateWeft;
  //wave params
  float treadlingSin1, treadlingSin2, treadlingNoise1, threadingSin1, threadingSin2, threadingNoise1 ;

  ofColor bg, fg;

  deque<vector<int>> threading;
  vector<vector<int>> tieUp;
  deque<int> treadling;
  deque<vector<int>> drawDown;
  vector<int> shed;
  deque<int> threadingSimple; // a single deque used to draw waveforms in the threading

  //fbo for thermal printing
  ofFbo currentRowFbo;

};
