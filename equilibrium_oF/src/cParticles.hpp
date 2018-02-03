#pragma once
#include "ofMain.h"

class cParticles{
public:
    
    cParticles();
    
    ofVec2f position;
    ofVec2f velocity;
    ofVec2f accel;
    float mass;
    int life;
    bool isAlive;
    bool id;
    
    void applyForce(ofVec2f force);
    void setup(ofVec2f _pos);
    void setup(ofVec2f _pos, float _mass);
    void update();
    void draw();
    
    float sizeMultiplier;
    
};



