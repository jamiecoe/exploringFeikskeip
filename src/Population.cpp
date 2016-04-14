#include "Population.h"
#include <algorithm>


//-------------------------------------------------------
Population::Population() {
    
}
//-------------------------------------------------------
void Population::setup(float m, int num, int _numSamples)
{
    mutationRate = m;
    numRectX = 10; // number of columns
    numRectY = 5; // number of rows
    numSamples = _numSamples;
    squareWidth = ofGetWidth()/numRectX; // calculate square width
    squareHeight = ofGetHeight()/numRectY; // calculate square height
    generations = 0; // start generation at 0
    
    // for grid of SoundSquares
    for (int i = 0; i < numRectX; i++) {
        for (int j = 0; j < numRectY; j++) {
            float locX = i * squareWidth; // calculate X position
            float locY = j * squareHeight; // calculate Y position
            xLocations.push_back(locX); // store X positions
            yLocations.push_back(locY); // store Y Positions
            DNA newDna;
            newDna.setup(numSamples); // Create new DNA
            SoundSquare newSquare;
            newSquare.setup(newDna, locX, locY, squareWidth, squareHeight, numSamples); // Create new SoundSquare
            currentPopulation.push_back(newSquare); // Add to population
        }
    }

}
//------------------------------------------------------------
void Population::draw(float xEye, float yEye) {

    // For current Population
    for (int i = 0; i < currentPopulation.size(); i++) {
        // Pass in gaze coordinates
        currentPopulation[i].draw(xEye, yEye);
    }
    
}
//------------------------------------------------------------
// Generate a mating pool
void Population::naturalSelection() {
    // Clear the vector
    matingPool.clear();
    // Get maximum fitness
    float maxFitness = getMaxFitness();

    // For population
    for (int i = 0; i < currentPopulation.size(); i++) {
        float fitnessNormal = ofMap(currentPopulation[i].getFitness(), 0, maxFitness, 0, 1); //  Map fitness between 0 - 1
        int n = (int)(fitnessNormal*100); //change to a percentage value
        // Add to mating pool based on percentage value
        for (int j = 0; j < n; j++) {
            matingPool.push_back(currentPopulation[i]);
        }
    }
}
//------------------------------------------------------------
SoundSquare Population::pickOne() {
    
    // Pick from mating pool
    int f = int(ofRandom(matingPool.size()));
    SoundSquare fit = matingPool[f];
    return fit;
    
}
//------------------------------------------------------------
// Create a new generation
void Population::generate() {
    // Refill the population with children from the mating pool
    for (int i = 0; i < currentPopulation.size(); i++) {
        // spin wheel of fortune to pick parents
        int m = int(ofRandom(matingPool.size()));
        int d = int(ofRandom(matingPool.size()));
        SoundSquare mum = matingPool[m];
        SoundSquare dad = matingPool[d];
        // Get their genes
        DNA momgenes = mum.getDNA();
        DNA dadgenes = dad.getDNA();
        // Mate their genes
        DNA child = momgenes.crossover(dadgenes);
        // Mutate child genes
        child.mutate(mutationRate);
        // Fill new population with the new child
        SoundSquare newChild;
        newChild.setup(child, xLocations[i], yLocations[i], squareWidth, squareHeight, numSamples);
        currentPopulation[i] = newChild;
    }
    generations++; // Increment generation
}
//------------------------------------------------------------
int Population::getGenerations() {
    return generations;
  }
//------------------------------------------------------------
// Compute highest fitness for the population
float Population::getMaxFitness() {
    float record = 0;
    for (int i = 0; i < currentPopulation.size(); i++) {
        if (currentPopulation[i].getFitness() > record) {
            record = currentPopulation[i].getFitness();
        }
    }
    return record;
}
