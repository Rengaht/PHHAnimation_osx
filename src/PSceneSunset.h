//
//  SceneSunset.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef SceneSunset_h
#define SceneSunset_h
#include "PSunset.h"
#include "PWave.h"
#define MIN_SUN_INTERVAL 5000
#define MAX_SUN_INTERVAL 10000

class PSceneSunset:public PScene{
    
    ofFbo _tex_line;
    float _pos_line;
    FrameTimer _timer_add;
    
    PSea _psea;
    ofColor _bgd,_dest_bgd;
    FrameTimer _timer_color;
    
public:
    
    PSceneSunset():PScene(){
        reset();
        initTexture();
        _mstage=2;
        
    }
    void update(float dt){
        
        for(auto it=_element.begin();it!=_element.end();){
            (**it).update(0,dt);
            if((**it)._dead){
                if((**it)._layer==1) addWave();
                _element.erase(it++);
//                addSun();
            }else it++;
        }
        _psea.update(0,dt);
        
        _timer_add.update(dt);
        if(_timer_add.val()==1){
            addSun();
        }
        
        _timer_color.update(dt);
        if(_timer_color.val()==1){
            
             _bgd=_dest_bgd;
            _dest_bgd=ofColor(ofRandom(20,80),0,ofRandom(50,120));
            
            _timer_color=FrameTimer(ofRandom(1000,5000));
            _timer_color.restart();
        }
        
       
    }
    void draw(){
        
        
        ofColor b_=_bgd.lerp(_dest_bgd,_timer_color.valEaseOut());
        ofClear(0);
//                _tex_line.draw(0,0);
        
        _tex_line.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==0 && ((PSunset*)e)->_stage==0) (*e).draw();
      
        _psea.draw();
      
        for(auto& e: _element){
            if(e->_layer==0 && ((PSunset*)e)->_stage==1) (*e).draw();
            if(_idx_stage>0 && e->_layer==1) (*e).draw();
        }
        _tex_line.getTexture().unbind();
        
        
        
    }
    void reset(){
        PScene::reset();
        
        _element.clear();
        
        _psea=PSea();
        addSun();
        
        
        _timer_add=FrameTimer(ofRandom(MIN_SUN_INTERVAL,MAX_SUN_INTERVAL)/2);
        _timer_add.restart();
        
        
        _bgd=ofColor(ofRandom(20,80),0,ofRandom(50,80));
        _dest_bgd=ofColor(ofRandom(20,80),0,ofRandom(50,80));
        _timer_color=FrameTimer(ofRandom(MIN_SUN_INTERVAL,MAX_SUN_INTERVAL));
        _timer_color.restart();
        
        _pos_line=0;
        
        for(int i=0;i<5;++i) addWave();
        
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                reset();
                _timer_add.restart();
                break;
            case 's':
            case 'S':
                addSun();
                break;
            case '.':
            case '>':
                goNextStage();
                break;
            case ',':
            case '<':
                goPrevStage();
                break;
        }
    }
    
    void initTexture(){
        _tex_line.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        float c=120;
        float m=ofGetHeight()/c;
        _tex_line.begin();
        ofClear(0,0);
        
        //        ofSetLineWidth(WSTROKE);
        
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float s=ofMap(j,0,c,100,10);
                float dx=ofNoise(i/s,j/s)+ofMap(j,0,c,0.5,1.0);
                float dy=ofRandom(.5)+.5;
                ofSetColor(ofMap(j,0,c,200,255));
                ofDrawEllipse(i*m+dx*m,j*m-dy*m,dx*m,dx*m);
            }
        _tex_line.end();
    }
    void addWave(){
//        int m=floor(ofRandom(1,3));
//        for(int i=0;i<m;++i){
        if(ofRandom(2)<1)
            _element.push_back(new PWave(ofVec2f(ofRandom(-.1,1.1)*ofGetWidth(),ofGetHeight()*ofRandom(.1,.3)),ofRandom(2,8),ofRandom(30,100),100));
        else{
            auto p=new PWave(ofVec2f(ofRandom(-.1,1.1)*ofGetWidth(),ofGetHeight()*ofRandom(.5,1)),ofRandom(2,8),ofRandom(30,100),100);
            _element.push_back(p);
        }
//        }
    }
    void addSun(){
        float t=ofRandom(MIN_SUN_INTERVAL,MAX_SUN_INTERVAL);
        _element.push_front(new PSunset(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),ofGetHeight()*ofRandom(.2,.5),t));
        _timer_add=FrameTimer(ofRandom(.7,1)*t);
        _timer_add.restart();
    }
    
};

#endif /* SceneSunset_h */
