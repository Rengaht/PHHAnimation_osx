//
//  PSun.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PSun_h
#define PSun_h

#include "PElement.h"
#include "PWave.h"

class PSea:public PElement{
    ofMesh _mesh;
    ofColor _color;
    ofVec2f _pos_shadow;
    
    ofColor _dest_color;
    FrameTimer _timer_color;
   
    
public:
    PSea(){
        _color=ofColor(ofRandom(20),ofRandom(20),ofRandom(120,255));
        _dest_color=ofColor(ofRandom(20),ofRandom(20),ofRandom(120,255));
        
        
        _timer_color=FrameTimer(ofRandom(1000,5000));
        _timer_color.restart();
        
        _layer=0;
        init();
    }
    void init(){
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        float y=.5*ofGetHeight();
        float sw=ofGetWidth();
        float sh=ofGetHeight()-y;
        
        _pos=ofVec2f(0,y);
        _size=ofVec2f(sw,sh);
        
        _mesh.addVertex(ofVec2f(-sw*.1,y));
        _mesh.addVertex(ofVec2f(sw*1.1,y));
        _mesh.addVertex(ofVec2f(sw*1.1,y+sh));
        
        _mesh.addVertex(ofVec2f(sw*1.1,y+sh));
        _mesh.addVertex(ofVec2f(-sw*.1,y+sh));
        _mesh.addVertex(ofVec2f(-sw*.1,y));
        
        float ty=ofRandom(0,y);
        _mesh.addTexCoord(ofVec2f(0,ty));
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty));
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty+sh));
        
        _mesh.addTexCoord(ofVec2f(ofGetHeight(),ty+sh));
        _mesh.addTexCoord(ofVec2f(0,ty+sh));
        _mesh.addTexCoord(ofVec2f(0,ty));
        
        int m=floor(ofRandom(3,6));
       
    }
    void draw(){
        ofPushStyle();
        ofPushMatrix();
        
        ofPushMatrix();
        ofTranslate(_pos_shadow);
        
        ofColor c_=_color.lerp(_dest_color,_timer_color.valEaseOut());
        
        ofSetColor(c_,128);
        _mesh.draw();
        ofPopMatrix();
        
        ofSetColor(c_,255);
        _mesh.draw();
        
        
        ofPopMatrix();
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
        
        _timer_color.update(dt_);
        //_timer_fadein.update(dt_);
        if(ofRandom(10)<1) _pos_shadow=ofVec2f(20*ofNoise(-20,20),ofRandom(-20,20));
        
        if(_timer_color.val()==1){
            
            _color=_dest_color;
            _dest_color=ofColor(ofRandom(20),ofRandom(20),ofRandom(120,255));
            
            _timer_color=FrameTimer(ofRandom(1000,5000));
            _timer_color.restart();
        }
        
        if(ofRandom(10)>1) return;
        
        float ty=abs(sin(ofGetFrameNum()/200.0))*_pos.y;
        float sh=_size.y;
        float tx=ofGetHeight()*ofRandom(-.1,.1);
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
    ofMesh _mesh_half;
    
    ofColor _color;
    FrameTimer _timer_fadein;
    ofVec2f _vel;
    
    ofVec2f _pos_shadow;
    ofColor _color_shadow;

    
    FrameTimer _timer_drop;
    FrameTimer _timer_move;
    
    
    list<PWave> _wave;
    float _seg;
public:
    
    int _stage;
    PSunset(ofVec2f p,float w,float t){
        _color=ofColor(ofRandom(200,255),ofRandom(80,150),ofRandom(60));
        _color_shadow=ofColor(255-_color.r,255-_color.g,_color.b);
        
        _timer_drop=FrameTimer(t*.25);
        _timer_drop.restart();
        
        _timer_move=FrameTimer(t*.75);
//        _timer_move.restart();
        
        _layer=0;
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
        
        float tx=ofGetHeight()/2+ofRandom(-20,20);
        float ty=ofGetHeight()/2+ofRandom(-20,20);
        
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            _mesh.addVertex(ofVec2f(0,0));
            _mesh.addVertex(ofVec2f(w*sin(th),w*cos(th)));
            _mesh.addVertex(ofVec2f(w*sin(th+eth),w*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
        
        for(float i=0;i<=_seg/2;++i){
            float th=HALF_PI+eth*i;
            _mesh_half.addVertex(ofVec2f(0,0));
            _mesh_half.addVertex(ofVec2f(w*sin(th),w*cos(th)));
            _mesh_half.addVertex(ofVec2f(w*sin(th+eth),w*cos(th+eth)));
            
            _mesh_half.addTexCoord(ofVec2f(tx,ty));
            _mesh_half.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh_half.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
        
        _pos_shadow=ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
        
        _stage=0;
        int m=floor(ofRandom(3,8));
        
        float t=ofRandom(.3,.6)*2*w;
        float ww=ofRandom(4,10);
        float tty=ofRandom(1,1.5)*ww;
        float ttx=0;
        for(int i=0;i<m;++i){
            
            PWave p(ofVec2f(ttx,tty),ww*ofRandom(.8,1.2),t,100*i+50,_timer_drop.getDue()*.9+ofRandom(100,200));
            p._color=ofColor(_color,ofRandom(120,220));
            p._auto_dead=false;
            _wave.push_back(p);
                         
            ttx+=ofRandom(-.1,.1)*w;
            tty+=ww*ofRandom(1,2.2);
            t*=ofRandom(.6,.8);
        }
    }
    
    void draw(){
        
        ofPushStyle();
        ofFill();
        
//        float t=_timer_move.valEaseInOut();
        ofPushMatrix();
        if(_stage==0) ofTranslate(_pos.x,ofMap(_timer_drop.valEaseIn(),0,1,-_size.y/2,ofGetHeight()/2));
        else ofTranslate(_pos.x,ofGetHeight()/2+(ofGetHeight()/2+_size.y*2)*_timer_move.valEaseIn());
        
        float scl_=ofMap(_timer_move.valEaseIn(),0,1,.2,1.5);
        ofScale(scl_,scl_);
        
       
        ofSetColor(_color,128*_timer_fadein.valEaseOut());
        
        
        ofPushMatrix();
        ofTranslate(_pos_shadow);
        
        if(_stage==0) _mesh.draw();
        else _mesh_half.draw();
        
        ofPopMatrix();
        
        ofSetColor(_color,255*_timer_fadein.valEaseOut());
        
        if(_stage==0) _mesh.draw();
        else{
            _mesh_half.draw();
        }
        for(auto& t:_wave) t.draw();
        
       
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
        
        _timer_drop.update(dt_);
        if(_timer_drop.val()==1 && _stage==0){
            _timer_move.restart();
            _stage=1;
        }
        _timer_move.update(dt_);
        
        for(auto& w:_wave){
            w.update(0,dt_);
            if(ofRandom(3)<1){
//                w._pos.x+=ofRandom(-.25,.25)*w._size.x;
//                w._pos.y+=ofRandom(-.5,.5)*w._size.y;
            }
        }
        
        
        if(_timer_move.val()==1) _dead=true;
        
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
