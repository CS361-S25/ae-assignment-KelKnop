// The blues

#ifndef PREY_H
#define PREY_H
#include "org.h"  // Include the base Organism class

// Derived class for Species 0 organisms
class preyOrganism : public Organism {
public:
    preyOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {}

    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 120) {
            std::cout << "Species 0 Reproducing" << std::endl;
            emp::Ptr<preyOrganism> offspring = emp::NewPtr<preyOrganism>(*this);
            offspring->SetPoints(0);
            this->AddPoints(-120);
            return offspring;
        } else {
            std::cout << "Species 0: Not enough points to reproduce" << std::endl;
            return emp::Ptr<Organism>(nullptr);
        }
    }
};

#endif
