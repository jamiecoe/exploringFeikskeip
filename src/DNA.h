#pragma once
#include "ofMain.h"

class DNA{

	public:
		DNA();
		void setup(int geneSize);
        void setup(vector<float> newGenes);
		void draw();
        DNA crossover(DNA partner);
        void mutate(float mutationRate);

		vector<float> genes;
		int geneSize;
        float fitness;
        float mutationAmount;
};
