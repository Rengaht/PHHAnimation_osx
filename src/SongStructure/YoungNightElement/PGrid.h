//
//  PGrid.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PGrid_h
#define PGrid_h

#include "PElement.h"

class PGrid:public PElement{
    ofMesh _mesh;
    ofColor _color;
    FrameTimer _timer_fadein;
    
public:
    PGrid(float x,float y,float w,float t){
        if(ofRandom(5)<1) _color=ofColor(255);
        else _color=ofColor(ofRandom(180,255),0,ofRandom(60));
        
        _pos=ofVec2f(x+ofRandom(-.1,.1)*w,y+ofRandom(-.1,.1)*w);
        init(w*ofRandom(1,1.2));
        
        _layer=0;
        _timer_fadein=FrameTimer(t);
        _timer_fadein.restart();
    }
    void init(float w){
//
//        float dx=ofRandom(-.1,.1)*w;
//        float dy=ofRandom(-.1,.1)*w;
        float tx=ofRandom(w,ofGetHeight()-w);
        float ty=ofRandom(w,ofGetHeight()-w);
        
        int index_=floor(ofRandom(6));
        float seg_=50;
        float eth=TWO_PI/seg_;
        
        switch(index_){
            case 0:
                _mesh.addVertex(ofVec2f(0,0));
                _mesh.addVertex(ofVec2f(w,0));
                _mesh.addVertex(ofVec2f(w,w));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                break;
            case 1:
                _mesh.addVertex(ofVec2f(0,0));
                _mesh.addVertex(ofVec2f(0,w));
                _mesh.addVertex(ofVec2f(w,w));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx,ty+w));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                break;
            case 2:
//                for(float i=0;i<=seg_;++i){
//                    float th=eth*i;
//                    _mesh.addVertex(ofVec2f(w/2,w/2));
//                    _mesh.addVertex(ofVec2f(w/2+w/2*sin(th),w/2+w/2*cos(th)));
//                    _mesh.addVertex(ofVec2f(w/2+w/2*sin(th+eth),w/2+w/2*cos(th+eth)));
//
//                    _mesh.addTexCoord(ofVec2f(tx+w/2,ty+w/2));
//                    _mesh.addTexCoord(ofVec2f(tx+w/2+w/2*sin(th),ty+w/2+w/2*cos(th)));
//                    _mesh.addTexCoord(ofVec2f(tx+w/2+w/2*sin(th+eth),ty+w/2*cos(th+eth)));
//                }
                eth=HALF_PI/seg_;
                for(float i=0;i<=seg_;++i){
                    float th=PI+eth*i;
                    _mesh.addVertex(ofVec2f(w,w));
                    _mesh.addVertex(ofVec2f(w+w*sin(th),w+w*cos(th)));
                    _mesh.addVertex(ofVec2f(w+w*sin(th+eth),w+w*cos(th+eth)));
                    
                    _mesh.addTexCoord(ofVec2f(tx,ty+w/2));
                    _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
                    _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
                }
                break;
            case 3:
                eth=HALF_PI/seg_;
                for(float i=0;i<=seg_;++i){
                    float th=eth*i;
                    _mesh.addVertex(ofVec2f(0,0));
                    _mesh.addVertex(ofVec2f(w*sin(th),w*cos(th)));
                    _mesh.addVertex(ofVec2f(w*sin(th+eth),w*cos(th+eth)));
                    
                    _mesh.addTexCoord(ofVec2f(tx,ty+w/2));
                    _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
                    _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
                }
                break;
            case 4:
                _mesh.addVertex(ofVec2f(0,0));
                _mesh.addVertex(ofVec2f(w,0));
                _mesh.addVertex(ofVec2f(w,w));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                
                _mesh.addVertex(ofVec2f(0,0));
                _mesh.addVertex(ofVec2f(0,w));
                _mesh.addVertex(ofVec2f(w,w));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx,ty+w));
                _mesh.addTexCoord(ofVec2f(tx+w,ty+w));
                break;
            case 5:
                break;
        }
        
        
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

#endif /* PGrid_h */

