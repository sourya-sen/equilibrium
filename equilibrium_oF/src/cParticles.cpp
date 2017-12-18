#include "cParticles.hpp"

//.................................................
cParticles::cParticles(){
    mass = ofRandomuf();
    isAlive = true;
    life = ofRandom(127);
    id = int(ofRandom(3)) % 2;
}

//.................................................
void cParticles::setup(ofVec2f _pos){
    position = _pos;
}

//.................................................
void cParticles::setup(ofVec2f _pos, float _mass){
    position = _pos;
    mass =_mass;
}

//.................................................
void cParticles::applyForce(ofVec2f force){
    accel += (force / mass);
    
}

//.................................................
void cParticles::update(){
    velocity += accel;
    position += velocity;
    
    velocity *= 0.97;
    
    accel.set(0);
    
    life++;
    
    if(life>255){
        isAlive = false;
    }
}


//.................................................
void cParticles::draw() {
    ofSetColor(255, 255 - life);
    float size = mass * 2.0;
    size = ofClamp(size, 1.0, 2.0);
    ofDrawCircle(position, size);
}
