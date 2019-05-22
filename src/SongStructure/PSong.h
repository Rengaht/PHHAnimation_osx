//
//  PSong.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PSong_h
#define PSong_h

#include "PScene.h"

class PSong{
public:
    int _idx_scene;
    int _mscene;
    string _name_song;
    
    vector<PScene*> _scene;
    
    PSong(){
        _idx_scene=_mscene=0;
    }
    void goNextScene(){
        _idx_scene=min(_idx_scene+1,_mscene-1);
    }
    virtual void update(float dt_){
        (*_scene[_idx_scene]).update(dt_);
    }
    virtual void draw(){
         (*_scene[_idx_scene]).draw();
        
#ifdef DRAW_DEBUG
        ofPushStyle();
        ofSetColor(0);
        ofDrawBitmapString(_name_song,50,50);
        ofDrawBitmapString("scene= "+ofToString(_idx_scene)+"/"+ofToString(_mscene),50,10);
        ofPopStyle();
#endif
    }
    virtual void reset(){
        _idx_scene=0;
        for(int i=0;i<_mscene;++i) (*_scene[i]).reset();
    }
    virtual void setScene(int index_){
        if(index_<0 || index_>=_mscene) return;
        _idx_scene=index_;
    }
    virtual void setEffect(int key_){
        switch(key_){
            case 'q':
            case 'Q':
                setScene(0);break;
            case 'w':
            case 'W':
                setScene(1);break;
            case 'e':
            case 'E':
                setScene(2);break;
            case 'r':
            case 'R':
                setScene(3);break;
            case 't':
            case 'T':
                setScene(4);break;
            default:
                (*_scene[_idx_scene]).setEffect(key_);
        }
    }
};

#endif /* PSong_h */
