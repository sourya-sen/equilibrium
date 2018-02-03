#include "cAttractor.hpp"
//.................................................
cAttractor::cAttractor(){
    mass = 0.0;
    cA = 5.0;
    cB = 30.0;
}

//.................................................
void cAttractor::setup(ofVec2f _pos, float _mass){
    position = _pos;
    mass = _mass;
}

//.................................................
ofVec2f cAttractor::attract(cParticles p){
    
    ofVec2f force = position - p.position;
    float distance = force.length();
    
    distance = ofClamp(distance, cA, cB);
    
    force.normalize();
    
    float strength = (mass * p.mass) / (distance * distance);
    
    force.scale(strength);
    
    return force;
    
}

//.................................................
void cAttractor::draw(){
    ofSetColor(ofColor::white);
    ofDrawCircle(position, 3);
    ofDrawBitmapStringHighlight("Mass: " + ofToString(mass), ofVec2f(position.x + 10, position.y));
}

//..................................................
void cAttractor::resetPos(){
    position = ofVec2f(ofRandomWidth(), ofRandomHeight());
}

//..................................................
void cAttractor::resetPosX(){
    position.x = ofRandomWidth();
}

//..................................................
void cAttractor::resetPosY(){
    position.y = ofRandomHeight();
}

//..................................................
void cAttractor::resetMass(int _min, int _max){
    mass = ofRandom(_min, _max);
}
