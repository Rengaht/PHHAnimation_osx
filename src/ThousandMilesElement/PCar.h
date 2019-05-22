//
//  PCar.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/23.
//

#ifndef PCar_h
#define PCar_h
#include "PElement.h"

class PCar:public PElement{
    ofMesh _mesh;
    ofColor _color;
    
public:
    int _stage;
    PCar(float x){
        _color=ofColor(ofRandom(80));
        
        _pos=ofVec2f(x,ofGetHeight()/2+80+ofRandom(-10,10));
        
        _layer=3;
        init();
    }
    void init(){
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float y=0;
        float sw=ofGetHeight()*ofRandom(.05,.08);
        float sh=sw*ofRandom(.1,.3);
        
//        _pos=ofVec2f(ofRandom(-.2,.8)*sw,y);
        _size=ofVec2f(sw,sh*2);
        
        int m=floor(ofRandom(2,3));
        float x=0;
        for(int i=0;i<m;++i){
             float dx=ofRandom(-.1,.1)*sw;
             x+=ofRandom(-.2,.2)*sw;
            
            _mesh.addVertex(ofVec2f(x+dx,y));
            _mesh.addVertex(ofVec2f(x+sw+dx,y-dx));
            _mesh.addVertex(ofVec2f(x+sw,y+sh+dx));
            
            _mesh.addVertex(ofVec2f(x+sw,y+sh+dx));
            _mesh.addVertex(ofVec2f(x+ofRandom(-.1,.1)*sw,y+sh));
            _mesh.addVertex(ofVec2f(x+dx,y));
            
            float ty=ofRandom(.3,.7)*ofGetHeight();
            float tx=ofRandom(.3,.7)*ofGetHeight();
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+sw,ty));
            _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh));
            
            _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh));
            _mesh.addTexCoord(ofVec2f(tx+0,ty+sh));
            _mesh.addTexCoord(ofVec2f(tx+0,ty));
            
           
            sw*=ofRandom(.5,.8);
            sh*=ofRandom(.8,1);
            y-=sh*ofRandom(.5,.9);
        }
       
        
        
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(_pos);
        
        ofSetColor(_color);
        _mesh.draw();
        
        
        ofPopMatrix();
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
        
        _pos.x+=vel_;
        if(_pos.x>ofGetWidth()+_size.x) _dead=true;
        
    }
};

#endif /* PCar_h */
