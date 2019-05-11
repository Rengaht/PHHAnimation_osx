#include "PScene.h"


PScene::PScene(){

}

void PScene::update(float dt_){
    for(auto& e: _element) (*e).update(0,dt_);
}

void PScene::draw(){
	for(auto& e: _element) (*e).draw();

}
void PScene::init(){
	for(auto& e: _element) (*e).init();
}
void PScene::end(){
	for(auto& e: _element) (*e).end();
}
void PScene::reset(){
	for(auto& e: _element) (*e).reset();
}

