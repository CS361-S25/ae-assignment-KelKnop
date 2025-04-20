#ifndef PREDATOR_H
#define PREDATOR_H
// Species 2
#include "org.h"

class Predator : public Organism {
    public:
    Predator(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points, 2) {}  // Species 2 for Predators

    void Interact(Organism &other) override {
        // Predators try to eat Prey (species 1)
        if (other.GetSpecies() == 1) {
            std::cout << "Predator is hunting!" << std::endl;
            this->AddPoints(other.GetPoints());  // Predator gains points by hunting
            other.SetPoints(0);    // Prey loses all points (or "dies")
        }
    }
};

#endif
