//
//  PSun.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PSun_h
#define PSun_h

#include "PElement.h"

class PSea:public PElement{
     ofMesh _mesh;
    ofColor _color;
public:
    PSea(){
        _color=ofColor(ofRandom(20),ofRandom(20),ofRandom(120,255));
        _layer=0;
        init();
    }
    void init(){
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float y=ofRandom(.3,.8)*ofGetHeight();
        float sw=ofGetWidth();
        float sh=ofGetHeight()-y;
        _mesh.addVertex(ofVec2f(0,y));
        _mesh.addVertex(ofVec2f(sw,y));
        _mesh.addVertex(ofVec2f(sw,y+sh));
        
        _mesh.addVertex(ofVec2f(sw,y+sh));
        _mesh.addVertex(ofVec2f(0,y+sh));
        _mesh.addVertex(ofVec2f(0,y));
        
        float ty=ofRandom(0,y);
        _mesh.addTexCoord(ofVec2f(0,ty));
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty));
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty+sh));
        
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty+sh));
        _mesh.addTexCoord(ofVec2f(0,ty+sh));
        _mesh.addTexCoord(ofVec2f(0,ty));
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        
        ofSetColor(_color,255);
        _mesh.draw();
        
        ofPopMatrix();
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
        //_timer_fadein.update(dt_);
        
        
        if(ofRandom(10)>1) return;
        
        float ty=ofGetFrameNum()%(ofGetHeight()/2);
        float sh=ofGetHeight()-ty;
        float tx=0;//ofGetHeight()/2+ofRandom(-10,10);
        float sw=ofGetHeight()-tx;
        
        _mesh.clearTexCoords();
        _mesh.addTexCoord(ofVec2f(tx,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh));
        
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh));
        _mesh.addTexCoord(ofVec2f(tx,ty+sh));
        _mesh.addTexCoord(ofVec2f(tx,ty));
    }
};

class PSunset:public PElement{
    ofMesh _mesh;
    ofMesh _mesh_sea;
    
    ofColor _color;
    FrameTimer _timer_fadein;
    ofVec2f _vel;
    
    ofVec2f _pos_shadow;
    ofColor _color_shadow;

    
    float _seg;
public:
    PSunset(ofVec2f p,float w,float t){
        _color=ofColor(ofRandom(200,255),ofRandom(80,150),ofRandom(60));
        _color_shadow=ofColor(255-_color.r,255-_color.g,_color.b);
        
        _pos=p;
        init(w);
        
        _layer=0;
        _timer_fadein=FrameTimer(t);
        _timer_fadein.restart();
    }
    void init(float w){
        
        _size=ofVec2f(w,w);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=64;
        float eth=TWO_PI/_seg;
        
        float tx=ofGetHeight()/2;
        float ty=ofGetHeight()/2;
        
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            _mesh.addVertex(ofVec2f(0,0));
            _mesh.addVertex(ofVec2f(w*sin(th),w*cos(th)));
            _mesh.addVertex(ofVec2f(w*sin(th+eth),w*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
        
        _pos_shadow=ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
        
        
       
    }
    
    void draw(){
        
        ofPushStyle();
        ofFill();
        
        ofPushMatrix();
        ofTranslate(_pos);
        //ofRotate(-_vel.angle(ofVec2f(1,0)));
        
       
        ofSetColor(_color,128*_timer_fadein.valEaseOut());
        
        
        ofPushMatrix();
        ofTranslate(_pos_shadow);
        _mesh.draw();
        ofPopMatrix();
        
        ofSetColor(_color,255*_timer_fadein.valEaseOut());
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
        _timer_fadein.update(dt_);
      
        
        if(ofRandom(10)>1) return;
        
        _pos_shadow=ofVec2f(20*ofNoise(-20,20),ofRandom(-20,20));
        
//        if(ofRandom(3)>1) return;
        
        float eth=TWO_PI/_seg;
        float w=_size.x;
        
        int m=0;
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            float tx=ofGetHeight()/2+ofGetFrameNum()%20-10;
            float ty=ofGetHeight()/2+ofGetFrameNum()%20-10;
            
            _mesh.setTexCoord(m++,ofVec2f(tx,ty));
            _mesh.setTexCoord(m++,ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.setTexCoord(m++,ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
        
      
    }
};

#endif /* PSun_h */
