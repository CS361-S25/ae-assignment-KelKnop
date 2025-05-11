#ifndef PREDATOR_H
#define PREDATOR_H

#include "org.h"  // Include the base Organism class

// PredatorOrganism: Represents the predator species (Species 1)
class predatorOrganism : public Organism {
public:
    /**
     * Constructor for the predator organism.
     * Sets the species to 1 (predator) and optionally initializes energy points.
     * 
     * @param _random Pointer to random number generator.
     * @param _points Initial energy points (default: 0).
     */
    predatorOrganism(emp::Ptr<emp::Random> _random, double _points = 0.0)
        : Organism(_random, _points) {
        SetSpecies(1);  // Species 1 = predator
    }

    /**
     * Processes the predator's behavior each update.
     * Predators lose energy over time to simulate the cost of movement or hunting.
     */
    void Process() override {
        this->AddPoints(-30);  // Predators lose 30 points per update
    }

    /**
     * Interacts with another organism (prey).
     * The predator gains energy from the prey and marks the prey for removal.
     * 
     * @param other The other organism involved in the interaction (typically prey).
     */
    void Interact(Organism &other) override {
        std::cout << "Predator eating prey..." << std::endl;

        this->AddPoints(other.GetPoints());  // Gain points from prey
        other.SetPoints(-1);  // Mark prey for removal
    }

    /**
     * Checks if the predator is ready to reproduce.
     * If the predator has enough energy, it reproduces and creates an offspring.
     * 
     * @return A new predator organism if ready to reproduce, or nullptr if not.
     */
    emp::Ptr<Organism> CheckReproduction() override {
        if (this->GetPoints() >= 8000) {
            std::cout << "Predator: Reproducing" << std::endl;

            // Create offspring with 100 points, subtract cost from parent
            emp::Ptr<predatorOrganism> offspring = emp::NewPtr<predatorOrganism>(*this);
            offspring->SetPoints(7500);  // Set offspring's energy
            this->AddPoints(-8000);      // Deduct energy from parent
            return offspring;            // Return new offspring
        } else {
            return emp::Ptr<Organism>(nullptr);  // Not ready to reproduce
        }
    }
};

#endif // PREDATOR_H
