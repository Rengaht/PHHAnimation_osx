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
#include "PCloud.h"
#include "PFloatLine.h"

class PSceneFloat:public PScene{
    
    ofFbo _tex_rock,_tex_cloud;
    float _pos_planet,_pos_cloud,_pos_line;
    
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
        _mstage=2;
        
    }
    void update(float dt){
        for(auto it=_element.begin();it!=_element.end();){
            switch((**it)._layer){
                case 0:
                    (**it).update(_speed*5,dt);
                    break;
                case 1:
                    (**it).update(_speed,dt);
                    break;
                case 2:
                    (**it).update(_speed*.5,dt);
                    break;
            }
            if((**it)._dead) _element.erase(it++);
            else it++;
        }
        
        if(_speed>8) _speed-=1;
        _pos_planet-=_speed;
        _pos_cloud-=_speed*.5;
        
        addPlanet();
        addCloud();
        
//        if(_idx_stage>0){
//            _pos_line-=_speed*5;
//            addLine();
//        }
    }
    void draw(){
        ofClear(255);
        
//        _tex_rock.draw(0,0);
        
//        _camera.begin();
        ofDrawAxis(10);
       
        _tex_cloud.getTexture().bind();
        for(auto& e: _element)
            if(e->_layer==2) (*e).draw();
        _tex_cloud.getTexture().unbind();
        
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
        _pos_cloud=0;
        _pos_line=0;
    }
    void setEffect(int i){
        switch(i){
            case 'a':
                _speed*=2;
                _speed=ofClamp(_speed,10,80);
                break;
            case '.':
            case '>':
                _pos_line=0;
                addLine();
                break;
        }
    }
    void addPlanet(){
        while(_pos_planet<ofGetWidth()*1.2){
            //            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            //            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PPlanet(ofVec2f(_pos_planet,ofRandom(-0.2,1.2)*ofGetHeight()));
            _element.push_back(p);
            _pos_planet+=p->_size.x;
        }
    }
    void addCloud(){
        while(_pos_cloud<ofGetWidth()*1.2){
            //            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            //            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PCloud(ofVec2f(_pos_planet,ofRandom(-0.2,1.2)*ofGetHeight()));
            _element.push_back(p);
            _pos_cloud+=p->_size.x;
        }
    }
    void addLine(){
//        while(_pos_line<ofGetWidth()*1.2){
            //            if(ofRandom(5)<1) _pos_road+=ofVec2f(ofRandom(-250,25),ofRandom(-5,5));
            //            if(abs(_pos_road.y-ofGetHeight()/1.9)>50) _pos_road.y=ofGetHeight()/1.9;
            auto p=new PFloatLine(ofVec2f(_pos_planet,ofRandom(-0.2,1.2)*ofGetHeight()));
//            int m=ofRandom(3,6);
//            for(auto& t:_element){
//                if(t->_layer==1) p->addPlanet((PPlanet*)t);
//            }
        
            _element.push_back(p);
            _pos_line+=p->_size.x;
//        }
    }
   
    void initTexture(){
        
        _tex_rock.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        float c=130;
        float m=ofGetHeight()/c;
        
        _tex_rock.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
       
        //ofSetLineWidth(WSTROKE);
        //ofNoFill();
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float r=(ofNoise(i/10.0,j/10.0)+ofRandom(-.1,.1));
                if(r<.2) continue;
                r=m;
                int mang=ofRandom(4,16);
                float eang=TWO_PI/(float)mang;
                
                 ofSetColor(240,200);
                ofBeginShape();
                for(int k=0;k<=mang;++k) ofVertex(i*m+r*sin(eang*k+ofNoise(i/40.0+k*j/10.0)),j*m+r*cos(eang*k-ofNoise(i*j/20.0)));
                ofEndShape();

                ofSetColor(120,200);
                float dx=ofNoise(i/100.0,j/100.0)-.5;
                float dy=ofRandom(-1,1)*.5;
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i)*m-dy*dx*m,(j+1)*m+dy*m);
                
            }
        ofPopStyle();
        _tex_rock.end();
        
        _tex_cloud.allocate(ofGetHeight(),ofGetHeight(),GL_RGBA);
        
        c=80;
        m=ofGetHeight()/c;
        
        _tex_cloud.begin();
        ofClear(255,255,255,0);
        ofPushStyle();
        
        ofNoFill();
        //        ofBeginShape();
        for(int i=0;i<c;++i)
            for(int j=0;j<c;++j){
                float r=(ofNoise(i/20.0,j/20.0)+ofRandom(-.1,.1));
                if(r<.5) continue;
                r=m;
                int mang=ofRandom(4,16);
                float eang=TWO_PI/(float)mang;
                
                ofSetColor(120,120);
                ofBeginShape();
                for(int k=0;k<=mang;++k) ofVertex(i*m+r*sin(eang*k+ofNoise(i/40.0+k*j/10.0)),j*m+r*cos(eang*k-ofNoise(i*j/20.0)));
                ofEndShape();
                
                ofSetColor(120,200);
                float dx=ofNoise(i/100.0,j/100.0)-.5;
                float dy=ofRandom(-1,1)*.5;
                ofDrawLine(i*m+dx*m,j*m-dy*m,(i)*m-dy*dx*m,(j+1)*m+dy*m);
                
            }
        //        ofEndShape();
        ofPopStyle();
        _tex_cloud.end();
    }
};

#endif /* PSceneFloat_h */
