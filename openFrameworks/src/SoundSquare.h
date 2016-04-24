#pragma once
#include "ofMain.h"
#include "DNA.h"

class SoundSquare {

	public:
		SoundSquare();
		void setup(DNA _dna, float _x, float _y, float w, float h, int _numOfSamples);
		void draw(float xEye, float yEye);
        bool eyeContact(float xEye, float yEye);
        float getFitness();
        SoundSquare crossover(SoundSquare partner);
        DNA getDNA();
        void mutate(float mutationRate);

		DNA dna;
        float fitness;
        float x, y;
        float squareWidth, squareHeight;
        int opacity;
        int numSamples;
        vector<int> audioSamples;
};
