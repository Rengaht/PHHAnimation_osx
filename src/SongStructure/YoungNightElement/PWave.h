//
//  PWave.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/20.
//

#ifndef PWave_h
#define PWave_h
#include "PElement.h"

class PWave:public PElement{
    ofMesh _mesh;
    ofVec2f _vel;
    float _seg;
    ofColor _color;
public:
     PWave(ofVec2f p,float w,float t){
         _color=ofColor(ofRandom(200,255),ofRandom(80,150),ofRandom(60));
         _layer=1;
         _pos=p;
         init(w);
     }
    void init(float w){
        
        _size=ofVec2f(w*ofRandom(3,6),w*2);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=12;
        float eth=PI/_seg;
        
        float tx=ofGetHeight()/2;
        float ty=ofGetHeight()/2;
        
        float xx=-_size.x/2;
        
        for(float i=0;i<=_seg;++i){
            float th=-eth*i;
            
            _mesh.addVertex(ofVec2f(xx,0));
            _mesh.addVertex(ofVec2f(xx+w*sin(th),w*cos(th)));
            _mesh.addVertex(ofVec2f(xx+w*sin(th+eth),w*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
        _mesh.addVertex(ofVec2f(0,_size.y));
        _mesh.addVertex(ofVec2f(_size.x,_size.y));
        _mesh.addVertex(ofVec2f(0,_size.y));
        
        _mesh.addVertex(ofVec2f(0,_size.y));
        _mesh.addVertex(ofVec2f(_size.x,0));
        _mesh.addVertex(ofVec2f(9,_size.y));
        
//        _mesh.addTexCoord(ofVec2f(tx+w,ty));
        
        xx=_size.x/2;
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            
            _mesh.addVertex(ofVec2f(xx,0));
            _mesh.addVertex(ofVec2f(xx+w*sin(th),w*cos(th)));
            _mesh.addVertex(ofVec2f(xx+w*sin(th+eth),w*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(_pos);
        ofSetColor(_color,255);
        _mesh.draw();
        
        ofPopMatrix();
        ofPopStyle();
    }
    void end(){
        
    }
    void reset(){
        
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
//        _timer_fadein.update(dt_);
        
    }
};

#endif /* PWave_h */
