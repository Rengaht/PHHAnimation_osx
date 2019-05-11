#ifndef PTHOUSAND_MILES_H
#define PTHOUSAND_MILES_H

#include "PScene.h"
#include "PMountain.h"
#include "PRoad.h"

class PThousandMiles:public PScene{
    float _pos_mountain=0;
    ofVec2f _pos_road;
public:
    static float _speed;
    ofFbo _tex_mountain;
    ofFbo _tex_grass;
    
    PThousandMiles():PScene(){
		_speed=10;
        _mstage=2;
        
        initTexture();
        
        _pos_mountain=ofGetWidth();
        _pos_road=ofVec2f(ofGetWidth(),ofGetHeight()/1.9);
        //addRoad();
	}

	void draw(){

		ofBackground(255);
		
//        _tex_mountain.draw(0,0);
        
//        ofEnableNormalizedTexCoords();
        ofDisableArbTex();
        
        _tex_mountain.getTexture().bind();
        for(auto& e: _element)
            if((*e)._use_texture) (*e).draw();
        _tex_mountain.getTexture().unbind();
        
        
        for(auto& e: _element)
            if(!(*e)._use_texture) (*e).draw();
        
//        ofDisableNormalizedTexCoords();
#ifdef DRAW_DEBUG
        ofPushStyle();
        ofSetColor(0);
        ofDrawBitmapString("Thousand Mlles",50,50);
        ofDrawBitmapString(ofToString(_idx_stage),50,30);
        ofPopStyle();
#endif
        
	}
    void update(float dt){
        for(auto it=_element.begin();it!=_element.end();){
            (**it).update(_speed,dt);
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        
        if(_idx_stage>0){
            _pos_mountain-=_speed;
            addMountain();
        }
        _pos_road.x-=_speed*1.2;
        addRoad();
    }
    void addMountain(){
        while(_pos_mountain<ofGetWidth()*1.2){
            auto p=new PMountain(_pos_mountain);
            _element.push_back(p);
            _pos_mountain+=p->_size.x*ofRandom(.1,.9);
        }
    }
    void addRoad(){
        while(_pos_road.x<ofGetWidth()*1.2){
            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PRoad(_pos_road);
            _element.push_back(p);
            _pos_road+=p->_size;
        }
    }
    void initTexture(){
        
        _tex_grass.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=50;
        float m=ofGetHeight()/c;
        _tex_grass.begin();
            ofClear(255,255,255,0);
            ofSetColor(0);
            for(int i=0;i<c;++i)
                for(int j=0;j<c;++j){
                    float dx=ofNoise(i/10.0,j/10.0)-.5;
                    float dy=ofRandom(-1,1)*.5;
                    ofDrawLine(i*m+dx*m,j*m-dy*m,(i+1)*m+dy*m,(j)*m+dx*m);
                }
        _tex_grass.end();
        
        _tex_mountain.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        c=100;
        m=ofGetHeight()/c;
        _tex_mountain.begin();
        ofClear(255,255,255,0);
        ofSetColor(0);
        ofSetLineWidth(WSTROKE);
        
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float dx=ofNoise(i/10.0,j/10.0)-.5;
                float dy=ofRandom(-1,1)*.5;
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i)*m+dy*m,(j+1)*m+dx*m);
            }
        _tex_mountain.end();
    }
    void reset(){
        PScene::reset();
        _pos_mountain=ofGetWidth();
        _pos_road=ofVec2f(ofGetWidth(),ofGetHeight()/1.9);
        
    }
};


#endif
