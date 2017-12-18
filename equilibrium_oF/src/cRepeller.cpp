#include "cRepeller.hpp"
//.................................................
cRepeller::cRepeller(){
    
    randomMass = ofRandom(100);
    startMass = ofRandom(100);
    
}

//.................................................
void cRepeller::setup(ofVec2f _pos){
    
    position = _pos;
    
}

//.................................................
ofVec2f cRepeller::repel(cParticles p){
    
    ofVec2f force = position - p.position;
    float distance = force.length();
    
    distance = ofClamp(distance, 2, 18);
    
    force.normalize();
    
    float strength = (mass * p.mass) / (distance * distance);
    
    force.scale(strength);
    
    return -force;
    
}

//.................................................
void cRepeller::resetPos(){
    
    position = ofVec2f(ofRandomWidth(), ofRandomHeight());
    startMass = ofRandom(100);
    randomMass = ofRandom(100);
}

//.................................................
void cRepeller::draw(){
    ofSetColor(ofColor::red);
    ofDrawRectangle(position, 5, 5);
    
}

//.................................................
void cRepeller::update(){
    mass = startMass + sin(ofDegToRad(ofGetFrameNum()/25.0)) * randomMass;
}

