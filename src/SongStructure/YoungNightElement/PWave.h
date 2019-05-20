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
    FrameTimer _timer_fadein,_timer_fadeout;
public:
     PWave(ofVec2f p,float w,float t){
         _color=ofColor(0,0,ofRandom(20,120));
         _layer=1;
         _pos=p;
         _timer_fadein=FrameTimer(t);
         _timer_fadein.restart();
         _timer_fadeout=FrameTimer(t);
         
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
        ofSetColor(_color,255.0*_timer_fadein.valEaseOut()*(1.0-_timer_fadeout.valEaseOut()));
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
        
        if(_timer_fadeout.val()==0){
            if(ofRandom(200)<1){
                _timer_fadeout.restart();
            }
        }
        if(_timer_fadeout.val()==1) _dead=true;
        
        if(ofRandom(10)>1) return;
        _pos.x+=ofRandom(-5,5);
        _pos.y+=ofRandom(-5,5);
        
    }
};

#endif /* PWave_h */
