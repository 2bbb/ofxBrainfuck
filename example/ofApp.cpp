#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string source = ofxGetBrainfuckSource("Hello Brainfuck, on openFrameworks!!");
    ofLogNotice() << source;
    fuck.setup(source);
    bPause = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < 27; i++) if(!bPause) fuck.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("space: start/pause | r: reset", ofPoint(10, 20));
    
    const vector<int> memoryState = fuck.getCurrentMemoryState();
    for(int i = 0; i < memoryState.size(); i++) {
        ofSetColor((fuck.getCurrentProcessiState() == OFX_BRAINFUCK_ERROR) ? 255 : 0, (fuck.getCurrentProcessiState() == OFX_BRAINFUCK_PROCESS_NOW) &&  (i == fuck.getCurrentPointer()) ? 255 : 0, memoryState[i]);
        ofRect(i % 10 * 40, i / 10 * 40 + 40, 40, 40);
        
        ofSetColor(255, 255, 255);
        ofDrawBitmapString(ofToString(memoryState[i]), ofPoint(i % 10 * 40 + 10, i / 10 * 40 + 60));
    }
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString(fuck.getResult(), ofPoint(10, 380));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        bPause = !bPause;
    } else if(key == 'r') {
        fuck.reset();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
