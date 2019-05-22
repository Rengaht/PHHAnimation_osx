//
//  PSceneTunnel.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PSceneTunnel_h
#define PSceneTunnel_h

#include "PScene.h"
#include "PRoadSign.h"
#include "PRock.h"
#include "PSign.h"

class PSceneTunnel:public PScene{
    
    float _pos_road,_pos_rock,_pos_sign;
    ofFbo _tex_rock,_tex_sign;
    
public:
    static float _speed;
    ofCamera _camera;
    
    PSceneTunnel():PScene(){
        _camera.setPosition(ofVec3f(0,ofGetHeight()/4,ofGetWidth()));
        _camera.setFov(120);
        _camera.setNearClip(0);
        _camera.setFarClip(ofGetWidth()*2);
        
        _mstage=2;
        
        reset();
        initTexture();
    }
    void update(float dt){
        for(auto it=_element.begin();it!=_element.end();){
            (**it).update(_speed,dt);
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        _pos_road+=_speed*1.2;
        addRoad();
        _pos_sign+=_speed;
        addSign();
        
        if(_idx_stage>0){
            _pos_rock-=_speed*10;
            addRock();
        }
        
        if(_speed>10) _speed-=.5;
    }
    void draw(){
        ofClear(255);
//        _tex_sign.draw(0,0);
        
        _camera.begin();
//        ofEnableLighting();
        ofDrawAxis(10);
        
        _tex_sign.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==2) (*e).draw();
        _tex_sign.getTexture().unbind();
        
        _tex_rock.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==1) (*e).draw();
        _tex_rock.getTexture().unbind();
        
        
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        
        _camera.end();

    }
    void reset(){
        PScene::reset();
        
        _pos_sign=_pos_road=2*ofGetWidth();
        _pos_rock=-2*ofGetWidth();
        _speed=10;
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                //                _timer_speed.restart();
                _speed*=2;
                _speed=ofClamp(_speed,10,80);
                break;
            case '.':
            case '>':
                goNextStage();
                break;
            case ',':
            case '<':
                goPrevStage();
                break;
        }
    }
    void addRoad(){
        while(_pos_road>-ofGetWidth()*2){
//            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
//            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PRoadSign(ofVec3f(0,0,_pos_road));
            _element.push_back(p);
            _pos_road-=p->_size.y;
        }
    }
    void addSign(){
        while(_pos_sign>-ofGetWidth()*2){
            //            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            //            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PSign(ofVec3f(0,0,_pos_sign));
            _element.push_back(p);
            _pos_sign-=p->_size.y*ofRandom(1,3);
        }
    }
    void addRock(){
        while(_pos_rock<ofGetWidth()*2){
            if(ofRandom(2)<1) _pos_rock+=ofRandom(.5,1)*ofGetWidth();
            
            auto p=new PRock(ofVec3f(0,0,_pos_rock));
            _element.push_back(p);
            _pos_rock+=p->_size.y;
        }
    }
    void initTexture(){
        
        _tex_rock.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        _tex_sign.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=5;
        float m=ofGetHeight()/c;
        
        _tex_rock.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
        ofSetColor(20);
        ofSetLineWidth(WSTROKE);
        float rat=100;
            for(int i=0;i<c*rat;++i)
            for(int j=0;j<c;++j){
                float dx=ofNoise(i/10.0/rat,j/10.0)-.5;
                float dy=ofRandom(-1,1)*.5;
                ofDrawLine(i*m/rat+dx*m/rat,j*m-dy*m,(i)*m/rat-dy*dx*m/rat,(j+1)*m+dy*m);
            }

        ofPopStyle();
        _tex_rock.end();
        
        
        _tex_sign.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
        ofSetColor(120);
        ofSetLineWidth(WSTROKE);
        ofNoFill();
        c=50;
        m=(float)ofGetHeight()/c;
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float dx=ofNoise(i/5.0,j/5.0)-.5;
                float dy=ofRandom(-1,1)*.5;
//                    ofDrawEllipse(i*m+dx*m,j*m-dy*m,dy*m*5,dy*m*5);
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i+1)*m*dx+dy*dx*m,(j)*m+dy*m);
            }
        
        ofPopStyle();
        _tex_sign.end();
    }
};
#endif /* PSceneTunnel_h */
