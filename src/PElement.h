#ifndef PELEMENT_H
#define PELEMENT_H

#include "FrameTimer.h"
#define INTERVAL_ELEM_LOOP 500

class PElement{
	
	int _layer;
	bool _loop;
	FrameTimer _anim_loop;

public:
    
    ofVec2f _pos,_size;
    bool _dead;
    
	PElement(){
        _dead=false;
		_layer=0;
		_loop=true;
		_anim_loop=FrameTimer(INTERVAL_ELEM_LOOP,ofRandom(.5)*INTERVAL_ELEM_LOOP);
	}
    ~PElement(){};
	
    virtual void init(){};
    virtual void end(){};
    virtual void update(float vel_,float dt_){};
    virtual void draw(){};
    virtual void reset(){};



};

#endif
