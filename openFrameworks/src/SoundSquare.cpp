#include "SoundSquare.h"

//-------------------------------------------------------
SoundSquare::SoundSquare(){
    

}
//-------------------------------------------------------
void SoundSquare::setup(DNA _dna, float _x, float _y, float w, float h, int _numOfSamples)
{
    dna = _dna;
    x = _x;
    y = _y;
    fitness = 1;
    opacity = 0;
    squareWidth = w;
    numSamples = _numOfSamples;
    squareHeight = h;
    // Use genes to create integer array (phenotype)
    for (int i = 0; i < numSamples; i++) {
        int pheno = ofMap(dna.genes[i], 0, 1, 0, numSamples);
        audioSamples.push_back(pheno);
    }
    
}
//-------------------------------------------------------
void SoundSquare::draw(float xEye, float yEye)
{
 
    // Code to update and visual fitness
    
    ofPushStyle();
    // If the person is looking at SoundSquare
    if (eyeContact(xEye, yEye)) {
        ofSetColor(255, opacity);
        ofFill();
        ofDrawRectangle(x, y, squareWidth, squareHeight);
        fitness += 0.25; // Increase fitness
        if (opacity < 255) opacity+=1;
        else opacity = 255;
    }
    else {
        opacity = 0;
    }
    ofPopStyle();
    
    
}
//-------------------------------------------------------
bool SoundSquare::eyeContact(float xEye, float yEye)
{
    // Checks whether gaze coordinates are in SoundSquare
    
    if (xEye > x && xEye < x + squareWidth && yEye > y && yEye < y + squareHeight) {
        return true;
    }
    else return false;
}
//--------------------------------------------------------
float SoundSquare::getFitness () {

    return fitness;
}
//--------------------------------------------------------
DNA SoundSquare::getDNA() {
    
    return dna;
}
