//
//  PSmoke.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PSmoke_h
#define PSmoke_h

#define SMOKE_VEL 2.0
#include "PElement.h"

class PSmoke:public PElement{
    ofMesh _mesh;
    ofColor _color;
    FrameTimer _timer_fadein;
    ofVec2f _vel;
public:
    PSmoke(ofVec2f p,ofVec2f v,float w,float t){
        //_color=ofColor(ofRandom(180,255),ofRandom(80,150),ofRandom(60));
        _color=ofColor(255);
        _pos=p;
        _vel=v;
        init(w);
        
        _layer=0;
        _timer_fadein=FrameTimer(t);
        _timer_fadein.restart();
    }
    void init(float w){
        
        _size=ofVec2f(w,w);
        float r=w/2;
        
        float eang=TWO_PI/ofRandom(4,8);
        vector<float> corner;
        float sang=0;
        float ang=sang;
        while(ang<sang+TWO_PI){
            corner.push_back(ang);
            ang+=ofRandom(.4,1.5)*eang;
        }
        
        int mcorner=corner.size();
        
        
        float rt=ofRandom(.2,.5);
        float tx=ofGetHeight()/2+ofRandom(-2,2)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
        float ty=ofGetHeight()/2+ofRandom(-2,2)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
        
    
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        for(int i=0;i<mcorner;++i){
            _mesh.addVertex(ofVec2f(0,0));
            
            float tt=cos(corner[i]);
            _mesh.addVertex(ofVec2f(r*sin(corner[i]),r*tt));
            
            tt=cos(corner[(i+1)%mcorner]);
            _mesh.addVertex(ofVec2f(r*sin(corner[(i+1)%mcorner]),r*tt));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(max((float)(tx+r*rt*cos(corner[i])),0.0f),min((float)ofGetHeight(),(float)(ty+r*rt*sin(corner[i])))));
            _mesh.addTexCoord(ofVec2f(max((float)(tx+r*rt*cos(corner[(i+1)%mcorner])),0.0f),min((float)ofGetHeight(),(float)(ty+r*rt*sin(corner[(i+1)%mcorner])))));
        }
        
        
    }
    
    void draw(){
        ofPushMatrix();
        ofTranslate(_pos);
        ofRotate(-_vel.angle(ofVec2f(1,0)));
        
        ofPushStyle();
        ofSetColor(_color,255*_timer_fadein.valEaseOut());
        ofFill();
        
        _mesh.draw();
        
        ofPopStyle();
        
        ofPopMatrix();
    }
    void end(){
        
    }
    void reset(){
        
    }
    void update(ofVec2f wind_,float dt_){
        PElement::update(0,dt_);
        _timer_fadein.update(dt_);
        
        _pos+=_vel;
        _vel+=wind_*ofMap(_pos.y,0,ofGetWidth(),0,1);
        
        if(_pos.x<-_size.x || _pos.x>ofGetWidth() || _pos.y<-_size.y || _pos.y>ofGetHeight()+_size.y) _dead=true;
    }
};

#endif /* PSmoke_h */
