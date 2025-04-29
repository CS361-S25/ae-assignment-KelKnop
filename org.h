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
    // Constructor with optional points and species (default: 0)
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0, int _species = 0)
        : points(_points), species(_species), random(_random) { }

    // Set the points of the organism
    virtual void SetPoints(double _in) { points = _in; }

    // Add to the organism's points
    virtual void AddPoints(double _in) { points += _in; }

    // Get the species ID of the organism
    virtual int GetSpecies() const { return species; }

    // Set the species ID of the organism
    virtual void SetSpecies(int _species) { species = _species; }

    // Get the current points
    virtual int GetPoints() const { return points; }

    // Placeholder method to process organism behavior
    virtual void Process() {
        std::cout << "Processing org" << std::endl;            // Debug message (can be removed)
        std::cout << "ORG POINTS ADDED" << std::endl;          // Debug message (can be removed)
    }

    // Placeholder method to process organism interactions
    virtual void Interact(Organism &other) {
        std::cout << "Interacting" << std::endl;               // Debug message (can be removed)
    }

    // Checks whether this organism should reproduce
    // Currently returns nullptr by default; override with specific logic
    virtual emp::Ptr<Organism> CheckReproduction() {
        return emp::Ptr<Organism>(nullptr);
    }
};

#endif // ORG_H
