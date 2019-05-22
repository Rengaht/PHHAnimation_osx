#ifndef PYOUNG_NIGHT_H
#define PYOUNG_NIGHT_H

#include "PSong.h"
#include "PSceneRecord.h"
#include "PSceneGrid.h"
#include "PSceneSmoke.h"
#include "PSceneSunset.h"

class PYoungNight:public PSong{

public:
    bool _effect_show;
    PYoungNight():PSong(){
        _mscene=3;
		_name_song="Young Night";
        
        _scene.push_back(new PSceneGrid());
        _scene.push_back(new PSceneSunset());
        _scene.push_back(new PSceneRecord());
        _scene.push_back(new PSceneSmoke());
        
        _effect_show=false;
        
	}
    void setScene(int index_){
        if(index_<0 || index_>=_mscene) return;
        _idx_scene=index_;
        _scene[_idx_scene]->reset();
    }
    void update(float dt_){
        (*_scene[_idx_scene]).update(dt_);
        
        if(_effect_show) (*_scene[3]).update(dt_);
    }
    void draw(){
        (*_scene[_idx_scene]).draw();
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        if(_effect_show && _idx_scene>0) (*_scene[3]).draw();
        
        ofDisableBlendMode();
    }
    void setEffect(int key_){
        switch(key_){
            case '/':
            case '?':
                _effect_show=!_effect_show;
                break;
            case 'o':
            case 'O':
            case 'p':
            case 'P':
                _scene[3]->setEffect(key_);
                break;
            default:
                PSong::setEffect(key_);
                break;
        }
                
    }
    void reset(){
        PSong::reset();
        _effect_show=false;
    }
};


#endif
