//
//  ofxBrainfuck.cpp
//
//  Created by ISHII 2bit
//

#include "ofxBrainfuck.h"

char charAtPosition(string str, int position) {
    if(position < 0 || str.length() <= position) {
        ofLogError() << "Index out of bounds";
        return '\0';
    } else {
        return str[position];
    }
}

void repeat(stringstream &stream, string str, int n) {
    string res = "";
    for(int i = 0; i < n; i++) {
        stream << str;
    }
}

string createSourcePieces(stringstream &stream, int num, string op) {
    float sqrtNum = sqrtf(num);
    int m = num, n = num, r = num;
    for(int i = 0; i < sqrtNum; i++) {
        for(int j = 0; j < sqrtNum; j++) {
            if((i + j + num - i * j) < m + n + r) {
                m = i;
                n = j;
                r = num - i * j;
            }
        }
    }
    
    repeat(stream, "+", m);
    stream << "[>";
    repeat(stream, op, n);
    stream << "<-]>";
    repeat(stream, op, r);
    stream << ".";
    return stream.str();
}

string ofxGetBrainfuckSource(string str) {
    stringstream stream;
    repeat(stream, "+", 8);
    stream << "[>";
    repeat(stream, "+", 8);
    stream << "<-]>+[>";
    repeat(stream, ">+>", str.length());
    repeat(stream, "<<", str.length());
    stream << "<-]";
    for(int i = 0; i < str.length(); i++) {
        int c = charAtPosition(str, i) - 65;
        char sign = c < 0 ? -1 : 1;
        c *= sign;
        stream << ">";
        string sourcePiece = createSourcePieces(stream, c, sign < 0 ? "-" : "+");
    }
    
    return stream.str();
}

void ofxBrainfuck::setup(string source) {
    this->source = source;
    this->reset();
}

void ofxBrainfuck::reset() {
    memory.clear();
    memory.push_back(0);
    pointer = 0;
    cursor = 0;
    resultStream.str("");
    resultStream.clear(stringstream::goodbit);
    state = OFX_BRAINFUCK_PROCESS_NOW;
}

ofxBrainfuckState ofxBrainfuck::update() {
    if(state != OFX_BRAINFUCK_PROCESS_NOW) return state;
    
    char x = charAtPosition(source, cursor);
    switch(x) {
        case '>':
            pointer++;
            if(memory.size() <= pointer) {
                memory.push_back(0);
            }
            break;
        case '<':
            pointer--;
            if(pointer < 0) {
                ofLogError("Negative Memory Index");
                return (state = OFX_BRAINFUCK_ERROR);
            }
            break;
        case '+':
            memory[pointer]++;
            break;
        case '-':
            memory[pointer]--;
            break;
        case '.':
            putchar(memory[pointer]);
            resultStream << (char)memory[pointer];
            break;
        case ',':
            memory[pointer] = getchar();
            break;
        case '[':
            if(0 == memory[pointer]) {
                while (charAtPosition(source, cursor) != ']') {
                    cursor++;
                }
            } else {
                loopPosition.push_back(cursor);
            }
            break;
        case ']':
            if(loopPosition.size() == 0) {
                ofLogError("Loop Bracket is Unbalance");
                return (state = OFX_BRAINFUCK_ERROR);
            }
            cursor = loopPosition[loopPosition.size() - 1] - 1;
            loopPosition.pop_back();
            break;
    }
    cursor++;
    
    return (state = cursor < source.length() ? OFX_BRAINFUCK_PROCESS_NOW : OFX_BRAINFUCK_SUCCESS);
}

ofxBrainfuckState ofxBrainfuck::interpret() {
    while(true) {
        ofxBrainfuckState state = update();
        if(state != OFX_BRAINFUCK_PROCESS_NOW) {
            return state;
        }
    }
    return OFX_BRAINFUCK_UNKNOWN;
}

const vector<int> &ofxBrainfuck::getCurrentMemoryState() const {
    return memory;
}

ofxBrainfuckState ofxBrainfuck::getCurrentProcessiState() const {
    return state;
}

int ofxBrainfuck::getCurrentPointer() const {
    return pointer;
}

int ofxBrainfuck::getCurrentCursor() const {
    return cursor;
}

const string ofxBrainfuck::getResult() const {
    return resultStream.str();
}