#ifndef PELEMENT_H
#define PELEMENT_H

#include "FrameTimer.h"
#define INTERVAL_ELEM_LOOP 500

class PElement{
	
	
public:
    
    ofVec3f _pos,_size;
    bool _dead;
    bool _use_texture;

    int _layer;
    bool _loop;
    FrameTimer _anim_loop;

	PElement(){
        _dead=false;
		//_layer=0;
		_loop=true;
        _use_texture=false;
		_anim_loop=FrameTimer(INTERVAL_ELEM_LOOP,ofRandom(.5)*INTERVAL_ELEM_LOOP);
        _anim_loop.restart();
	}
    ~PElement(){}
	
    virtual void init(){}
    virtual void end(){}
    virtual void update(float vel_,float dt_){
        _anim_loop.update(dt_);
        if(_anim_loop.val()==1) _anim_loop.restart();
    }
    virtual void draw(){}
    virtual void reset(){}



};

#endif
