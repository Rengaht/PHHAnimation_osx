#pragma once

#include "ofMain.h"
#include "ofxNDISender.h"
#include "PYoungNight.h"
#include "PThousandMiles.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyReleased(int key);
		void mouseReleased(int x, int y, int button);
		

		float _dmillis;
		float _last_millis;

		int _idx_scene;
		vector<PScene*> _scene;

		void setScene(int set_);


		ofxNDISender _NDIsender;
		
		ofPixels _pixels;
		ofFbo _fbo;
};
