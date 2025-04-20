#ifndef WORLD_H
#define WORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "org.h"

class OrgWorld : public emp::World<Organism> {

    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;
    int world_width = 10; // <- Set this to your actual grid width

public:

    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {
    }

    void Update() {
        emp::World<Organism>::Update();
        std::cout << "Updating!" << std::endl;

        emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
        for (int i : schedule) {
            if (!IsOccupied(i)) continue;
            pop[i]->Process(5);

            // === New Neighbor Interaction ===
            int row = i / world_width;
            int col = i % world_width;
            std::vector<int> neighbor_indices;

            if (row > 0) neighbor_indices.push_back(i - world_width); // up
            if (row < (GetSize() / world_width) - 1) neighbor_indices.push_back(i + world_width); // down
            if (col > 0) neighbor_indices.push_back(i - 1); // left
            if (col < world_width - 1) neighbor_indices.push_back(i + 1); // right
            if (row > 0 && col > 0) neighbor_indices.push_back(i - world_width - 1); // up-left
            if (row > 0 && col < world_width - 1) neighbor_indices.push_back(i - world_width + 1); // up-right
            if (row < (GetSize() / world_width) - 1 && col > 0) neighbor_indices.push_back(i + world_width - 1); // down-left
            if (row < (GetSize() / world_width) - 1 && col < world_width - 1) neighbor_indices.push_back(i + world_width + 1); // down-right


            for (int j : neighbor_indices) {
                if (IsOccupied(j)) {
                    pop[i]->Interact(*pop[j]);
                }
            }

            // Death logic
            if (pop[i]->GetPoints() <= 0) {
                std::cout << "Organism at position " << i << " has died." << std::endl;
                pop[i] = nullptr;
                continue;
            }
        }

        for (size_t i = 0; i < GetSize(); ++i) {
        if (IsOccupied(i) && pop[i]->GetPoints() <= 0) {
            std::cout << "Cleanup: Organism at position " << i << " has died." << std::endl;
            pop[i] = nullptr;
        }
    }

        emp::vector<size_t> schedule2 = emp::GetPermutation(random, GetSize());
        for (int i : schedule2) {
            if (!IsOccupied(i)) continue;
            emp::Ptr<Organism> offspring = pop[i]->CheckReproduction();
            if (offspring) {
                DoBirth(*offspring, i);
                std::cout << "Birth!" << std::endl;
            }
        }
    }

    emp::Ptr<Organism> ExtractOrganism(size_t pos) {
        if (!IsOccupied(pos)) return nullptr;
        emp::Ptr<Organism> org = pop[pos];
        pop[pos] = nullptr;
        return org;
    }

    void MoveOrganism(size_t pos) {
        if (!IsOccupied(pos)) return;

        emp::Ptr<Organism> org = ExtractOrganism(pos);
        if (org == nullptr) return;

        emp::WorldPosition new_pos = GetRandomNeighborPos(pos);
        if (IsOccupied(new_pos)) {
            AddOrgAt(org, pos);
            return;
        }

        AddOrgAt(org, new_pos);
    }

};

#endif
