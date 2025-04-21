#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "world.h"
#include "org.h"

emp::web::Document doc{"target"};

// AEAnimator: Manages the simulation loop and visualizes the predator-prey interaction
class AEAnimator : public emp::web::Animate {

    // Arena configuration
    const int num_h_boxes = 20;                    // Grid height
    const int num_w_boxes = 20;                    // Grid width
    const double RECT_SIDE = 10;                   // Pixel size of each grid cell
    const double width{num_w_boxes * RECT_SIDE};   // Canvas width
    const double height{num_h_boxes * RECT_SIDE};  // Canvas height

    emp::Random random{5};                         // RNG (with fixed seed for consistency)
    OrgWorld world{random};                        // World simulation space
    emp::web::Canvas canvas{width, height, "canvas"};  // Drawing canvas

public:
    AEAnimator() {
        // ==== User Interface Setup ====

        doc << "<h1>Predator-Prey Ecosystem Simulation</h1>";

        doc << "<p>Welcome to an interactive simulation that demonstrates the ecological dynamics between two species:</p>";
        doc << "<ul>"
                "<li><strong>Blue squares</strong> represent <strong>prey organisms</strong>. They passively gain energy over time and reproduce once they’ve stored enough energy.</li>"
                "<li><strong>Red squares</strong> represent <strong>predator organisms</strong>. They lose energy over time unless they find and consume prey.</li>"
            "</ul>";

        doc << "<p>Each square on the grid represents a space where an organism can live. The simulation runs in discrete time steps. In each step:</p>";
        doc << "<ul>"
                "<li>Prey organisms gain energy and may reproduce if they reach a certain threshold.</li>"
                "<li>Predators lose energy unless they move to a cell occupied by prey, in which case they consume the prey to regain energy.</li>"
                "<li>If predators reach enough energy, they can reproduce as well.</li>"
            "</ul>";

        doc << "<p>Use the <strong>Start/Stop</strong> button to run or pause the simulation, and the <strong>Step</strong> button to advance it one frame at a time. Watch how predator and prey populations change over time!</p>";

        // Attach canvas and controls
        doc << canvas;
        doc << "<br>";
        doc << GetToggleButton("Toggle") << " ";
        doc << GetStepButton("Step");

        // ==== Simulation World Setup ====

        world.Resize(num_w_boxes, num_h_boxes);              // Resize world to grid dimensions
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);   // Use grid-based spatial structure

        // Add 20 prey organisms (blue)
        for (int i = 0; i < 20; i++) {
            world.AddOrgAt(new preyOrganism(&random, 100.0), random.GetUInt(world.GetSize()));
        }

        // Add 1 predator organism (red)
        world.AddOrgAt(new predatorOrganism(&random, 1000.0), random.GetUInt(world.GetSize()));
    }

    // Called automatically on each frame when animation is active
    void DoFrame() override {
        canvas.Clear();  // Clear previous drawing

        // Move each organism (if cell is occupied)
        for (size_t i = 0; i < world.GetSize(); ++i) {
            if (world.IsOccupied(i)) {
                world.MoveOrganism(i);
            }
        }

        // Update logic for all organisms (reproduction, energy, etc.)
        world.Update();

        // === Drawing organisms on the canvas ===
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                if (world.IsOccupied(org_num)) {
                    // Red for predator, Blue for prey
                    std::string color = (world.GetOrg(org_num).GetSpecies() == 1) ? "red" : "blue";
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, color, "black");
                } else {
                    // White for empty space
                    canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, "white", "black");
                }
                org_num++;
            }
        }
    }
};

// Instantiate and run simulation
AEAnimator animator;

int main() {
    animator.Step();     // Perform one simulation step initially
    animator.DoFrame();  // Render the first frame to display the starting state
}
