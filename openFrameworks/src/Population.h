#pragma once
#include "ofMain.h"
#include "SoundSquare.h"

class Population{

  public:
    Population();
    void setup(float m, int num, int _numSamples);
    void draw(float xEye, float yEye);
    void calcFitness();
    void naturalSelection();
    void generate();
    bool finished();
    int getGenerations();
    float getMaxFitness();
    SoundSquare pickOne();

    float mutationRate;            // Mutation rate
    vector<SoundSquare> currentPopulation; // Vector to hold the current population
    vector<SoundSquare> matingPool; // Vector which we will use for our "mating pool"
    int generations;               // Number of generations
    int numRectX, numRectY;
    int numSamples;
    float squareWidth, squareHeight;
    vector<float> xLocations;
    vector<float> yLocations;
};
