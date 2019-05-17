//
//  PRoad.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/11.
//

#ifndef PRoad_h
#define PRoad_h

#include "PElement.h"

class PRoad:public PElement{
    
    ofMesh _mesh;
    float _alpha;
public:
    
    PRoad(ofVec2f start_):PElement(){
        _alpha=ofRandom(120);
        _pos=start_;
        
        _layer=0;
        
        init();
    }
    void draw(){
        
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha);
        ofNoFill();
        
        ofPushMatrix();
        ofTranslate(_pos);
        //ofRotate(90,vel.x,vel.y,vel.z);
        _mesh.draw();
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        _pos.x-=vel_;
        if(_pos.x<-_size.x){
            _dead=true;
        }
    }
    void init(){
        
        int m=ofRandom(14,36);
        float r=ofGetHeight()/8*ofRandom(.2,6);
        
        _mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        float tx=0;
        float ty=0;
        int c=0;
        while(tx<r && c<50){
            if(c==50) tx=r;
            _mesh.addVertex(ofVec2f(tx,ty));
            _size=ofVec2f(tx,ty);
            
            tx+=ofRandom(-.5,1.5)*r/m;
            ty+=ofRandom(-2.5,2.5);
            c++;
        }
        
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};

#endif /* PRoad_h */
