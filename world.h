#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "org.h"
#include "predator.h"
#include "prey.h"

// OrgWorld: Manages simulation of predator-prey dynamics
class OrgWorld : public emp::World<Organism> {
private:
    emp::Random &random;               // Reference to random number generator
    emp::Ptr<emp::Random> random_ptr;  // Pointer used by organisms

    /**
     * Handles organism interactions.
     * Each organism interacts with its neighbors.
     */
    void RunInteractionPhase() {
        auto schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule) {
            if (!IsOccupied(i)) continue;
            for (size_t n : GetValidNeighborOrgIDs(i)) {
                pop[i]->Interact(*pop[n]);
            }
        }
    }

    /**
     * Removes organisms with negative energy.
     * Simulates death or removal from the environment.
     */
    void RunCullingPhase() {
        for (size_t i = 0; i < GetSize(); ++i) {
            if (IsOccupied(i) && GetOrg(i).GetPoints() < 0) {
                RemoveOrgAt(i);
                pop[i] = nullptr;
            }
        }
    }

    /**
     * Processes all organisms.
     * Called once per update to apply internal changes.
     */
    void RunProcessingPhase() {
        auto schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule) {
            if (!IsOccupied(i)) continue;
            pop[i]->Process();
        }
    }

    /**
     * Handles reproduction for organisms with sufficient energy.
     * Places offspring in a random adjacent cell.
     */
    void RunReproductionPhase() {
        auto schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule) {
            if (!IsOccupied(i)) continue;
            auto offspring = pop[i]->CheckReproduction();
            if (offspring) {
                AddOrgAt(offspring, GetRandomNeighborPos(i));
            }
        }
    }

public:
    /**
     * Constructor for OrgWorld.
     * Initializes base world and RNG pointer.
     */
    OrgWorld(emp::Random &_random)
        : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    /// Default destructor
    ~OrgWorld() = default;

    /**
     * Executes one full simulation update cycle.
     * Includes interaction, culling, processing, and reproduction.
     */
    void Update() {
        emp::World<Organism>::Update();
        RunInteractionPhase();
        RunCullingPhase();
        RunProcessingPhase();
        RunReproductionPhase();
    }

    /**
     * Removes and returns the organism at a given position.
     * Does not delete the organism object.
     * 
     * @param pos Position in the world grid.
     * @return Pointer to organism or nullptr if position is empty.
     */
    emp::Ptr<Organism> ExtractOrganism(size_t pos) {
        if (!IsOccupied(pos)) return nullptr;
        auto org = pop[pos];
        pop[pos] = nullptr;
        return org;
    }

    /**
     * Moves an organism to a random neighboring position.
     * If neighbor is occupied, the organism stays in place.
     * 
     * @param pos Position of the organism to move.
     */
    void MoveOrganism(size_t pos) {
        if (!IsOccupied(pos)) return;
        auto org = ExtractOrganism(pos);
        if (!org) return;
        auto new_pos = GetRandomNeighborPos(pos);
        if (IsOccupied(new_pos)) {
            AddOrgAt(org, pos);  // Return to original spot
        } else {
            AddOrgAt(org, new_pos);
        }
    }
};

#endif // WORLD_H
