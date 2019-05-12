#pragma once


#define DRAW_DEBUG
#define WSTROKE 1


#include "ofMain.h"
#include "ofxNDISender.h"
#include "PYoungNight.h"
#include "PThousandMiles.h"



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mouseReleased(int x, int y, int button);
		

		float _dmillis;
		float _last_millis;

		int _idx_song;
		vector<PSong*> _song;

		void setScene(int set_);
        void mapEffect(int key_);

		ofxNDISender _NDIsender;
		
		ofPixels _pixels;
		ofFbo _fbo;
    
        bool _recording;
};
