#include "helpers.h"

//////CONVERT VECTOR OF INTS TO STRING//////
string vectorToString(vector<int> tempVec) {
        stringstream ss;
        copy( tempVec.begin(), tempVec.end(), ostream_iterator<int>(ss)); //mod
        string currentString = ss.str();
        currentString = currentString.substr(0, currentString.length());  // get rid of the trailing space
        return currentString;
}

////////CONVERT 2d VECTOR OF INTS TO STRING//////
//string vectorToString(vector<vector<int>> tempVec) {
//    string finalString;
//    for(int i = 0; i < tempVec.size(); i++) {
//        stringstream ss;
//        copy( tempVec[i].begin(), tempVec[i].end(), ostream_iterator<int>(ss)); //mod
//        string currentString = ss.str();
//        currentString = currentString.substr(0, currentString.length()-1);  // get rid of the trailing space
//        finalString += currentString;
//    }
//        return finalString;
//}
