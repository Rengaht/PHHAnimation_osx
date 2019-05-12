#include "PScene.h"


PScene::PScene(){
    _idx_stage=0;
}

void PScene::update(float dt_){
    for(auto& e: _element) (*e).update(0,dt_);
}

void PScene::draw(){
	for(auto& e: _element) (*e).draw();

}
void PScene::init(){
    _idx_stage=0;
	for(auto& e: _element) (*e).init();
}
void PScene::end(){
	for(auto& e: _element) (*e).end();
}
void PScene::reset(){
    _idx_stage=0;
    _element.clear();
    //for(auto& e: _element) (*e).reset();
}
void PScene::goNextStage(){
    _idx_stage=min(_idx_stage+1,_mstage-1);
}
