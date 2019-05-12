#ifndef PTHOUSAND_MILES_H
#define PTHOUSAND_MILES_H

#include "PSong.h"
#include "PSceneRoad.h"
#include "PSceneTunnel.h"
#include "PSceneFloat.h"

class PThousandMiles:public PSong{
public:
    PThousandMiles():PSong(){
        
        _mscene=3;
        _scene.push_back(new PSceneRoad());
        _scene.push_back(new PSceneTunnel());
        _scene.push_back(new PSceneFloat());
        
        _name_song="Thousand Miles";
    }
   
};

#endif
