//
//  SceneLine.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef SceneLine_h
#define SceneLine_h



#include "PScene.h"
#include "PRecord.h"



class PSceneRecord:public PScene{
    
    ofFbo _tex_line;
    list<PRecord*> _record;
    
public:
    static float _speed;
    
    PSceneRecord():PScene(){
        
        
        reset();
        initTexture();
        _mstage=2;
        
    }
    void update(float dt){
        
        PScene::update(dt);
         for(auto&r :_record) r->update(0,dt);
       
    }
    void draw(){
        ofClear(0);
//        _tex_line.draw(0,0);
        
        _tex_line.getTexture().bind();
            for(auto&r :_record) r->draw();
        _tex_line.getTexture().unbind();
        
    }
    void reset(){
        PScene::reset();
        
        addRecord();
    }
    void addRecord(){
        _record.clear();
        if(_idx_stage==0) _record.push_back(new PRecord(ofVec2f(ofGetWidth()/2,ofGetHeight()/2),ofGetHeight()*ofRandom(.2,.45)));
        else{
            for(int i=0;i<4;++i) _record.push_back(new PRecord(ofVec2f(ofGetWidth()/4*(i+.5),ofGetHeight()/2),ofGetWidth()/4*ofRandom(.2,.45)));
        }
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                reset();
                break;
            case '.':
            case '>':
                goNextStage();
                addRecord();
                break;
            case ',':
            case '<':
                goPrevStage();
                addRecord();
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
                float dx=ofNoise(i/10.0,j/10.0)+.5;
                float dy=ofRandom(.5)+.5;
                ofSetColor(255);
                ofDrawCircle(i*m+dx*m,j*m-dy*m,dx*m);
            }
        c=120;
        m=ofGetHeight()/c;
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float dx=ofClamp(ofNoise(i/10.0,j/10.0),.5,1);
                float dy=ofRandom(.5)+.5;
                ofSetColor(200);
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i)*m-dy*m,(j+1)*m+dx*m);
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i+1)*m-dx*m,(j)*m+dx*m);
            }
        _tex_line.end();
    }
    
};
#endif /* SceneLine_h */
