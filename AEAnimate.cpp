#include "emp/math/Random.hpp"
#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "world.h"
#include "org.h"

emp::web::Document doc{"target"};

// AEAnimator: Manages the simulation loop and visualizes the predator-prey interaction
class AEAnimator : public emp::web::Animate {
    // Arena configuration
    const int num_h_boxes = 20;                    
    const int num_w_boxes = 20;                    
    const double RECT_SIDE = 10;                   
    const double width{num_w_boxes * RECT_SIDE};   
    const double height{num_h_boxes * RECT_SIDE};  

    emp::Random random{5};                         
    OrgWorld world{random};                        
    emp::web::Canvas canvas{width, height, "canvas"};  

public:
    /**
     * Constructor: Initializes the simulation interface, sets up the world grid, and populates
     * the environment with prey and predator organisms.
     */
    AEAnimator() {
        SetupUI();
        SetupWorld();
        AddInitialOrganisms();
    }

    /**
     * Called each animation frame: Clears canvas, moves organisms, updates world state, and redraws.
     */
    void DoFrame() override {
        canvas.Clear();
        MoveAllOrganisms();
        world.Update();
        DrawAllOrganisms();
    }

private:
    /**
     * Initializes the web-based UI elements (text, controls, canvas).
     */
    void SetupUI() {
        doc << "<h1>Predator-Prey Ecosystem Simulation</h1>";
        doc << "<p>Welcome to an interactive simulation that demonstrates the ecological dynamics between two species:</p>";
        doc << "<ul>"
                "<li><strong>Blue squares</strong> represent <strong>prey organisms</strong>.</li>"
                "<li><strong>Red squares</strong> represent <strong>predator organisms</strong>.</li>"
            "</ul>";
        doc << "<p>Each square on the grid represents a space where an organism can live.</p>";
        doc << "<ul>"
                "<li>Prey gain energy and reproduce when possible.</li>"
                "<li>Predators consume prey to regain energy.</li>"
            "</ul>";
        doc << "<p>Use the <strong>Start/Stop</strong> and <strong>Step</strong> buttons to control the simulation.</p>";
        doc << canvas << "<br>" << GetToggleButton("Toggle") << " " << GetStepButton("Step");
    }

    /**
     * Configures the simulation world structure and size.
     */
    void SetupWorld() {
        world.Resize(num_w_boxes, num_h_boxes);
        world.SetPopStruct_Grid(num_w_boxes, num_h_boxes);
    }

    /**
     * Adds initial prey and predator organisms to the world.
     */
    void AddInitialOrganisms() {
        for (int i = 0; i < 20; i++) {
            world.AddOrgAt(new preyOrganism(&random, 100.0), random.GetUInt(world.GetSize()));
        }
        world.AddOrgAt(new predatorOrganism(&random, 1000.0), random.GetUInt(world.GetSize()));
    }

    /**
     * Iterates through all cells and moves any organism present.
     */
    void MoveAllOrganisms() {
        for (size_t i = 0; i < world.GetSize(); ++i) {
            if (world.IsOccupied(i)) world.MoveOrganism(i);
        }
    }

    /**
     * Draws the entire organism grid on the canvas.
     */
    void DrawAllOrganisms() {
        int org_num = 0;
        for (int x = 0; x < num_w_boxes; x++) {
            for (int y = 0; y < num_h_boxes; y++) {
                DrawOrganismAt(org_num, x, y);
                org_num++;
            }
        }
    }

    /**
     * Draws a single organism (or empty cell) at the specified grid location.
     * 
     * @param index World index of organism
     * @param x X grid coordinate
     * @param y Y grid coordinate
     */
    void DrawOrganismAt(int index, int x, int y) {
        std::string color = "white";
        if (world.IsOccupied(index)) {
            color = (world.GetOrg(index).GetSpecies() == 1) ? "red" : "blue";
        }
        canvas.Rect(x * RECT_SIDE, y * RECT_SIDE, RECT_SIDE, RECT_SIDE, color, "black");
    }
};

// Instantiate and run simulation
AEAnimator animator;

int main() {
    animator.Step();     // Perform one simulation step initially
    animator.DoFrame();  // Render the first frame to display the starting state
}
