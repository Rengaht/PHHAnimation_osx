//
//  PRock.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PRock_h
#define PRock_h
#include "PElement.h"

class PRock:public PElement{
    
    ofMesh _mesh;
    float _alpha;
public:
    
    PRock(ofVec3f start_):PElement(){
        _alpha=ofRandom(180,255);
        _pos=start_;
        
        _layer=1;
        
        init();
    }
    void draw(){
        
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha);
        //        ofNoFill();
        
        ofPushMatrix();
        ofTranslate(_pos);
        _mesh.draw();
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
//        _pos.z+=vel_*10;
//        if(_pos.z>ofGetWidth()*2+_size.y){
//            _dead=true;
//        }
        _pos.z-=vel_*10;
        if(_pos.z<-ofGetWidth()*2-_size.y){
            _dead=true;
        }
    }
    void init(){
       
        int m=ofRandom(4,10);
        float r=ofGetHeight()/5*ofRandom(.3,2.5);
        float rat=ofRandom(.2,.6);
        _size=ofVec2f(r*2,r*rat*2);
        
        float aang=-HALF_PI+ofRandom(PI);
        float rr=ofRandom(.9,1.5)*ofGetHeight();
        float rx=rr*sin(aang);
        float ry=rr*cos(aang);
        
        for(int k=0;k<m;++k){
            
            
            float eang=TWO_PI/ofRandom(3,6);
            vector<float> corner;
            float sang=HALF_PI*3;
            float ang=sang;
            while(ang<sang+TWO_PI){
                corner.push_back(ang);
                ang+=ofRandom(.4,1.5)*eang;
            }
            
            int mcorner=corner.size();
            
            
            float rt=ofRandom(.5,1);
            float tx=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
            float ty=ofGetHeight()/2;//+ofRandom(-1,1)*r;//ofRandom(r*rt*4,ofGetHeight()-r*rt*4);
            
           
            float mx=ofRandom(-r,r)+rx;
            float my=ofRandom(-r*rat,r*rat)+ry;
            float mz=ofRandom(-10,10);
            //ofMesh tm_;
            float mr=r/m*ofRandom(.5,m);
            
            _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
            for(int i=0;i<mcorner;++i){
                _mesh.addVertex(ofVec3f(mx,my,0));
                
                float tt=cos(corner[i]);
                _mesh.addVertex(ofVec3f(mx+mr*sin(corner[i]),my+mr*tt,mz));
                
                tt=cos(corner[(i+1)%mcorner]);
                _mesh.addVertex(ofVec3f(mx+mr*sin(corner[(i+1)%mcorner]),my+mr*tt,mz));
                
                _mesh.addTexCoord(ofVec2f(tx,ty));
                _mesh.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[i]),0.0f),min((float)ofGetHeight(),ty+r*rt*cos(corner[i]))));
                _mesh.addTexCoord(ofVec2f(max(tx+r*rt*sin(corner[(i+1)%mcorner]),0.0f),min((float)ofGetHeight(),ty+r*rt*cos(corner[(i+1)%mcorner]))));
            }
            //_mesh.push_back(tm_);
        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};
#endif /* PRock_h */
