//
//  PSceneRoad.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PSceneRoad_h
#define PSceneRoad_h

#include "PScene.h"
#include "PMountain.h"
#include "PRoad.h"
#include "PCloud.h"
#include "PTree.h"

class PSceneRoad:public PScene{
    float _pos_mountain=0;
    ofVec2f _pos_road;
    float _pos_cloud;
    float _pos_tree;
    
    FrameTimer _timer_speed;
    
public:
    static float _speed;
    ofFbo _tex_mountain;
    ofFbo _tex_cloud;
    
    
    PSceneRoad():PScene(){
        _speed=10;
        _mstage=4;
        
        _timer_speed=FrameTimer(1000);
        
        initTexture();
        
        reset();
        
    }
    
    void draw(){
        
        ofBackground(255);
        
        //        _tex_cloud.draw(0,0);
        
        ofDisableArbTex();
        
        _tex_cloud.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==2) (*e).draw();
        _tex_cloud.getTexture().unbind();
        
        _tex_mountain.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==1)
                (*e).draw();
        _tex_mountain.getTexture().unbind();
        
        
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        
        
#ifdef DRAW_DEBUG
        ofPushStyle();
        ofSetColor(0);
        ofDrawBitmapString("stage= "+ofToString(_idx_stage),50,30);
        ofDrawBitmapString("speed= "+ofToString(_speed),120,30);
        ofPopStyle();
#endif
        
    }
    void update(float dt){
        
        //        _timer_speed.update(dt);
        //        _speed=10+(_timer_speed.valEaseOut())*20;
        
        for(auto it=_element.begin();it!=_element.end();){
            switch((**it)._layer){
                case 0:
                    (**it).update(_speed*1.2,dt);
                    break;
                case 1:
                    (**it).update(_speed,dt);
                    break;
                case 2:
                    (**it).update(_speed*.5,dt);
                    break;
            }
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        
        if(_idx_stage>0){
            _pos_mountain-=_speed;
            addMountain();
        }
        if(_idx_stage>1){
            _pos_cloud-=_speed*.5;
            addCloud();
        }
        if(_idx_stage>2){
            _pos_tree-=_speed;
            addTree();
        }
        _pos_road.x-=_speed*1.2;
        addRoad();
        
        if(_speed>10) _speed-=.5;
        //        if(_timer_speed.val()==1) _timer_speed.reset();
    }
    void addMountain(){
        while(_pos_mountain<ofGetWidth()*1.2){
            auto p=new PMountain(_pos_mountain);
            _element.push_back(p);
            _pos_mountain+=p->_size.x*ofRandom(.1,.9);
        }
    }
    void addCloud(){
        while(_pos_cloud<ofGetWidth()*1.2){
            
            if(ofRandom(2)<1) _pos_cloud+=ofRandom(.5,1.5)*ofGetWidth();
            
            auto p=new PCloud(_pos_cloud);
            _element.push_back(p);
            _pos_cloud+=p->_size.x*ofRandom(-.2,.9);
        }
    }
    void addTree(){
        while(_pos_tree<ofGetWidth()*1.2){
            if(ofRandom(4)<1) _pos_tree+=ofRandom(.3,.8)*ofGetWidth();
            
            auto p=new PTree(_pos_tree);
            
            _element.push_back(p);
            _pos_tree+=p->_size.x*ofRandom(-.2,.9);
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
        
        _tex_cloud.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=80;
        float m=ofGetHeight()/c;
        
        _tex_cloud.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
        
        ofNoFill();
        //        ofBeginShape();
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float r=(ofNoise(i/20.0,j/20.0)+ofRandom(-.1,.1));
                if(r<.5) continue;
                r=m;
                int mang=ofRandom(4,16);
                float eang=TWO_PI/(float)mang;
                
                ofSetColor(220);
                ofBeginShape();
                for(int k=0;k<=mang;++k) ofVertex(i*m+r*sin(eang*k+ofNoise(i/40.0+k*j/10.0)),j*m+r*cos(eang*k-ofNoise(i*j/20.0)));
                ofEndShape();
                
                ofSetColor(120,200);
                float dx=ofNoise(i/100.0,j/100.0)-.5;
                float dy=ofRandom(-1,1)*.5;
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i)*m-dy*dx*m,(j+1)*m+dy*m);
                
            }
        //        ofEndShape();
        ofPopStyle();
        _tex_cloud.end();
        
        _tex_mountain.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        c=80;
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
        
        _pos_tree=_pos_mountain=_pos_cloud=ofGetWidth();
        _pos_road=ofVec2f(ofGetWidth(),ofGetHeight()/1.9);
        
    }
    
    void setEffect(int i){
        switch(i){
            case '.':
            case '>':
                goNextStage();
                break;
            case 'a':
                //                _timer_speed.restart();
                _speed*=2;
                _speed=ofClamp(_speed,10,80);
                break;
        }
    }
};

#endif /* PSceneRoad_h */
