//
//  PFloatLine.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/17.
//

#ifndef PFloatLine_h
#define PFloatLine_h
#include "PElement.h"
#include "PPlanet.h"

class PFloatLine:public PElement{
    
    list<ofPolyline> _path;
    
    vector<PPlanet*> _planet;
    int _idx_planet;
    
    
    float _alpha;
    float _angle;
public:
    
    PFloatLine(ofVec2f start_):PElement(){
        _alpha=ofRandom(80,200);
        _pos=start_;
        _angle=ofRandom(-60,60);
        
        _layer=0;
        
        init();
    }
    void addPlanet(PPlanet* p){
        _planet.push_back(p);
    }
    void draw(){
        
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
        ofRotate(_angle);
        ofTranslate(-ofGetWidth()/2,-ofGetHeight()/2);
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha);
        //        ofNoFill();
        
        ofPushMatrix();
        ofTranslate(_pos);
        for(auto& p:_path) p.draw();
        
        ofPopMatrix();
        
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
       
        _pos.x-=vel_;//*ofMap(_alpha,180,255,0.5,2);
        if(_pos.x<-_size.x*1.5){
            _dead=true;
        }
        
        //if(_anim_loop.val()==0) _idx_planet=(_idx_planet+1)%_planet.size();
    }
    void init(){
        
        float m=ofRandom(10,22);
        float mv=ofRandom(3,5);
        
        float w=ofGetHeight()*ofRandom(.8,1.8);
        float r=ofGetHeight()*ofRandom(.2,.5);
        _size=ofVec2f(w,r);
        
        float sang=-HALF_PI;
        float ang=PI;
        
        for(float i=0;i<m;++i){
            for(float j=0;j<=mv;++j){
                ofPolyline p;
                float tx=i*w/m+ofRandom(-1.2,1.2)*w/m;
                float ty=j*r/mv+ofRandom(-1.5,1.5)*r/mv;
                
                int mk=ofRandom(3,12);
                float ll=ofRandom(.5,2.5)*w/m/mk;
                
                for(int k=0;k<mk;++k)
                    p.addVertex(ofVec2f(tx+k*ll*ofNoise(tx*i*k)*2,ty+ofNoise(j*k/8.0)*.5*r/mv));
                
                _path.push_back(p);
            }
            
        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};

#endif /* PFloatLine_h */
