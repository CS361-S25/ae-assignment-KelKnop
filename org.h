#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

class Organism {
    private:
        double points;
        int species;
        emp::Ptr<emp::Random> random;

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points = 0.0, int _species = 0)
    : points(_points), species(_species), random(_random) {;}


    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}
    int GetSpecies() const { return species; }
    void SetSpecies(int _species) { species = _species; }
    int GetPoints() const { return points; }

    void Process(int points) {
        std::cout << "Processing" << std::endl; 
        this->AddPoints(points);
    }

    // This method can be overridden by subclasses (like Predator or Prey)
    virtual void Interact(Organism &other) {
        // Default behavior, maybe just nothing
    }

    emp::Ptr<Organism> CheckReproduction (){
        if (species == 1) {
            if (points >= 1000) {
                std::cout << "Species 0 Reproducing" << std::endl;
                emp::Ptr<Organism> offspring = new Organism(*this);  // Create offspring of the same type
                offspring->SetPoints(0);
                this->AddPoints(-1000);
                offspring->SetSpecies(species);  // Set species for the offspring
                return offspring;
            } else {
                std::cout << "Species 1: Not enough points to reproduce" << std::endl;
                return emp::Ptr<Organism>(nullptr);  // Return null pointer if not enough points
            }
        }

        else if (species == 2) {
            if (points >= 1000) {
                std::cout << "Species 2 Reproducing" << std::endl;
                emp::Ptr<Organism> offspring = new Organism(*this);  // Create offspring of the same type
                offspring->SetPoints(0);
                this->AddPoints(-1000);  // Different points cost for species 2
                offspring->SetSpecies(species);  // Set species for the offspring
                return offspring;
            } else {
                std::cout << "Species 1: Not enough points to reproduce" << std::endl;
                return emp::Ptr<Organism>(nullptr);  // Return null pointer if not enough points
            }
        }
        // Default return to make the compiler happy (shouldn't be needed with correct logic)
        return emp::Ptr<Organism>(nullptr);
    }
};

#endif
