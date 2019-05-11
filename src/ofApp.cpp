#include "ofApp.h"

float PYoungNight::_speed=1;
float PThousandMiles::_speed=0.001;

//--------------------------------------------------------------
void ofApp::setup(){

	_idx_scene=0;
	_scene.push_back(new PThousandMiles());
	_scene.push_back(new PYoungNight());

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

	
	_scene[_idx_scene]->update(_dmillis);
    
	
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofEnableAlphaBlending();
    
	_fbo.begin();
    //ofBackground(255,0,0);
    ofClear(255);
		_scene[_idx_scene]->draw();
	_fbo.end();

    _fbo.readToPixels(_pixels);
    //_NDIsender.send(_pixels);

	_fbo.draw(0,0);

	ofPushStyle();
	ofSetColor(255,0,0);
		ofDrawBitmapString(ofToString(ofGetFrameRate()),0,10);
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch(key){
		case '1':
		case '2':
			setScene(key-'1');
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

void ofApp::setScene(int set_){
	
	_idx_scene=set_;
	_scene[set_]->init();
}
