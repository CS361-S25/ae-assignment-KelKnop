#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

// Class representing an organism in a simulation
class Organism {
private:
    double points;                       // Score or energy points
    int species;                         // Species identifier (e.g., 0 = prey, 1 = predator)
    emp::Ptr<emp::Random> random;        // Pointer to random number generator

public:
    /**
     * Constructor to initialize an organism with energy points and species.
     * Defaults to 0 points and species 0 (prey).
     * 
     * @param _random Pointer to the random number generator.
     * @param _points Initial energy or score of the organism.
     * @param _species Species identifier (default: 0).
     */
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0, int _species = 0)
        : points(_points), species(_species), random(_random) { }

    /**
     * Sets the energy points of the organism.
     * 
     * @param _in New energy value.
     */
    virtual void SetPoints(double _in) { points = _in; }

    /**
     * Adds energy points to the organism's current points.
     * 
     * @param _in Amount of energy to add.
     */
    virtual void AddPoints(double _in) { points += _in; }

    /**
     * Gets the species ID of the organism.
     * 
     * @return Species ID (e.g., 0 for prey, 1 for predator).
     */
    virtual int GetSpecies() const { return species; }

    /**
     * Sets the species ID of the organism.
     * 
     * @param _species New species ID.
     */
    virtual void SetSpecies(int _species) { species = _species; }

    /**
     * Gets the current energy points of the organism.
     * 
     * @return Current energy points.
     */
    virtual int GetPoints() const { return points; }

    /**
     * Placeholder method for processing organism behavior.
     * To be overridden with specific logic for behavior (e.g., movement, reproduction).
     */
    virtual void Process() {
    }

    /**
     * Placeholder method for processing interactions between organisms.
     * To be overridden with specific interaction logic (e.g., predator-prey behavior).
     * 
     * @param other The other organism involved in the interaction.
     */
    virtual void Interact(Organism &other) {
    }

    /**
     * Checks whether the organism should reproduce.
     * Default behavior returns nullptr, to be overridden with specific reproduction logic.
     * 
     * @return A pointer to a new organism if reproduction occurs; nullptr otherwise.
     */
    virtual emp::Ptr<Organism> CheckReproduction() {
        return emp::Ptr<Organism>(nullptr);
    }
};

#endif // ORG_H
