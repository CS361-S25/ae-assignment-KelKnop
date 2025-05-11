#ifndef PREY_H
#define PREY_H

#include "org.h"  // Include the base Organism class

// preyOrganism: Represents the prey species (Species 0)
class preyOrganism : public Organism {
public:
    /**
     * Constructor for the prey organism.
     * Sets the species to 0 (prey) and optionally initializes energy points.
     * 
     * @param _random Pointer to random number generator.
     * @param _points Initial energy points (default: 0).
     */
    preyOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {
        SetSpecies(0);  // Species 0 = prey
    }

    /**
     * Processes the prey's behavior each update.
     * Prey gains energy over time (e.g., through grazing or photosynthesis).
     */
    void Process() override {
        this->AddPoints(15);  // Prey gains 15 points per update
    }

    /**
     * Checks if the prey is ready to reproduce.
     * If the prey has enough energy, it reproduces and creates an offspring.
     * 
     * @return A new prey organism if ready to reproduce, or nullptr if not.
     */
    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 180) {
            // Create offspring with 30 starting points
            emp::Ptr<preyOrganism> offspring = emp::NewPtr<preyOrganism>(*this);
            offspring->SetPoints(30);  // Set offspring's energy
            this->AddPoints(-180);     // Deduct energy from parent
            return offspring;          // Return new offspring
        } else {
            return emp::Ptr<Organism>(nullptr);  // Not ready to reproduce
        }
    }
};

#endif // PREY_H
