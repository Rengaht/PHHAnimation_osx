//
//  PSceneSmoke.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PSceneSmoke_h
#define PSceneSmoke_h

#define MIN_SMOKE_INTERVAL 50
#include "PSmoke.h"
#include "PDrink.h"

class PSceneSmoke:public PScene{
    
    ofFbo _tex_line;
    FrameTimer _timer_add;
    ofVec2f _wind;
    ofVec2f _pos_smoke;
    
    float _ang_start;
    float _ang_end;
    
public:
    static float _speed;
    ofCamera _camera;
    
    PSceneSmoke():PScene(){
        
        reset();
        initTexture();
        _mstage=1;
        
        _wind=ofVec2f(0,-SMOKE_VEL);
        
        _timer_add=FrameTimer(100);
        _timer_add.restart();
        
        _pos_smoke=ofVec2f(0,ofGetHeight());
        _ang_start=0;
        _ang_end=HALF_PI;
        
    }
    void update(float dt){
        
        PScene::update(dt);
        
        _wind.x=cos(_timer_add.val()*(_ang_end-_ang_start)+_ang_start)*SMOKE_VEL*2;
        
        for(auto it=_element.begin();it!=_element.end();){
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        for(auto& p:_element){
            if(p->_layer==0) ((PSmoke*)p)->update(_wind,dt);
        }
        _timer_add.update(dt);
        if(_timer_add.val()==1){
            addSmoke();
            _timer_add.restart();
        }
        
        if(ofRandom(5)<1){
            _pos_smoke.x=ofRandom(.3,.7)*ofGetWidth();
            _ang_start=ofRandom(HALF_PI);
            _ang_end=ofRandom(_ang_start,PI);
            
            _timer_add.restart();
        }
    }
    void draw(){
//        ofClear(0);
        //        _tex_line.draw(0,0);
        
        _tex_line.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        _tex_line.getTexture().unbind();
        
        for(auto& e: _element)
            if(e->_layer==1) (*e).draw();
    }
    void reset(){
        PScene::reset();
        
        _pos_smoke.x=ofRandom(.3,.7)*ofGetWidth();
        _ang_start=ofRandom(HALF_PI);
        _ang_end=ofRandom(_ang_start,PI);
        
        _element.clear();
        
//        _element.push_back(new PDrink(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),ofRandom(50,200)));
//        _pos_line=0;
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                reset();
                break;
            case 'o':
            case 'O':
                _pos_smoke.x=ofRandom(.3,.7)*ofGetWidth();
                _ang_start=ofRandom(HALF_PI);
                _ang_end=ofRandom(_ang_start,PI);
                
                _timer_add.restart();
                break;
            case 'p':
            case 'P':
                addSmoke();
                break;
        }
    }
    
    void addSmoke(){
        
        int m=floor(ofRandom(10,20));
        
        for(int i=0;i<m;++i){
            float w=ofRandom(.01,.05)*ofGetWidth();
            _element.push_back(new PSmoke(_pos_smoke+ofVec2f(ofRandom(-1,1),ofRandom(-1,1))*w,_wind+ofVec2f(ofRandom(-3,3)*SMOKE_VEL,0),w,MIN_SMOKE_INTERVAL));
        }
    }
    void initTexture(){
        _tex_line.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        float c=250;
        float m=ofGetHeight()/c;
        _tex_line.begin();
        ofClear(0,0);
        
        //        ofSetLineWidth(WSTROKE);
        
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float dx=ofNoise(i/10.0,j/10.0)+.5;
                float dy=ofRandom(.5)+.5;
                ofSetColor(255);
                ofDrawCircle(i*m+dx*m,j*m-dy*m,dx*m);
            }
        _tex_line.end();
    }
    
};


#endif /* PSceneSmoke_h */
