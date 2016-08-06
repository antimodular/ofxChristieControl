/*
 *  pjControl.cpp
 *
 *
 *  Created by Noah Shibley on 8/9/10.
 *  Copyright 2010 Noah Shibley. All rights reserved.
 *
 */

#include "ofxChristieControl.h"
#include "ofMain.h"

ofxChristieControl::ofxChristieControl() {
    connected = false;
    projStatus = false;
}

ofxChristieControl::~ofxChristieControl() {
    
}

bool ofxChristieControl::getProjectorStatus() {
    return projStatus;
}

void ofxChristieControl::setProjectorType(int protocol) { //NEC_MODE, PJLINK_MODE or Christie_MODE
    commMode = protocol;
}

void ofxChristieControl::setup(string IP_add, int protocol, string password) {
    setProjectorIP(IP_add);
    setProjectorType(protocol);
    setProjectorPassword(password);
}

void ofxChristieControl::setProjectorIP(string IP_add) {
    IPAddress = IP_add;
}

void ofxChristieControl::setProjectorPassword(string passwd) {
    password = passwd;
}





void ofxChristieControl::sendCommand(string command, int amount) {
    //https://www.christiedigital.com/SupportDocs/Anonymous/020-000789-01-Christie-LIT-MAN-USR-D-Series-TECH-GUID-Multilingual.pdf
    //https://www.christiedigital.com/SupportDocs/Anonymous/020-000664-03-Christie-LIT-MAN-USR-Q-Series-TECH-GUIDE.pdf
    
    
    string msgRx="";
    
    
    if(!pjClient.isConnected()) {
        pjClient.setVerbose(true);
        connected = pjClient.setup(IPAddress, PJLINK_PORT,true);
        ofLog() << "connection established: " << IPAddress << ":" << PJLINK_PORT <<" = "<<connected;
    }
    
    string authToken = "";
    
    //    //eg. PJLINK 1 604cc14d
    //    if(msgRx[7] == '1') {
    //        ofLog() << "with authentication" << endl;
    //        MD5Engine md5;
    //        md5.reset();
    //        string hash = msgRx.substr(9,8);
    //        ofLog() << hash << endl;
    //        md5.update(hash + password);
    //        authToken = DigestEngine::digestToHex(md5.digest());
    //    }
    


    vector<int> vt;
    
    if(command == "powerGet") vt = {0xBE,0xEF,0x03,0x06,0x00,           0x19,0xd3,0x02,0x00,0x00,0x60,0x00,0x00};
    if(command == "powerOff") vt = {0xBE,0xEF,0x03,0x06,0x00,           0x2a,0xd3,0x01,0x00,0x00,0x60,0x00,0x00};
    if(command == "powerOn") vt = {0xBE,0xEF,0x03,0x06,0x00,            0xba,0xd2,0x01,0x00,0x00,0x60,0x01,0x00};
  
    if(command == "shutterOff") vt = {0xBE,0xEF,0x03,0x06,0x00,         0x63,0x92,0x01,0x00,0x05,0x24,0x01,0x00};
    if(command == "shutterOn") vt = {0xBE,0xEF,0x03,0x06,0x00,          0xf3,0x93,0x01,0x00,0x05,0x24,0x00,0x00};
    
    if(command == "focusIncrement") vt = {0xBE,0xEF,0x03,0x06,0x00,     0x6a,0x93,0x04,0x00,0x00,0x24,0x00,0x00};
    if(command == "focusDecrement") vt = {0xBE,0xEF,0x03,0x06,0x00,     0xbb,0x92,0x05,0x00,0x00,0x24,0x00,0x00};

    if(command == "zoomIncrement") vt = {0xBE,0xEF,0x03,0x06,0x00,      0x96,0x92,0x04,0x00,0x01,0x24,0x00,0x00};
    if(command == "zoomDecrement") vt = {0xBE,0xEF,0x03,0x06,0x00,      0x47,0x93,0x05,0x00,0x01,0x24,0x00,0x00};

    if(command == "brightGet") vt = {0xBE,0xEF,0x03,0x06,0x00,          0x89,0xd2,0x02,0x00,0x03,0x20,0x00,0x00};
    if(command == "brightIncrement") vt = {0xBE,0xEF,0x03,0x06,0x00,    0xef,0xd2,0x04,0x00,0x03,0x20,0x00,0x00};
    if(command == "brightDecrement") vt = {0xBE,0xEF,0x03,0x06,0x00,    0x3e,0xd3,0x05,0x00,0x03,0x20,0x00,0x00};

//    if(command == "dimGet") vt = {0xBE,0xEF,0x03,0x06,0x00,             0x7c,0x22,0x02,0x00,0x07,0x33,0x00,0x00};
//    if(command == "dimIncrement") vt = {0xBE,0xEF,0x03,0x06,0x00,       0x1a,0x22,0x04,0x00,0x07,0x33,0x00,0x00};
//    if(command == "dimDecrement") vt = {0xBE,0xEF,0x03,0x06,0x00,       0xcb,0x23,0x05,0x00,0x07,0x33,0x00,0x00};

    if(command == "ecoGet") vt = {0xBE,0xEF,0x03,0x06,0x00,             0x08,0x23,0x02,0x00,0x00,0x33,0x00,0x00};
    if(command == "ecoOff") vt = {0xBE,0xEF,0x03,0x06,0x00,             0x3b,0x23,0x01,0x00,0x00,0x33,0x00,0x00};
    if(command == "ecoOn") vt = {0xBE,0xEF,0x03,0x06,0x00,              0xab,0x22,0x01,0x00,0x00,0x33,0x00,0x00};
 
    if(command == "lampGet") vt = {0xBE,0xEF,0x03,0x06,0x00,            0x2c,0x21,0x02,0x00,0x0b,0x33,0x00,0x00};
    if(command == "lampDual") vt = {0xBE,0xEF,0x03,0x06,0x00,           0x1f,0x21,0x01,0x00,0x0b,0x33,0x00,0x00};
    if(command == "lamp1") vt = {0xBE,0xEF,0x03,0x06,0x00,              0x8f,0x20,0x01,0x00,0x0b,0x33,0x01,0x00};
    if(command == "lamp2") vt = {0xBE,0xEF,0x03,0x06,0x00,              0x7f,0x20,0x01,0x00,0x0b,0x33,0x02,0x00};
    if(command == "lampAlternate") vt = {0xBE,0xEF,0x03,0x06,0x00,      0xdf,0x2c,0x01,0x00,0x0b,0x33,0x10,0x00};
    if(command == "lampAlternateAuto") vt = {0xBE,0xEF,0x03,0x06,0x00,  0x6b,0x20,0x01,0x00,0x0c,0x33,0x10,0x00};
    if(command == "lampAlternateCycle") vt = {0xBE,0xEF,0x03,0x06,0x00, 0xfb,0x21,0x01,0x00,0x0c,0x33,0x10,0x00};

    if(command == "lampTime1LB") vt = {0xBE,0xEF,0x03,0x06,0x00,         0xc2,0xff,0x02,0x00,0x90,0x10,0x00,0x00};
    if(command == "lampTime1HB") vt = {0xBE,0xEF,0x03,0x06,0x00,         0x2a,0xfd,0x02,0x00,0x9e,0x10,0x00,0x00};
    if(command == "lampTime2LB") vt = {0xBE,0xEF,0x03,0x06,0x00,         0x02,0xae,0x02,0x00,0x90,0x11,0x00,0x00};
    if(command == "lampTime2HB") vt = {0xBE,0xEF,0x03,0x06,0x00,         0xfe,0xaf,0x02,0x00,0x91,0x11,0x00,0x00};


    char packet[13];

    ofLog()<<"sizeof(vt) "<<vt.size();
    for(int i=0; i<vt.size(); i++){
        packet[i] = ofHexToChar(ofToHex(vt[i]));
//        ofLog()<<i<<" "<<ofToHex(vt[i]);
    }
  
    
 
    bool rxTest = pjClient.sendRawBytes(packet, sizeof(packet));
    

    
    //     const unsigned char packet[] = { 0xbe, 0xef, 0x03,  0x06, 0x00, 0x0e, 0xd2, 0x01, 0x00, 0x00, 0x02, 0x03, 0x00};
    
    //    const  char packet[] = { "0xBE", "0xEF", "0x03", "0x06", "0x00", "0x0E", "0xD2", "0x01", "0x00", "0x00", "0x02", "0x03", "0x00"}; //input computerIn
    
    
    //     string packet[] = { "0xBE", "0xEF", "0x03", "0x06", "0x00", "0x0E", "0xD2", "0x01", "0x00", "0x00", "0x02", "0x03", "0x00"}; //input computerIn
    //     string packet[] = { "0xbe", "0xEF", "0x03", "0x06", "0x00", "0x2a", "0xd3", "0x01", "0x00", "0x00", "0x60", "0x00", "0x00"};// power off
    
    //   bool rxTest = pjClient.sendRawMsg(packet, sizeof(packet)); //packet.size());
    
    //    for(int i=0; i<13; i++){
    //        ofLog()<<"str "<<packet[i]<<" hex "<<ofToHex(packet[i]);
    //        bool rxTest = pjClient.sendRaw(packet[i]); //packet.size());
    ////         ofLog()<<"rxTest "<<rxTest;
    //    }
    //    bool rxTest = pjClient.sendRaw("\r");
    
    ofLog()<<"rxTest "<<rxTest;
    
    msgRx = "";
//    for(int i=0; i<msgRx.length(); i++) {
//        msgRx += pjClient.receiveRaw();
//    }
    
    if(pjClient.isConnected()) {
        msgRx = pjClient.receiveRaw();
//        cout << msgRx << endl;
    }
    
    /*
     ofToHex(msgRx) ==
     ACK reply: 06
     When the projector receives the Set, Increment, Decrement or Execute command correctly, the projector changes the setting data for the specified item by [Type], and it returns the code.
     
     NAK reply: 15
     When the projector cannot understand the received command, the projector returns the error code.
     In such a case, check the sending code and send the same command again.
     
     */
    ofLog() << "received response: " << msgRx <<" "<<ofToHex(msgRx)<<" +++";
    ofLog()<<"msgRx.length() "<<msgRx.length();
    
    
//    pjClient.close();
    //connected = false;
}


