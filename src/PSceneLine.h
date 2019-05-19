//
//  SceneLine.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef SceneLine_h
#define SceneLine_h

#include "PScene.h"
#include "PPLine.h"

#define MIN_LINE_INTERVAL 50
#define MAX_LINE_INTERVAL 200

class PSceneLine:public PScene{
    
    ofFbo _tex_line;
    float _pos_line;
//    list<PPLine> _line;
    FrameTimer _timer_add;
public:
    static float _speed;
    ofCamera _camera;
    
    PSceneLine():PScene(){
        
        
        reset();
        initTexture();
        _mstage=1;
        
        _timer_add=FrameTimer(ofRandom(MIN_LINE_INTERVAL,MAX_LINE_INTERVAL));
    }
    void update(float dt){
        
        PScene::update(dt);
        
        _timer_add.update(dt);
        if(_timer_add.val()==1){
            addLine();
        }
        
       
    }
    void draw(){
        ofClear(0);
//        _tex_line.draw(0,0);
        
        _tex_line.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        _tex_line.getTexture().unbind();
        
    }
    void reset(){
        PScene::reset();
        
        _element.clear();
        _pos_line=0;
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                reset();
                _timer_add.restart();
                break;
            case '.':
            case '>':
                addLine();
                break;
        }
    }
    
    void addLine(){
        if(_pos_line>=ofGetWidth()){
            _timer_add.restart();
            reset();
            return;
        }
        
        float t=ofRandom(MIN_LINE_INTERVAL,MAX_LINE_INTERVAL);
        _timer_add=FrameTimer(t);
        _timer_add.restart();
        
        float w=ofRandom(.01,.05)*ofGetWidth();
        _element.push_back(new PPLine(_pos_line,w,t));
        _pos_line+=w;
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
                float dx=ofNoise(i/10.0,j/10.0)+.5;
                float dy=ofRandom(.5)+.5;
                ofSetColor(255);
                ofDrawCircle(i*m+dx*m,j*m-dy*m,dx*m);
            }
        _tex_line.end();
    }
    
};
#endif /* SceneLine_h */
