//
//  ofxBrainfuck.h
//
//  Created by ISHII 2bit
//

#ifndef __ofxBrainfuck__
#define __ofxBrainfuck__

#include "ofMain.h"

string ofxGetBrainfuckSource(string str);

typedef enum {
    OFX_BRAINFUCK_ERROR,
    OFX_BRAINFUCK_PROCESS_NOW,
    OFX_BRAINFUCK_SUCCESS,
    OFX_BRAINFUCK_UNKNOWN
} ofxBrainfuckState;

class ofxBrainfuck {
public:
    void setup(string source);
    void reset();
    ofxBrainfuckState update();
    ofxBrainfuckState interpret();
    
    const vector<int> &getCurrentMemoryState() const;
    ofxBrainfuckState getCurrentProcessiState() const;
    int getCurrentPointer() const;
    int getCurrentCursor() const;
    
    const string getResult() const;
    
private:
    string source;
    
    ofxBrainfuckState state;
    vector<int> memory;
    int pointer;
    int cursor;
    vector<int> loopPosition;
    
    stringstream resultStream;
};

#endif /* defined(__ofxBrainfuck__) */
