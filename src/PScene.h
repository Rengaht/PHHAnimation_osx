#ifndef PSCENE_H
#define PSCENE_H

#include "ofMain.h"
#include "PElement.h"

class PScene{

public:
	PScene();

	virtual void init();
	virtual void end();
	virtual void update(float dt_);
	virtual void draw();
	virtual void reset();
    virtual void setEffect(int i_){};
    
	list<PElement*> _element;
    
    int _idx_stage;
    int _mstage;
    void goNextStage();
};


#endif // !PSCENE_H
