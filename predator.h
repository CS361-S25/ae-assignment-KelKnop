// The reds

#ifndef PREDATOR_H
#define PREDATOR_H
#include "org.h"  // Include the base Organism class

// Derived class for Species 1 organisms
class predatorOrganism : public Organism {
public:
    predatorOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {}

    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 10000) {
            std::cout << "Species 1 Reproducing" << std::endl;
            emp::Ptr<predatorOrganism> offspring = emp::NewPtr<predatorOrganism>(*this);
            offspring->SetPoints(0);
            this->AddPoints(-10000);
            return offspring;
        } else {
            std::cout << "Species 1: Not enough points to reproduce" << std::endl;
            return emp::Ptr<Organism>(nullptr);
        }
    }

};

#endif
