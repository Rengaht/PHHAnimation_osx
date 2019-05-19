//
//  SceneSunset.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef SceneSunset_h
#define SceneSunset_h
#include "PSunset.h"

class PSceneSunset:public PScene{
    
    ofFbo _tex_line;
    float _pos_line;
    FrameTimer _timer_add;
    
    
public:
    
    PSceneSunset():PScene(){
        reset();
        initTexture();
        _mstage=1;
        
        _timer_add=FrameTimer(ofRandom(MIN_LINE_INTERVAL,MAX_LINE_INTERVAL));
        
        
    }
    void update(float dt){
        
        PScene::update(dt);
//        for(auto)
        
        _timer_add.update(dt);
        if(_timer_add.val()==1){
            //addLine();
        }
        
        
    }
    void draw(){
        ofClear(0);
//                _tex_line.draw(0,0);
        
        _tex_line.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        _tex_line.getTexture().unbind();
        
    }
    void reset(){
        PScene::reset();
        
        _element.clear();
        _element.push_back(new PSunset(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),ofGetHeight()*ofRandom(.2,.5),100));
        _element.push_back(new PSea());
        
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
//                addLine();
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
    
};

#endif /* SceneSunset_h */
