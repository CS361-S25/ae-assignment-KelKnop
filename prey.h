// The blues (Prey Organism)

#ifndef PREY_H
#define PREY_H

#include "org.h"  // Include the base Organism class

// preyOrganism: Represents the prey species (Species 0)
class preyOrganism : public Organism {
public:
    // Constructor: sets species and optionally starting points
    preyOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {
        SetSpecies(0);  // Species 0 = prey
    }

    // Processing logic each update
    void Process() override {
        // Prey gains points over time (e.g., from photosynthesis or grazing)
        this->AddPoints(15);
    }

    // Check if the prey is ready to reproduce
    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 180) {
            // Create offspring with 30 starting points
            emp::Ptr<preyOrganism> offspring = emp::NewPtr<preyOrganism>(*this);
            offspring->SetPoints(30);
            this->AddPoints(-180);  // Cost of reproduction
            return offspring;
        } else {
            return emp::Ptr<Organism>(nullptr);
        }
    }
};

#endif // PREY_H
