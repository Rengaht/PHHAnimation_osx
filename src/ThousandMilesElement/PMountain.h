#ifndef PMOUNTAIN_H
#define PMOUNTAIN_H

#include "PElement.h"

class PMountain:public PElement{

    ofMesh _mesh;
    float _alpha;
public:
    PMountain(float dx_):PElement(){
        _alpha=ofRandom(120,180);
        _pos=ofVec2f(dx_,ofGetHeight()/2+ofRandom(-50,0));
        _use_texture=true;
        _layer=1;
        
        init();
	}
	void draw(){
        
    
        ofPushStyle();
        ofSetColor(_alpha);
        
        ofPushMatrix();
        ofTranslate(_pos);
        //ofRotate(90,vel.x,vel.y,vel.z);
        _mesh.draw();
        ofPopMatrix();
        
        ofPopStyle();
	}
    void update(float vel_,float dt_){
       // _pos.x-=vel_*ofMap(_pos.y,ofGetHeight()/2-50,ofGetHeight()/2,0.5,1);
         _pos.x-=vel_*ofMap(_pos.y,ofGetHeight()/2-100,ofGetHeight()/2,.2,1);
        if(_pos.x<-_size.x){
            _dead=true;
        }
    }
    void init(){
        
        int m=ofRandom(4,16);
        float r=ofGetHeight()/12*ofRandom(.4,6)/2;
        float rat=ofRandom(.1,.5);
        
        _size=ofVec2f(r*2,r*rat*2);
        
        float eang=TWO_PI/float(m);
        vector<float> corner;
        float sang=HALF_PI*3;
        float ang=sang;
        while(ang<sang+TWO_PI){
            corner.push_back(ang);
            ang+=ofRandom(.8,1.2)*eang;
        }
        
        int mcorner=corner.size();
        
        float rt=ofRandom(.6,3);
        float tx=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
        float ty=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        for(int i=0;i<mcorner;++i){
            _mesh.addVertex(ofVec3f(0,0,0));
            
            float tt=cos(corner[i]);
            if(tt>0) tt=ofRandom(-.1,.1);
            _mesh.addVertex(ofVec3f(r*sin(corner[i]),r*rat*tt,0));
            
            tt=cos(corner[(i+1)%mcorner]);
            if(tt>0) tt=ofRandom(-.1,.1);
            _mesh.addVertex(ofVec3f(r*sin(corner[(i+1)%mcorner]),r*rat*tt,0));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[i]),0.0f),min((float)ofGetHeight(),ty+r*rt*rat*cos(corner[i]))));
            _mesh.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[(i+1)%mcorner]),0.0f),min((float)ofGetHeight(),ty+r*rt*rat*cos(corner[(i+1)%mcorner]))));
        }
    }
    void end(){
        
    }
    void reset(){
        
    }

};

#endif
