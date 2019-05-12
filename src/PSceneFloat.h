//
//  PSceneFloat.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PSceneFloat_h
#define PSceneFloat_h

#include "PScene.h"
#include "PPlanet.h"

class PSceneFloat:public PScene{
    
    ofFbo _tex_rock;
    float _pos_planet;
    
public:
    static float _speed;
    ofCamera _camera;
    
    PSceneFloat():PScene(){
        _camera.setPosition(ofVec3f(0,ofGetHeight()/4,ofGetWidth()));
        _camera.setFov(120);
        _camera.setNearClip(0);
        _camera.setFarClip(ofGetWidth()*2);
        
        reset();
        initTexture();
    }
    void update(float dt){
        for(auto it=_element.begin();it!=_element.end();){
            (**it).update(_speed,dt);
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        
        if(_speed>1) _speed-=.25;
        _pos_planet-=_speed;
        addPlanet();
    }
    void draw(){
        ofClear(255);
        
//        _tex_rock.draw(0,0);
        
//        _camera.begin();
        ofDrawAxis(10);
        
        
        _tex_rock.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==1) (*e).draw();
        _tex_rock.getTexture().unbind();
        
        
        for(auto& e: _element)
            if(e->_layer==0) (*e).draw();
        
//        _camera.end();
        
    }
    void reset(){
        PScene::reset();
        _pos_planet=0;
    }
    void setEffect(int i){
        switch(i){
            case 'a':
                _speed*=2;
                _speed=ofClamp(_speed,10,80);
                break;
        }
    }
    void addPlanet(){
        while(_pos_planet<ofGetWidth()){
            //            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            //            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PPlanet(ofVec2f(_pos_planet,ofRandom(-0.2,1.2)*ofGetHeight()));
            _element.push_back(p);
            _pos_planet+=p->_size.x;
        }
    }
   
    void initTexture(){
        
        _tex_rock.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=120;
        float m=ofGetHeight()/c;
        
        _tex_rock.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
        ofSetColor(120);
        //ofSetLineWidth(WSTROKE);
        //ofNoFill();
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float r=(ofNoise(i/20.0,j/20.0)+ofRandom(-.1,.1));
                if(r<.4) continue;
                r=m;
                int mang=ofRandom(4,16);
                float eang=TWO_PI/(float)mang;

                ofBeginShape();
                for(int k=0;k<=mang;++k) ofVertex(i*m+r*sin(eang*k+ofNoise(i/40.0+k*j/10.0)),j*m+r*cos(eang*k-ofNoise(i*j/20.0)));
                ofEndShape();


            }
        ofPopStyle();
        _tex_rock.end();
    }
};

#endif /* PSceneFloat_h */
