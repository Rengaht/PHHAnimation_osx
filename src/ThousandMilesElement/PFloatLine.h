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
    
    list<ofMesh> _path;
    
    vector<PPlanet*> _planet;
    int _idx_planet;
    
    
    float _alpha;
    float _angle;
public:
    
    PFloatLine(ofVec2f start_):PElement(){
        _alpha=ofRandom(80);
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
        for(auto& p:_path){
            ofTranslate(ofRandom(-.1,.1)*_size.y,ofRandom(-.1,.1)*_size.y);
            p.draw();
//            p.rotate(ofRandom(TWO_PI));
        }
        
        ofPopMatrix();
        
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
       
        _pos.x-=vel_;//*ofMap(_alpha,180,255,0.5,2);
        if(_pos.x<-_size.x*1.5){
            _dead=true;
        }
        if(ofRandom(10)>1) return;
        _angle+=ofRandom(-1,1);
        //if(_anim_loop.val()==0) _idx_planet=(_idx_planet+1)%_planet.size();
    }
    void init(){
        
        float m=ofRandom(10,30);
        float mv=ofRandom(1,3);
        
        float w=ofGetHeight()*ofRandom(.4,.6);
        float r=ofGetHeight()*ofRandom(.05,.2);
        _size=ofVec2f(w,r);
        
        float sang=-HALF_PI;
        float ang=PI;
        
        for(float i=0;i<m;++i){
            for(float j=0;j<=mv;++j){
//                ofPolyline p;
                ofMesh p;
                
                float tx=i*w/m+ofRandom(-1.2,1.2)*w/m;
                float ty=j*r/mv+ofRandom(-1.5,1.5)*r/mv;
                
                float eang=TWO_PI/ofRandom(3,6);
                vector<float> corner;
                float sang=HALF_PI*3;
                float ang=sang;
                while(ang<sang+TWO_PI){
                    corner.push_back(ang);
                    ang+=ofRandom(.4,1.5)*eang;
                }
                
                int mcorner=corner.size();
                
                
                float rt=ofRandom(.5,1);
                float ttx=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
                float tty=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
                
                ofMesh tm_;
                float mr=_size.y/m*ofRandom(.5,1.2);
                
                tm_.setMode(OF_PRIMITIVE_TRIANGLES);
                for(int i=0;i<mcorner;++i){
                    tm_.addVertex(ofVec2f(tx,ty));
                    
                    float tt=cos(corner[i]);
                    tm_.addVertex(ofVec2f(tx+mr*sin(corner[i]),ty+mr*tt));
                    
                    tt=cos(corner[(i+1)%mcorner]);
                    tm_.addVertex(ofVec2f(tx+mr*sin(corner[(i+1)%mcorner]),ty+mr*tt));
                    
                    tm_.addTexCoord(ofVec2f(ttx,tty));
                    tm_.addTexCoord(ofVec2f(max(ttx+r*rt*sin(corner[i]),0.0f),min((float)ofGetHeight(),tty+r*rt*cos(corner[i]))));
                    tm_.addTexCoord(ofVec2f(max(ttx+r*rt*sin(corner[(i+1)%mcorner]),0.0f),min((float)ofGetHeight(),tty+r*rt*cos(corner[(i+1)%mcorner]))));
                }
                _path.push_back(tm_);
                
            }
            
        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};

#endif /* PFloatLine_h */
