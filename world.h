#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "org.h"
#include "predator.h"
#include "prey.h"

// A world to manage and simulate interactions between Organisms
class OrgWorld : public emp::World<Organism> {
private:
    emp::Random &random;                      // Reference to RNG
    emp::Ptr<emp::Random> random_ptr;         // Pointer to RNG for use by organisms

public:
    // Constructor initializes world and sets up RNG pointer
    OrgWorld(emp::Random &_random)
        : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    // Destructor
    ~OrgWorld() { }

    // Main update loop for the simulation
    void Update() {
        emp::World<Organism>::Update();

        // --- INTERACTION PHASE ---
        emp::vector<size_t> interaction_schedule = emp::GetPermutation(random, GetSize());
        for (int i : interaction_schedule) {
            if (!IsOccupied(i)) continue;

            emp::vector<size_t> neighbors = GetValidNeighborOrgIDs(i);
            for (size_t neighbor_id : neighbors) {
                pop[i]->Interact(*pop[neighbor_id]);
            }
        }

        // --- CULLING PHASE ---
        // Remove organisms with negative points (e.g., prey that were eaten)
        for (size_t i = 0; i < GetSize(); ++i) {
            if (IsOccupied(i) && GetOrg(i).GetPoints() < 0) {
                RemoveOrgAt(i);
                pop[i] = nullptr;
            }
        }

        // --- PROCESSING PHASE ---
        // Let each organism perform any internal updates
        emp::vector<size_t> process_schedule = emp::GetPermutation(random, GetSize());
        for (int i : process_schedule) {
            if (!IsOccupied(i)) continue;
            pop[i]->Process();
        }

        // --- REPRODUCTION PHASE ---
        // Check each organism for reproduction and add offspring if needed
        emp::vector<size_t> reproduce_schedule = emp::GetPermutation(random, GetSize());
        for (int i : reproduce_schedule) {
            if (!IsOccupied(i)) continue;

            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring) {
                emp::WorldPosition offspring_pos = GetRandomNeighborPos(i);
                AddOrgAt(offspring, offspring_pos);
            }
        }
    }

    // Extract an organism from the world without deleting it
    emp::Ptr<Organism> ExtractOrganism(size_t pos) {
        if (!IsOccupied(pos)) return nullptr;
        emp::Ptr<Organism> org = pop[pos];
        pop[pos] = nullptr;
        return org;
    }

    // Move an organism to a neighboring position
    void MoveOrganism(size_t pos) {
        if (!IsOccupied(pos)) return;  // No organism to move

        // Step 1: Extract the organism
        emp::Ptr<Organism> org = ExtractOrganism(pos);
        if (org == nullptr) return;

        // Step 2: Choose a random neighboring position
        emp::WorldPosition new_pos = GetRandomNeighborPos(pos);

        // Step 3: Skip if neighbor is occupied (optional logic)
        if (IsOccupied(new_pos)) {
            AddOrgAt(org, pos);  // Return organism to original position
            return;
        }

        // Step 4: Move organism to new position
        AddOrgAt(org, new_pos);
    }
};

#endif // WORLD_H
