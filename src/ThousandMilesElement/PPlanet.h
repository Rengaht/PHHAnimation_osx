//
//  PPlanet.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PPlanet_h
#define PPlanet_h
#include "PElement.h"

class PPlanet:public PElement{
    
    list<ofMesh> _mesh;
    float _alpha;
    float _angle;
    float _vel_angle;
public:
    
    PPlanet(ofVec2f start_):PElement(){
        _alpha=ofRandom(180,255);
        _pos=start_;
        _anim_loop=FrameTimer(ofRandom(4000,8000),ofRandom(500));
        _anim_loop.restart();
        
        _angle=ofRandom(360);
        _vel_angle=ofRandom(-1,1);
        
        _layer=1;
        
        init();
    }
    void draw(){
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha/2);
        
        ofPushMatrix();
        ofTranslate(_pos);
        ofRotate(_angle);
        ofTranslate(10,10);
        
        for(auto& p:_mesh) p.draw();
        ofPopMatrix();
        
        ofPopStyle();
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha);
        
        ofPushMatrix();
        ofTranslate(_pos);
        ofRotate(_angle);
        
        for(auto& p:_mesh) p.draw();
        ofPopMatrix();
        
        ofPopStyle();
        
        
    }
    void update(float vel_,float dt_){
        PElement::update(vel_,dt_);
        _angle+=_vel_angle*_anim_loop.valEaseOut();
        
        //if(_anim_loop.val()==0) _vel_angle=ofRandom(-10,10);
        
        _pos.x-=vel_*ofMap(_alpha,180,255,0.5,2);
        if(_pos.x<-_size.x){
            _dead=true;
        }
    }
    void init(){
        
        int m=ofRandom(6,12);
        float r=ofGetHeight()/20*ofRandom(.3,2.5);
        float rat=ofRandom(.3,.7);
        _size=ofVec2f(r*2,r*rat*2);
        
        for(int k=0;k<m;++k){
            
            
            float eang=TWO_PI/ofRandom(3,8);
            vector<float> corner;
            float sang=HALF_PI*3;
            float ang=sang;
            while(ang<sang+TWO_PI){
                corner.push_back(ang);
                ang+=ofRandom(.4,1.5)*eang;
            }
            
            int mcorner=corner.size();
            
            
            float rt=ofRandom(.8,1);
            float tx=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
            float ty=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
            
            float mx=ofRandom(-r,r);
            float my=ofRandom(-r*rat*2,r*rat*2);
            ofMesh tm_;
            
            tm_.setMode(OF_PRIMITIVE_TRIANGLES);
            for(int i=0;i<mcorner;++i){
                tm_.addVertex(ofVec2f(mx,my));
                
                float tt=cos(corner[i]);
                tm_.addVertex(ofVec2f(mx+r*sin(corner[i]),my+r*rat*tt));
                
                tt=cos(corner[(i+1)%mcorner]);
                tm_.addVertex(ofVec2f(mx+r*sin(corner[(i+1)%mcorner]),my+r*rat*tt));
                
                tm_.addTexCoord(ofVec2f(tx,ty));
                tm_.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[i]),0.0f),min((float)ofGetHeight(),ty+r*rt*rat*cos(corner[i]))));
                tm_.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[(i+1)%mcorner]),0.0f),min((float)ofGetHeight(),ty+r*rt*rat*cos(corner[(i+1)%mcorner]))));
            }
            _mesh.push_back(tm_);
        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
};

#endif /* PPlanet_h */
