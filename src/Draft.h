

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
  void updateThreading();
  void updateTieUp();
  void updateTreadling();
  void drawThreading();
  void drawTieUp();
  void drawTreadling();




  int numWarps, numShafts, numWeft;
  float orgX, orgY, width, height, wWidth, wHeight, tWidth, tHeight, cellSize, boxPad, cellPad;

  //Corners of boxes from top right
  float threadingX, threadingY, treadlingX, treadlingY, tieUpX, tieUpY, drawDownX, drawDownY;

  deque<vector<int>> threading;
  vector<vector<int>> tieUp;
  deque<int> treadling;
  deque<vector<int>> drawDown;

};
