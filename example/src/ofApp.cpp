#include "ofApp.h"

//christie network control reference PDF 020-000789-01-Christie-LIT-MAN-USR-D-Series-TECH-GUID-Multilingual.pdf
//const char *packet = { "0xBE", "0xEF", "0x03", "0x06", "0x00", "0x0E", "0xD2", "0x01", "0x00", "0x00", "0x02", "0x03", "0x00"};

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLogLevel(OF_LOG_VERBOSE);
    //Your projectors IP, and if its not PJLINK try NEC
    
    string baseIP = "192.168.1.254";
    
    projector1.setup(baseIP,Christie_MODE,"");
   
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == '1')  projector1.sendCommand("shutterOff");
    if(key == '2')  projector1.sendCommand("shutterOn");

    
    if(key == 'o')  projector1.sendCommand("powerOff");
    if(key == 'i')  projector1.sendCommand("powerOn");

    
    if(key == '-' || key == '_')  projector1.sendCommand("focusIncrement");
    if(key == '+' || key == '=')  projector1.sendCommand("focusDecrement");
    
    if(key == '{' || key == '[')  projector1.sendCommand("zoomIncrement");
    if(key == '}' || key == ']')  projector1.sendCommand("zoomDecrement");

    if(key == 'q')  projector1.sendCommand("brightGet"); // darkest == 1d60 (96), brightest == 1da0 (160)
    if(key == 'a')  projector1.sendCommand("brightIncrement");
    if(key == 'z')  projector1.sendCommand("brightDecrement");
    
//    if(key == 'w')  projector1.sendCommand("dimGet");
//    if(key == 's')  projector1.sendCommand("dimIncrement");
//    if(key == 'x')  projector1.sendCommand("dimDecrement");

    if(key == 'e')  projector1.sendCommand("ecoGet"); //return 1d01 == eco is used, return 1d == eco is not used
    if(key == 'd')  projector1.sendCommand("ecoOff");
    if(key == 'c')  projector1.sendCommand("ecoOn");
    
    if(key == 'r')  projector1.sendCommand("lampGet"); // dual == 1d, lamp1 == 1d01
    if(key == 'f')  projector1.sendCommand("lampDual");
    if(key == 'v')  projector1.sendCommand("lamp1");
    if(key == 't')  projector1.sendCommand("lamp2");
    if(key == 'g')  projector1.sendCommand("lampAlternate");
    if(key == 'b')  projector1.sendCommand("lampAlternateAuto");
    if(key == 'y')  projector1.sendCommand("lampAlternateCycle");
    
    if(key == '3')  projector1.sendCommand("lamp1TimeLB");
    if(key == '4')  projector1.sendCommand("lamp1TimeHB");
    if(key == '5')  projector1.sendCommand("lamp2TimeLB");
    if(key == '6')  projector1.sendCommand("lamp2TimeHB");
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
