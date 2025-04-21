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
        std::cout << "Processing" << std::endl; //feel free to get rid of this
        this->AddPoints(points);
    }

    void Interact(Organism &other) {
        std::cout << "Interacting" << std::endl; //feel free to get rid of this
        if (species == 0 && other.GetSpecies() == 1) {
            // Species 0 (prey) interacts with Species 1 (predator)
            std::cout << "Species 0 interacting with Species 1" << std::endl;
            this->AddPoints(0); 
            other.AddPoints(0); 
        } else if (species == 1 && other.GetSpecies() == 0) {
            // Species 1 (predator) interacts with Species 0 (prey)
            std::cout << "Species 1 interacting with Species 0" << std::endl;
            this->AddPoints(other.GetPoints());
            other.SetPoints(-1);
        }
        
    } 

    // Updated CheckReproduction method with species-specific logic
    virtual emp::Ptr<Organism> CheckReproduction (){
        // Logic for species 0 prey
        if (species == 0) {
            if (points >= 120) {
                std::cout << "Species 0 Reproducing" << std::endl;
                emp::Ptr<Organism> offspring = new Organism(*this);  // Create offspring of the same type
                offspring->SetPoints(0);
                this->AddPoints(-120);
                offspring->SetSpecies(species);  // Set species for the offspring
                return offspring;
            } else {
                std::cout << "Species 0: Not enough points to reproduce" << std::endl;
                return emp::Ptr<Organism>(nullptr);  // Return null pointer if not enough points
            }
        }

        // Logic for species 1 predator
        else if (species == 1) {
            if (points >= 10000) {
                std::cout << "Species 1 Reproducing" << std::endl;
                emp::Ptr<Organism> offspring = new Organism(*this);  // Create offspring of the same type
                offspring->SetPoints(0);
                this->AddPoints(-10000);  // Different points cost for species 1
                offspring->SetSpecies(species);  // Set species for the offspring
                return offspring;
            } else {
                std::cout << "Species 1: Not enough points to reproduce" << std::endl;
                
            }
        }

        // Default return to make the compiler happy (shouldn't be needed with correct logic)
        return emp::Ptr<Organism>(nullptr);
    }
};

#endif
