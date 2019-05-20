#ifndef PYOUNG_NIGHT_H
#define PYOUNG_NIGHT_H

#include "PSong.h"
#include "PSceneRecord.h"
#include "PSceneGrid.h"
#include "PSceneSmoke.h"
#include "PSceneSunset.h"

class PYoungNight:public PSong{

public:
    PYoungNight():PSong(){
        _mscene=4;
		_name_song="Young Night";
        
        _scene.push_back(new PSceneGrid());
        _scene.push_back(new PSceneSunset());
        _scene.push_back(new PSceneRecord());
        _scene.push_back(new PSceneSmoke());
        
	}

};


#endif
