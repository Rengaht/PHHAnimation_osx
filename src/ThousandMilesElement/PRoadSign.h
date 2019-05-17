//
//  PRoadSign.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/12.
//

#ifndef PRoadSign_h
#define PRoadSign_h

class PRoadSign:public PElement{
    
    list<ofPolyline> _path;
    float _alpha;
public:
    
    PRoadSign(ofVec3f start_):PElement(){
        _alpha=ofRandom(120);
        _pos=start_;
        
        _layer=0;
        
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
        for(auto& p:_path) p.draw();
        ofPopMatrix();
        
        ofPopStyle();
    }
    void update(float vel_,float dt_){
        _pos.z+=vel_*1.2;
        if(_pos.z>ofGetWidth()*2+_size.y){
            _dead=true;
        }
    }
    void init(){
        
        float m=ofRandom(80,150);
        float r=ofGetHeight()/8*ofRandom(.2,6);
        float w=ofGetHeight();
        _size=ofVec2f(w,r);
        
        float sang=-HALF_PI;
        float ang=PI;
        
        for(float i=0;i<m;++i){
            ofPolyline p;
            float tx=ofRandom(.6,1.2)*w;
            float mv=ofRandom(3,12);
            for(float j=0;j<=mv;++j){
                p.addVertex(ofVec3f(tx*sin(sang+ang/m*i)+r*.2*ofNoise(i*j/10),tx*cos(sang+ang/m*i)+ofNoise(i*j/10.0)*.2*r,ofRandom(-.2,.2)*r+r/mv*j));
            }
//            p.addVertex(ofVec3f(tx*sin(sang+ang/m*(i+.5)),tx*cos(sang+ang/m*(i+.5)),ofRandom(-.2,.2)*r+r));
//            p.addVertex(ofVec3f(tx*sin(sang+ang/m*(i+.5)),tx*cos(sang+ang/m*(i+.5)),ofRandom(-.2,.2)*r));
            
            _path.push_back(p);
        }
        
    }
    void end(){
        
    }
    void reset(){
        
    }
    
};




#endif /* PRoadSign_h */
