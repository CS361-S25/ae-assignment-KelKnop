#ifndef PREY_H
#define PREY_H
// Species 1
#include "org.h"

class Prey : public Organism {
    public:
    Prey(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points, 1) {}  // Species 1 for Prey

    void Interact(Organism &other) override {
        // Prey tries to avoid Predators (species 2)
        if (other.GetSpecies() == 2) {
            std::cout << "Prey is fleeing from Predator!" << std::endl;
            this->SetPoints(0);  // Prey loses some points from stress
        }
    }
};

#endif
