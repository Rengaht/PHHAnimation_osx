//
//  PPLine.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PPLine_h
#define PPLine_h

#include "PElement.h"

class PPLine:public PElement{
    ofMesh _mesh;
    ofColor _color;
    FrameTimer _timer_fadein;
public:
    PPLine(float x,float w,float t){
        _color=ofColor(ofRandom(180,255),ofRandom(80,150),ofRandom(60));
        _pos=ofVec2f(x,0);
        init(w);
        
        _layer=0;
        _timer_fadein=FrameTimer(t);
        _timer_fadein.restart();
    }
    void init(float w){
        
        float h=ofRandom(.5,1)*ofGetHeight();
        float dx=ofRandom(-.1,.1)*w;
        float dy=ofRandom(-.1,.1)*h;
        
        _mesh.addVertex(ofVec2f(dx,0));
        _mesh.addVertex(ofVec2f(0,h+dy));
        _mesh.addVertex(ofVec2f(w-dx,h));

        float tx=ofRandom(0,ofGetHeight()-w-dx);
//        ofLog()<<"tx "<<tx<<"  "<<w;
        _mesh.addTexCoord(ofVec2f(tx+dx,0));
        _mesh.addTexCoord(ofVec2f(tx,h+dy));
        _mesh.addTexCoord(ofVec2f(tx+w-dx,h));
        
        _mesh.addVertex(ofVec2f(w-dx,h));
        _mesh.addVertex(ofVec2f(w,dx));
        _mesh.addVertex(ofVec2f(dx,0));

        _mesh.addTexCoord(ofVec2f(tx+w-dx,h));
        _mesh.addTexCoord(ofVec2f(tx+w,dx));
        _mesh.addTexCoord(ofVec2f(tx+dx,0));
        

    }
    
    void draw(){
        ofPushMatrix();
        ofTranslate(_pos);
        
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
    void update(float vel_,float dt_){
        PElement::update(vel_,dt_);
        _timer_fadein.update(dt_);
    }
};


#endif /* PPLine_h */
