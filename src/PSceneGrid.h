//
//  PSceneGrid.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/19.
//

#ifndef PSceneGrid_h
#define PSceneGrid_h

#include "PGrid.h"
#define MIN_LINE_INTERVAL 50
#define MAX_LINE_INTERVAL 200

class PSceneGrid:public PScene{
    
    ofFbo _tex_line;
    float _grid_width;
    int _mgridx,_mgridy;
    int _idx_gridx,_idx_gridy;
    
    FrameTimer _timer_add;
public:
    float _speed;
    ofCamera _camera;
    
    PSceneGrid():PScene(){
        
        
        reset();
        initTexture();
        _mstage=1;
        
        _timer_add=FrameTimer(ofRandom(MIN_LINE_INTERVAL,MAX_LINE_INTERVAL));
        _timer_add.restart();
    }
    void update(float dt){
        
        PScene::update(dt);
        
        _timer_add.update(dt);
        if(_timer_add.val()==1){
            addGrid();
        }
        
//        _speed*=1.01;
        if(_speed>3) _speed=3;
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
        
//        int t=floor(ofRandom(1,3));
        _mgridx=ofRandom(6,15);
        _grid_width=(float)ofGetWidth()/_mgridx;
        _mgridy=floor((float)ofGetHeight()/_grid_width);
        
        _idx_gridx=0;
        _idx_gridy=0;
        _speed=0;
        
    }
    void setEffect(int i){
        switch(i){
            case 'a':
            case 'A':
                reset();
                _timer_add.restart();
                break;
            case '>':
            case '.':
                addGrid();
                break;
        }
    }
    
    void addGrid(){
        if(_idx_gridx>=_mgridx && _idx_gridy>=_mgridy-1){
            _timer_add.restart();
            reset();
            return;
        }
        
        float t=ofRandom(MIN_LINE_INTERVAL,MAX_LINE_INTERVAL);
        _timer_add=FrameTimer(t);
        _timer_add.restart();
        
        float w=ofRandom(.01,.05)*ofGetWidth();
        _element.push_back(new PGrid((_idx_gridx+ofRandom(-1,1)*_speed)*_grid_width,(_idx_gridy+ofRandom(-1,1)*_speed)*_grid_width,_grid_width,t));
        
        if(_idx_gridx<_mgridx) _idx_gridx++;
        else{
            _idx_gridx=0;
            _idx_gridy++;
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
        _tex_line.end();
    }
    
};
#endif /* PSceneGrid_h */
