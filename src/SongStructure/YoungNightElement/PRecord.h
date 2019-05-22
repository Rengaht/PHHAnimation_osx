//
//  PRecord.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/20.
//

#ifndef PRecord_h
#define PRecord_h
#include "PElement.h"

#define MIN_RECORD_INTERVAL 500
#define MAX_RECORD_INTERVAL 20000

class PRecord:public PElement{
    ofMesh _mesh;
    ofMesh _mesh_pinhead;
    
    ofColor _color,_color_center;
    FrameTimer _timer_rot,_timer_pin;
    float _vel;
    float _ang_rot;
    float _ang_pin;
    
    ofVec2f _pos_shadow;
    
    float _seg;
    float _rad_texcoord;
    
    float _rad_center;
    
public:
    
    int _stage;
    PRecord(ofVec2f p,float w){
        _color=ofColor(ofRandom(200,255),ofRandom(80,150),ofRandom(60),120);
        _color_center=ofColor(ofRandom(120),0,ofRandom(180,255));
        
        _rad_center=ofRandom(.3,.6);
        
        reset();
        _timer_pin=FrameTimer(ofRandom(100,500));
        _timer_rot.restart();
        _timer_pin.restart();
        
        _vel=1;
        
        _pos=p;
        init(w);
        
        _layer=0;
    }
    void init(float w){
        
        _size=ofVec2f(w,w);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=64;
        float eth=TWO_PI/_seg;
        
//        int mm=floor(ofRandom(2,5));
        
//        for(int x=0;x<mm;++x){
            float mr=w;
            _rad_texcoord=ofRandom(.5,1.2)*mr;
        
            float tx=ofGetHeight()/2+ofRandom(-20,20);
            float ty=ofGetHeight()/2+ofRandom(-20,20);
            
            
            for(float i=0;i<=_seg;++i){
                float th=eth*i;
                _mesh.addVertex(ofVec2f(0,0));
                _mesh.addVertex(ofVec2f(mr*sin(th),mr*cos(th)));
                _mesh.addVertex(ofVec2f(mr*sin(th+eth),mr*cos(th+eth)));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx+_rad_texcoord*sin(th),ty+_rad_texcoord*cos(th)));
                _mesh.addTexCoord(ofVec2f(tx+_rad_texcoord*sin(th+eth),ty+_rad_texcoord*cos(th+eth)));
            }
//        }
        
        
        _pos_shadow=ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
        
        
        ofVec2f ph_(0,0);
        ofVec2f pin_(0,w*1.2);
//        pin_.rotate(-5);
        
        ofVec2f norm(pin_.y,-pin_.x);
        norm.normalize();
        norm*=w/20;
     
        _mesh_pinhead.addVertex(ofVec2f(ph_.x,ph_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x+norm.x,ph_.y+pin_.y+norm.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(0,w/10));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        
        ph_=ph_+pin_;
        pin_.normalize();
        pin_*=w*.6;
        pin_.rotate(-30);
        norm.rotate(-30);
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x,ph_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x+norm.x,ph_.y+pin_.y+norm.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(0,w/10));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        
        ph_=ph_+pin_*.9-norm*.5;
        pin_*=.33;
        norm*=2;
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x,ph_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x+norm.x,ph_.y+pin_.y+norm.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(0,w/10));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
       
        
    }
    
    void draw(){
        
        ofPushStyle();
        ofFill();
        
        //        float t=_timer_move.valEaseInOut();
        ofPushMatrix();
        ofTranslate(_pos);
        ofPushMatrix();
        ofRotate(_timer_rot.val()*_ang_rot*_vel);
        
        ofSetColor(_color,128);
        ofPushMatrix();
        ofTranslate(_pos_shadow);
            _mesh.draw();
        ofPopMatrix();
        
        ofSetColor(_color,255);
            _mesh.draw();
        
        
        ofPushMatrix();
        ofScale(_rad_center,_rad_center);
        ofSetColor(_color_center);
            _mesh.draw();
        ofPopMatrix();

        ofPushMatrix();
        ofScale(.1,.1);
        ofSetColor(0);
            _mesh.draw();
        ofPopMatrix();
        
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(-_size.x*1.1,-_size.y*1.2);
        ofRotate(-_timer_pin.valEaseIn()*_ang_pin);
        
        ofSetColor(255,128);
        ofPushMatrix();
        ofTranslate(_pos_shadow*.33);
            _mesh_pinhead.draw();
        ofPopMatrix();
        ofSetColor(255);
        _mesh_pinhead.draw();
        
        
        ofPopMatrix();
        
        ofPopMatrix();
        
        ofPopStyle();
        
    }
    void end(){
        
    }
    void reset(){
        _vel=ofRandom(2)<1?1:-1;
        _ang_rot=ofRandom(.5,5)*360;
        _ang_pin=ofRandom(0,10);
        _timer_rot=FrameTimer(ofRandom(MIN_RECORD_INTERVAL,MAX_RECORD_INTERVAL),100);
        
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
        _timer_rot.update(dt_);
        _timer_pin.update(dt_);
        if(_timer_rot.val()==1){
            reset();
            _timer_pin.restart();
            _timer_rot.restart();
        }
        
        if(ofRandom(10)>1) return;
        
        _pos_shadow=ofVec2f(ofRandom(-1,1),ofRandom(-1,1))*_size.x*.05;
        
        //        if(ofRandom(3)>1) return;
        
        float eth=TWO_PI/_seg;
        float w=_size.x;
        
        int m=0;
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            float tx=ofGetHeight()/2+ofGetFrameNum()%10-5+ofRandom(-1,1);
            float ty=ofGetHeight()/2+ofGetFrameNum()%10-5+ofRandom(-1,1);
            
            _mesh.setTexCoord(m++,ofVec2f(tx,ty));
            _mesh.setTexCoord(m++,ofVec2f(tx+_rad_texcoord*sin(th),ty+_rad_texcoord*cos(th)));
            _mesh.setTexCoord(m++,ofVec2f(tx+_rad_texcoord*sin(th+eth),ty+_rad_texcoord*cos(th+eth)));
        }
        
        
    }
};

#endif /* PRecord_h */
