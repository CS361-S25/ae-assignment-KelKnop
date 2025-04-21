// The reds (Predator Organism)

#ifndef PREDATOR_H
#define PREDATOR_H

#include "org.h"  // Include the base Organism class

// PredatorOrganism: Represents the predator species (Species 1)
class predatorOrganism : public Organism {
public:
    // Constructor: sets species and optionally starting points
    predatorOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {
        SetSpecies(1);  // Species 1 = predator
    }

    // Processing logic each update
    void Process() override {
        // Predators lose points over time to simulate energy cost
        this->AddPoints(-30);
    }

    // Interact with another organism
    void Interact(Organism &other) override {
        std::cout << "Predator eating prey..." << std::endl;

        // Predator gains points from prey, prey is marked for death
        this->AddPoints(other.GetPoints());
        other.SetPoints(-1);  // Mark prey for removal
    }

    // Check if the predator is ready to reproduce
    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 8000) {
            std::cout << "Predator: Reproducing" << std::endl;

            // Create offspring with 100 points, subtract cost from parent
            emp::Ptr<predatorOrganism> offspring = emp::NewPtr<predatorOrganism>(*this);
            offspring->SetPoints(7500);
            this->AddPoints(-8000);
            return offspring;
        } else {
            return emp::Ptr<Organism>(nullptr);
        }
    }
};

#endif // PREDATOR_H
