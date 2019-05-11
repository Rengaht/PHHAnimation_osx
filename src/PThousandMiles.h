#ifndef PTHOUSAND_MILES_H
#define PTHOUSAND_MILES_H

#include "PScene.h"
#include "PMountain.h"

class PThousandMiles:public PScene{
    float dx=0;
public:
    static float _speed;
    ofFbo _tex_mountain;
    
	PThousandMiles(){
		PScene();
        _speed=10;
        initTexture();
        addMountain();
       
	}

	void draw(){

		ofBackground(255);
		ofSetColor(0);
		ofDrawBitmapString("Thousand Mlles",50,50);
        
//        _tex_mountain.draw(0,0);
        
//        ofEnableNormalizedTexCoords();
        ofDisableArbTex();
        _tex_mountain.getTexture().bind();
        PScene::draw();
        _tex_mountain.getTexture().unbind();
        
//        ofDisableNormalizedTexCoords();
        
	}
    void update(float dt){
        for(auto it=_element.begin();it!=_element.end();){
            (**it).update(_speed,dt);
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        dx-=_speed;
        addMountain();
    }
    void addMountain(){
        while(dx<ofGetWidth()*1.2){
            auto p=new PMountain(dx);
            _element.push_back(p);
            dx+=p->_size.x*ofRandom(.1,.9);
        }
    }
    void initTexture(){
        
        _tex_mountain.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=50;
        float m=ofGetHeight()/c;
        _tex_mountain.begin();
            ofClear(255,255,255,0);
            ofSetColor(0);
            for(int i=0;i<c;++i)
                for(int j=0;j<c;++j){
                    float dx=ofNoise(i/10.0,j/10.0)-.5;
                    float dy=ofRandom(-1,1)*.5;
                    ofDrawLine(i*m+dx*m,j*m-dy*m,(i+1)*m+dy*m,(j)*m+dx*m);
                }
        _tex_mountain.end();
    }
};


#endif
