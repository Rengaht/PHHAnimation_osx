#ifndef PYOUNG_NIGHT_H
#define PYOUNG_NIGHT_H

#include "PScene.h"

class PYoungNight:public PScene{

public:
    static float _speed;
    
    PYoungNight():PScene(){
		
	}

	void draw(){

		ofBackground(0);
		ofDrawBitmapString("Young Nights",50,50);
		PScene::draw();
	}
};


#endif
