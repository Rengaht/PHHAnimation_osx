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

	list<PElement*> _element;

};


#endif // !PSCENE_H
