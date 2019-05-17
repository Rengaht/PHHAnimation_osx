//
//  PCloud.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/11.
//

#ifndef PCloud_h
#define PCloud_h

#include "PElement.h"

class PCloud:public PElement{
    
    list<ofMesh> _mesh;
    float _alpha;
public:
    PCloud(float dx_):PElement(){
        _alpha=255;//ofRandom(120,180);
        _pos=ofVec2f(dx_,ofGetHeight()/2-100+ofRandom(-50,0));
        _use_texture=true;
        _layer=2;
        
        init(ofGetHeight()/10*ofRandom(.3,2.5));
    }
    PCloud(ofVec2f dx_):PElement(){
        _alpha=255;//ofRandom(120,180);
        _pos=dx_;
        _use_texture=true;
        _layer=2;
        
        init(ofGetHeight()/5*ofRandom(1,2.5));
    }
    void draw(){
        
        
        ofPushStyle();
        ofSetColor(_alpha);
        
        ofPushMatrix();
        ofTranslate(_pos);
        //ofRotate(90,vel.x,vel.y,vel.z);
        for(auto& m: _mesh) m.draw();
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        _pos.x-=vel_*.5;
        if(_pos.x<-_size.x){
            _dead=true;
        }
    }
    void init(float r){
        
        int m=ofRandom(8,26);
//        float r=ofGetHeight()/10*ofRandom(.3,2.5);
        float rat=ofRandom(.2,.6);
        _size=ofVec2f(r*2,r*rat*2);
        
        for(int k=0;k<m;++k){
        
            
            float eang=TWO_PI/ofRandom(4,8);
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
            float my=ofRandom(-r*rat,r*rat);
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
#endif /* PCloud_h */
