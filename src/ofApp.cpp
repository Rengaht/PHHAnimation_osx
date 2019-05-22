#include "ofApp.h"


float PSceneRoad::_speed=0.001;
float PSceneTunnel::_speed=10;
float PSceneFloat::_speed=8;
//float PSceneSmoke::_speed=1;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofHideCursor();
    
    _recording=false;
	_idx_song=0;
	_song.push_back(new PThousandMiles());
	_song.push_back(new PYoungNight());

	_last_millis=ofGetElapsedTimeMillis();

    _NDIsender.setMetaData("HHAnimation", "hhndi", "ofxNDI", "0.0.0", "", "", "");
	_fbo.allocate(ofGetWidth(),ofGetHeight(),GL_RGB);
    
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableTextureEdgeHack();
}

//--------------------------------------------------------------
void ofApp::update(){

	_dmillis=ofGetElapsedTimeMillis()-_last_millis;
	_last_millis+=_dmillis;

	
	_song[_idx_song]->update(_dmillis);
    
	
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofEnableAlphaBlending();
    
	_fbo.begin();
    //ofBackground(255,0,0);
    ofClear(255);
		_song[_idx_song]->draw();
	_fbo.end();

    _fbo.readToPixels(_pixels);
    _NDIsender.send(_pixels);

	_fbo.draw(0,0);

#ifdef DRAW_DEBUG
	ofPushStyle();
	ofSetColor(255,0,0);
		ofDrawBitmapString(ofToString(ofGetFrameRate()),0,10);
	ofPopStyle();
#endif
    
    if(_recording) ofSaveFrame("tmp_####.png");
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case '1':
		case '2':
			setScene(key-'1');
			break;
//        case 'p':
//        case 'P':
//            _song[_idx_song]->reset();
//            break;
        case ' ':
            _recording=!_recording;
            break;
        default:
            mapEffect(key);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ofSaveFrame("capture_####.png");
}

void ofApp::setScene(int set_){
	
	_idx_song=set_;
	_song[set_]->reset();
}

void ofApp::mapEffect(int key_){
    (*_song[_idx_song]).setEffect(key_);
}
