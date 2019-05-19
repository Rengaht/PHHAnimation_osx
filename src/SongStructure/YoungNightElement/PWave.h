//
//  PWave.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/20.
//

#ifndef PWave_h
#define PWave_h
#include "PElement.h"

class PWave:pubic PElement{
    ofMesh _mesh;
    ofVec2f _vel;
public:
     PSunset(ofVec2f p,float w,float t){
         _pos=p;
         init(w);
     }
    void init(float w){
        
        _size=ofVec2f(w,w);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=64;
        float eth=TWO_PI/_seg;
        
        float tx=ofGetHeight()/2;
        float ty=ofGetHeight()/2;
        
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            _mesh.addVertex(ofVec2f(0,0));
            _mesh.addVertex(ofVec2f(w*sin(th),w*cos(th)));
            _mesh.addVertex(ofVec2f(w*sin(th+eth),w*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th),ty+w*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+w*sin(th+eth),ty+w*cos(th+eth)));
        }
    }
}

#endif /* PWave_h */
