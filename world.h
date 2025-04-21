#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "org.h"
#include "predator.h"
#include "prey.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

    void Update() {
        emp::World<Organism>::Update();
        std::cout << "Updating!" << std::endl;

        emp::vector<size_t> interaction_schedule = emp::GetPermutation(random, GetSize());
        for (int i : interaction_schedule) {
            if (!IsOccupied(i)) continue;

            // Get IDs of occupied neighbors
            emp::vector<size_t> neighbors = GetValidNeighborOrgIDs(i);
            for (size_t neighbor_id : neighbors) {
                pop[i]->Interact(*pop[neighbor_id]);
            }
        }

        // Culling: remove dead prey probably doesn't need a schedule
        for (size_t i = 0; i < GetSize(); ++i) {
            if (IsOccupied(i) && GetOrg(i).GetPoints() < 0) {
                RemoveOrgAt(i);
                pop[i] = nullptr; // Clear the pointer
            }
        }

        emp::vector<size_t> process_schedule = emp::GetPermutation(random, GetSize());
        for (int i : process_schedule) {
            if (!IsOccupied(i)) continue;
            if (pop[i]->GetSpecies() == 0) {
                pop[i]->Process(15); // Species 0 (prey)
            } else if (pop[i]->GetSpecies() == 1) {
                pop[i]->Process(-30); // Species 1 (predator)
            }
        }

        emp::vector<size_t> reproduce_schedule = emp::GetPermutation(random, GetSize());
        for (int i : reproduce_schedule) {
            if (!IsOccupied(i)) continue;
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring) {
                DoBirth(*offspring, i);
                std::cout << "Birth!" << std::endl;
            }
        }
    }

    // New method: ExtractOrganism
    emp::Ptr<Organism> ExtractOrganism(size_t pos) {
        if (!IsOccupied(pos)) return nullptr;
        emp::Ptr<Organism> org = pop[pos];
        pop[pos] = nullptr; // remove from population
        return org;
    }

    void MoveOrganism(size_t pos) {
    if (!IsOccupied(pos)) return; // nothing to move!

    // Step 1: Extract the organism
    emp::Ptr<Organism> org = ExtractOrganism(pos);
    if (org == nullptr) return;

    // Step 2: Pick a neighboring position
    emp::WorldPosition new_pos = GetRandomNeighborPos(pos);

    // Step 3: Optionally check if it's occupied
    if (IsOccupied(new_pos)) {
        // If you want to skip movement into occupied spaces
        // AddOrgAt will overwrite if you don't check!
        AddOrgAt(org, pos); // put it back in original spot
        return;
    }

    // Step 4: Place it in the new position
    AddOrgAt(org, new_pos);
}

};

#endif