void ofxChristieControl::sendPJLinkCommand(string command) {
    string msgRx="";
    
    if(!pjClient.isConnected()) {
        pjClient.setVerbose(true);
        connected = pjClient.setup(IPAddress, PJLINK_PORT,true);
        ofLog() << "connection established: " << IPAddress << ":" << PJLINK_PORT << endl;
        
        ofLog()<<"msgRx.length() "<<msgRx.length();
        /*
         string response = "";
         while (msgRx.length() < 8) {
         msgRx = pjClient.receiveRaw();
         ofLog() << "response: " << msgRx << endl;
         }
         ofLog() << "received response: " << msgRx << endl;
         */
    }
    string authToken = "";
    
    //eg. PJLINK 1 604cc14d
    if(msgRx[7] == '1') {
        ofLog() << "with authentication" << endl;
        MD5Engine md5;
        md5.reset();
        string hash = msgRx.substr(9,8);
        ofLog() << hash << endl;
        md5.update(hash + password);
        authToken = DigestEngine::digestToHex(md5.digest());
    }
    
    
    ofLog() << "sending command: " << authToken+command << endl;
    pjClient.sendRaw(authToken+command);
    
    /*
     msgRx = "";
     while (msgRx.length() < 8) {
     msgRx = pjClient.receiveRaw();
     }
     ofLog() << "received response: " << msgRx << endl;
     */
    
    pjClient.close();
    //connected = false;
}

