//
//  PTree.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PTree_h
#define PTree_h

#include "PElement.h"

class PTree:public PElement{
    
    list<ofMesh> _mesh;
    float _alpha;
public:
    PTree(float dx_):PElement(){
        _alpha=255;//ofRandom(120,180);
        _pos=ofVec2f(dx_,ofGetHeight()/2+ofRandom(-50,0));
        _use_texture=true;
        _layer=1;
        
        init();
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
        _pos.x-=vel_*ofMap(_pos.y+_size.y,ofGetHeight()/2-100,ofGetHeight()/2,.2,1);
        if(_pos.x<-_size.x){
            _dead=true;
        }
    }
    void init(){
        
        int m=ofRandom(12,20);
        float r=ofGetHeight()/40*ofRandom(.3,1.5);
        float rat=ofRandom(.2,1);
        _size=ofVec2f(r*2,r*rat*2);
        
        for(int k=0;k<m;++k){
            
            
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
            
            float mx=ofRandom(-r,r);
            float my=ofRandom(-r*rat,r*rat);
            float tang=(mx>0)?-PI/4:PI/4;
            
            ofMesh tm_;
            
            tm_.setMode(OF_PRIMITIVE_TRIANGLES);
            for(int i=0;i<mcorner;++i){
                tm_.addVertex(ofVec2f(mx,my));
                
                float tt=cos(corner[i]);
                tm_.addVertex(ofVec2f(mx+r*sin(corner[i]),my+r*tt));
                
                tt=cos(corner[(i+1)%mcorner]);
                tm_.addVertex(ofVec2f(mx+r*sin(corner[(i+1)%mcorner]),my+r*tt));
                
                tm_.addTexCoord(ofVec2f(tx,ty));
                tm_.addTexCoord(ofVec2f(max((float)(tx+r*rt*cos(corner[i]+tang)),0.0f),min((float)ofGetHeight(),(float)(ty+r*rt*sin(corner[i]+tang)))));
            tm_.addTexCoord(ofVec2f(max((float)(tx+r*rt*cos(corner[(i+1)%mcorner]+tang)),0.0f),min((float)ofGetHeight(),(float)(ty+r*rt*sin(corner[(i+1)%mcorner]+tang)))));
            }
            _mesh.push_back(tm_);
        }
    }
   
    
    void end(){
        
    }
    void reset(){
        
    }
};

#endif /* PTree_h */
