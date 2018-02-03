#pragma once
#include "ofMain.h"
#include "cParticles.hpp"

class cAttractor{
public:
    
    cAttractor();
    
    ofVec2f position;
    float mass;
    float cA, cB;
    
    void setup(ofVec2f _pos, float _mass);
    ofVec2f attract(cParticles p);
    
    void resetPos();
    void resetPosX();
    void resetPosY();
    
    void draw();
    
    void resetMass(int _min, int _max);
};
