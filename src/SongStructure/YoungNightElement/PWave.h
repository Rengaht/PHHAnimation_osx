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
    
    FrameTimer _timer_fadein,_timer_fadeout;
public:
     ofColor _color;
    bool _auto_dead;
    
     PWave(ofVec2f p,float w,float h,float t,float delay_=0){
         _color=ofColor(255,ofRandom(50,120));
         _layer=1;
         _pos=p;
         _timer_fadein=FrameTimer(t,delay_);
         _timer_fadein.restart();
         _timer_fadeout=FrameTimer(t,delay_);
         _auto_dead=true;
         init(w,h);
     }
    void init(float w,float h){
        
        _size=ofVec2f(h,w*2);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=12;
        float eth=PI/_seg;
        
        float tx=ofGetHeight()/2;
        float ty=ofGetHeight()/2;
        
        int m=floor(ofRandom(1,5));
        
        for(int x=0;x<m;++x){
            float cx=ofRandom(-.5,.5)*_size.x;
            float cy=ofRandom(-.5,.5)*_size.y;
            
            float xx=-_size.x/2;
            float yy=_size.y/2;
            
            for(float i=0;i<=_seg;++i){
                float th=-eth*i;
                _mesh.addVertex(ofVec2f(cx+xx,cy+0));
                _mesh.addVertex(ofVec2f(cx+xx+w*sin(th),cy+w*cos(th)));
                _mesh.addVertex(ofVec2f(cx+xx+w*sin(th+eth),cy+w*cos(th+eth)));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
                _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
            }
            _mesh.addVertex(ofVec2f(cx+xx,cy-yy));
            _mesh.addVertex(ofVec2f(cx-xx,cy+yy));
            _mesh.addVertex(ofVec2f(cx+xx,cy+yy));
            
            _mesh.addTexCoord(ofVec2f(tx+xx,ty-yy));
            _mesh.addTexCoord(ofVec2f(tx-xx,ty+yy));
            _mesh.addTexCoord(ofVec2f(tx+xx,ty+yy));
            
            
            _mesh.addVertex(ofVec2f(cx+xx,cy-_size.y/2));
            _mesh.addVertex(ofVec2f(cx-xx,cy-_size.y/2));
            _mesh.addVertex(ofVec2f(cx-xx,cy+_size.y/2));
            
            _mesh.addTexCoord(ofVec2f(tx+xx,ty-yy));
            _mesh.addTexCoord(ofVec2f(tx-xx,ty-yy));
            _mesh.addTexCoord(ofVec2f(tx-xx,ty+yy));
            
    //        _mesh.addTexCoord(ofVec2f(tx+w,ty));
            
            xx=_size.x/2;
            for(float i=0;i<=_seg;++i){
                float th=eth*i;
                
                _mesh.addVertex(ofVec2f(cx+xx,cy+0));
                _mesh.addVertex(ofVec2f(cx+xx+w*sin(th),cy+w*cos(th)));
                _mesh.addVertex(ofVec2f(cx+xx+w*sin(th+eth),cy+w*cos(th+eth)));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
                _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
            }
            
        }
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(_pos);
        ofSetColor(_color,_color.a*_timer_fadein.valEaseOut()*(1.0-_timer_fadeout.valEaseOut()));
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
        _timer_fadeout.update(dt_);
        
        if(_auto_dead && _timer_fadeout.val()==0){
            if(ofRandom(200)<1){
                _timer_fadeout.restart();
            }
        }
        if(_timer_fadeout.val()==1) _dead=true;
        
        if(ofRandom(10)>1) return;
        _pos.x+=ofRandom(-.25,.25)*_size.x;
//        _pos.y+=ofRandom(-.25,.25)*_size.y;
        
    }
};


class PHWave:public PElement{
    ofMesh _mesh;
    ofColor _color;
    ofVec2f _pos_shadow;
    
    FrameTimer _timer_drop,_timer_move;
    
public:
    int _stage;
    PHWave(float t){
        _color=ofColor(ofRandom(80,180),ofRandom(20),ofRandom(120,255),ofRandom(180,255));
        
        _timer_drop=FrameTimer(t*.3);
        _timer_drop.restart();
        _timer_move=FrameTimer(t*.7);
        _timer_move.restart();
        
        _layer=2;
        init();
    }
    void init(){
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float y=0;
        float sw=ofGetWidth()*ofRandom(.2,.7);
        float sh=ofRandom(.05,.1)*ofGetHeight();
        
        _pos=ofVec2f(ofRandom(-.2,.8)*sw,y);
        _size=ofVec2f(sw,sh);
        
        _mesh.addVertex(ofVec2f(0,y));
        _mesh.addVertex(ofVec2f(sw,y));
        _mesh.addVertex(ofVec2f(sw,y+sh));
        
        _mesh.addVertex(ofVec2f(sw,y+sh));
        _mesh.addVertex(ofVec2f(0,y+sh));
        _mesh.addVertex(ofVec2f(0,y));
        
        float ty=ofRandom(0,y);
        float tx=ofRandom(0,sw);
        float sc=(float)ofGetHeight()/sw;
        _mesh.addTexCoord(ofVec2f(tx,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh*sc));
        
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh*sc));
        _mesh.addTexCoord(ofVec2f(tx+0,ty+sh*sc));
        _mesh.addTexCoord(ofVec2f(tx+0,ty));
        
        int m=floor(ofRandom(3,6));
        
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        //ofTranslate(_pos.x,_pos.y+ofGetHeight()*_timer_move.valEaseInOut());
        if(_stage==0) ofTranslate(_pos.x,ofMap(_timer_drop.val(),0,1,-_size.y/2,ofGetHeight()/2));
        else ofTranslate(_pos.x,ofGetHeight()/2+(ofGetHeight()/2+_size.y*2)*_timer_move.valEaseOut());
        
//        ofPushMatrix();
//        ofTranslate(_pos_shadow);
        
        
//        ofSetColor(_color,128);
//        _mesh.draw();
//        ofPopMatrix();
        
        ofSetColor(_color);
        _mesh.draw();
        
        
        ofPopMatrix();
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
        
        _pos.y+=vel_;
        //if(_pos.y>ofGetHeight()+_size.y) _dead=true;
        _timer_drop.update(dt_);
        if(_timer_drop.val()==1 && _stage==0){
            _timer_move.restart();
            _stage=1;
        }
        _timer_move.update(dt_);
        if(_timer_move.val()==1) _dead=true;
        
        
        //_timer_fadein.update(dt_);
        if(ofRandom(10)<1) _pos_shadow=ofVec2f(20*ofNoise(-20,20),ofRandom(-20,20));
        
        
        if(ofRandom(10)>1) return;
        
        float ty=abs(sin(ofGetFrameNum()/200.0))*_pos.y;
        float sh=_size.y;
        float sw=_size.x;
        float tx=ofRandom(0,ofGetHeight()-sw);
        float sc=(float)ofGetHeight()/sw;
        
        _mesh.clearTexCoords();
        _mesh.addTexCoord(ofVec2f(tx,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty));
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh*sc));
        
        _mesh.addTexCoord(ofVec2f(tx+sw,ty+sh*sc));
        _mesh.addTexCoord(ofVec2f(tx,ty+sh*sc));
        _mesh.addTexCoord(ofVec2f(tx,ty));
    }
};

#endif /* PWave_h */
