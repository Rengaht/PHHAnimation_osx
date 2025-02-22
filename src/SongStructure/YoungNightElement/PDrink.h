//
//  PDrink.h
//  PHHAnimation
//
//  Created by RengTsai on 2019/5/21.
//

#ifndef PDrink_h
#define PDrink_h

class PDrink:public PElement{
    ofMesh _mesh;
    ofMesh _mesh_pinhead;
    
    ofColor _color;
    FrameTimer _timer_move,_timer_pin;
    float _vel;
    
    ofVec2f _pos_shadow;
    
    float _seg;
    float _rad_texcoord;
    float _height_drink;
public:
    
    int _stage;
    PDrink(ofVec2f p,float w){
        _color=ofColor(ofRandom(200,255),ofRandom(20),ofRandom(60),120);
        
        reset();
        _timer_pin=FrameTimer(100);
        _timer_move.restart();
        _timer_pin.restart();
        
        _vel=1;
        _height_drink=ofRandom(10,50);
        
        _pos=p;
        init(w);
        
        _layer=1;
    }
    void init(float w){
        
        _size=ofVec2f(w,w);
        float r=w/2;
        
        _mesh.setMode(OF_PRIMITIVE_TRIANGLES);
        _seg=64;
        float eth=TWO_PI/_seg;
        
        float mr=w;
        _rad_texcoord=ofRandom(.5,1.2)*mr;
        
        float tx=ofGetHeight()/2+ofRandom(-20,20);
        float ty=ofGetHeight()/2+ofRandom(-20,20);
        
        
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            _mesh.addVertex(ofVec2f(0,0));
            _mesh.addVertex(ofVec2f(mr*sin(th),mr*cos(th)));
            _mesh.addVertex(ofVec2f(mr*sin(th+eth),mr*cos(th+eth)));
            
            _mesh.addTexCoord(ofVec2f(tx,ty));
            _mesh.addTexCoord(ofVec2f(tx+_rad_texcoord*sin(th),ty+_rad_texcoord*cos(th)));
            _mesh.addTexCoord(ofVec2f(tx+_rad_texcoord*sin(th+eth),ty+_rad_texcoord*cos(th+eth)));
        }
        //        }
        
        
        _pos_shadow=ofVec2f(ofRandom(-20,20),ofRandom(-20,20));
        
        
        ofVec2f ph_(0,0);
        ofVec2f pin_(0,-w*1.2);
        //        pin_.rotate(-5);
        
        ofVec2f norm(pin_.y,-pin_.x);
        norm.normalize();
        norm*=w/20;
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x,ph_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x+norm.x,ph_.y+pin_.y+norm.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(0,w/10));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        
        ph_=ph_+pin_;
        pin_.normalize();
        pin_*=w*.6;
        pin_.rotate(-30);
        norm.rotate(-30);
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x,ph_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,0));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x+norm.x,ph_.y+pin_.y+norm.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+pin_.x,ph_.y+pin_.y));
        _mesh_pinhead.addVertex(ofVec2f(ph_.x+norm.x,ph_.y+norm.y));
        
        _mesh_pinhead.addTexCoord(ofVec2f(0,0));
        _mesh_pinhead.addTexCoord(ofVec2f(0,w/10));
        _mesh_pinhead.addTexCoord(ofVec2f(w,w/10));
        
        
        
    }
    
    void draw(){
        
        ofPushStyle();
        ofFill();
        
        //        float t=_timer_move.valEaseInOut();
        ofPushMatrix();
        ofTranslate(_pos);
        ofPushMatrix();
//        ofRotate(_timer_rot.val()*_ang_rot*_vel);
        
        ofSetColor(_color,128);
        ofPushMatrix();
        ofTranslate(_pos_shadow);
        for(int i=0;i<_height_drink*_anim_loop.valEaseOut();++i){
            ofTranslate(0,-10);
            _mesh.draw();
        }
        
        ofPopMatrix();
        
        ofSetColor(_color,255);
        for(int i=0;i<_height_drink*_anim_loop.valEaseOut();++i){
            ofTranslate(0,-10);
            _mesh.draw();
        }
        ofPopMatrix();
        
        // draw border
        ofPushStyle();
        ofSetColor(255);
        ofNoFill();
            ofDrawCircle(0,0,_size.x);
            ofDrawCircle(0,-_height_drink*10,_size.x);
            ofDrawLine(_size.x,0,_size.x,-_height_drink*10);
            ofDrawLine(-_size.x,0,-_size.x,-_height_drink*10);
        ofPopStyle();
        
     
        
        
        ofPushMatrix();
        ofTranslate(-_size.x*1.1,-_size.y*1.2);
//        ofRotate(-_timer_pin.val()*_ang_pin);
        
        ofSetColor(255,128);
        ofPushMatrix();
        ofTranslate(_pos_shadow*.33);
        _mesh_pinhead.draw();
        ofPopMatrix();
        ofSetColor(255);
        _mesh_pinhead.draw();
        
        
        ofPopMatrix();
        
        ofPopMatrix();
        
        ofPopStyle();
        
    }
    void end(){
        
    }
    void reset(){
        _vel=ofRandom(2)<1?1:-1;
//        _ang_rot=ofRandom(.5,5)*360;
//        _ang_pin=ofRandom(0,10);
//        _timer_rot=FrameTimer(ofRandom(MIN_RECORD_INTERVAL,MAX_RECORD_INTERVAL),100);
        
    }
    void update(float vel_,float dt_){
        PElement::update(0,dt_);
//        _timer_rot.update(dt_);
        _timer_pin.update(dt_);
//        if(_timer_rot.val()==1){
//            reset();
//            _timer_pin.restart();
//            _timer_rot.restart();
//        }
        
        if(ofRandom(10)>1) return;
        
        _pos_shadow=ofVec2f(ofRandom(-1,1),ofRandom(-1,1))*_size.x*.05;
        
        //        if(ofRandom(3)>1) return;
        
        float eth=TWO_PI/_seg;
        float w=_size.x;
        
        int m=0;
        for(float i=0;i<=_seg;++i){
            float th=eth*i;
            float tx=ofGetHeight()/2+ofGetFrameNum()%10-5+ofRandom(-1,1);
            float ty=ofGetHeight()/2+ofGetFrameNum()%10-5+ofRandom(-1,1);
            
            _mesh.setTexCoord(m++,ofVec2f(tx,ty));
            _mesh.setTexCoord(m++,ofVec2f(tx+_rad_texcoord*sin(th),ty+_rad_texcoord*cos(th)));
            _mesh.setTexCoord(m++,ofVec2f(tx+_rad_texcoord*sin(th+eth),ty+_rad_texcoord*cos(th+eth)));
        }
        
        
    }
};
#endif /* PDrink_h */
