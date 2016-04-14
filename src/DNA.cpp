#include "DNA.h"

DNA::DNA(){
    
 
    
}

//-------------------------------------------------------
void DNA::setup(int _geneSize)
{
    
    // Initialises genes with random number between 0-1
    geneSize = _geneSize;
    for (int i = 0; i < geneSize; i++) {
        genes.push_back(ofRandom(1));
    }

}
//-----------------------------------------------------------------
void DNA::setup(vector<float> newGenes)
{
    // Update genes
    genes = newGenes;

}
//-----------------------------------------------------------------
// Crossover
DNA DNA::crossover(DNA partner) {
    // A new child
    DNA child;
    child.setup(geneSize);
    //int midpoint = int(ofRandom(genes.size())); // Pick a midpoint (NO RESPECT FOR GENE INTEGRITY)
    int midpoint = int(ofRandom(geneSize)); // Pick a midpoint (RESPECTING GENE INTEGRITY)

    // Half from one, half from the other
    for (int i = 0; i < genes.size(); i++) {
        if (i > midpoint) child.genes[i] = genes[i];
        else              child.genes[i] = partner.genes[i];
    }
    return child;

}
//------------------------------------------------------------------
void DNA::mutate(float mutationRate) {
    
    // Calcuate gene mutation
    for (int i = 0; i < genes.size(); i++) {
      if (ofRandom(1) < mutationRate) {
        genes[i] = ofRandom(1);
      }
   }
}
