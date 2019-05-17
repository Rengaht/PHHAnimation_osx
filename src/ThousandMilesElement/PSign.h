//
//  PSign.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PSign_h
#define PSign_h

class PSign:public PElement{
    
//    list<ofPolyline> _path;
    ofMesh _mesh;
    float _alpha;
public:
    
    PSign(ofVec3f start_):PElement(){
        _alpha=ofRandom(120);
        _pos=start_;
        
        _layer=2;
        
        init();
    }
    void draw(){
        
        
        ofPushStyle();
        ofSetLineWidth(WSTROKE);
        ofSetColor(_alpha);
        //        ofNoFill();
        
        ofPushMatrix();
        ofTranslate(_pos);
        //ofDrawEllipse(0,0,100,100);
        //ofRotate(90,vel.x,vel.y,vel.z);
//        for(auto& p:_path) p.draw();
        _mesh.draw();
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        _pos.z+=vel_;
        if(_pos.z>ofGetWidth()*2+_size.y){
            _dead=true;
        }
    }
    void init(){
        
        float m=1;//ofRandom(1,3);
        float r=ofGetHeight()/8*ofRandom(.2,6);
        float w=ofGetHeight()/20;
        _size=ofVec2f(w,r);
        
        float sang=-HALF_PI;
        float ang=PI;
        
//        for(float i=0;i<m;++i){
//            ofPolyline p;
            float tx=ofRandom(.9,1.1)*w;
            
            _mesh.addVertex(ofVec3f(-tx,0,0));
            _mesh.addVertex(ofVec3f(-tx,0,r));
            _mesh.addVertex(ofVec3f(tx,0,r));
        
            _mesh.addVertex(ofVec3f(tx,0,r));
            _mesh.addVertex(ofVec3f(tx,0,0));
            _mesh.addVertex(ofVec3f(-tx,0,0));
            
            float ux1=ofGetHeight()*ofRandom(.5);
            float uy1=ofGetHeight()*ofRandom(.2);
        
            _mesh.addTexCoord(ofVec2f(ux1,uy1));
            _mesh.addTexCoord(ofVec2f(ux1,uy1+r));
            _mesh.addTexCoord(ofVec2f(ux1+tx*2,uy1+r));
        
            _mesh.addTexCoord(ofVec2f(ux1+tx*2,uy1+r));
            _mesh.addTexCoord(ofVec2f(ux1+tx*2,uy1));
            _mesh.addTexCoord(ofVec2f(ux1,uy1));
            
        
//            _path.push_back(p);
//        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};
#endif /* PSign_h */
