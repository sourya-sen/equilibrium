#pragma once
#include "ofMain.h"
#include "cParticles.hpp"

class cRepeller{
public:
    cRepeller();
    
    ofVec2f position;
    float mass;
    float startMass;
    float randomMass;
    
    void setup(ofVec2f _pos);
    void resetPos();
    ofVec2f repel(cParticles p);
    void draw();
    void update();
};
