# Predator-Prey Simulation

## Organism Species

This simulation models an ecosystem with **two species of organisms** interacting on a grid:

### 1. Prey (`preyOrganism`)
- **Species ID:** 0
- **Color on Grid:** Blue
- **Behavior:**
  - Gains +15 points every time step.
  - Reproduces when it reaches **180 points**, creating a new prey organism with 30 points and subtracting 180 points from the parent.
- **Strategy:** Grows and reproduces rapidly to populate the grid, serving as a food source for predators.

### 2. Predator (`predatorOrganism`)
- **Species ID:** 1
- **Color on Grid:** Red
- **Behavior:**
  - Loses -30 points every time step (simulates energy expenditure).
  - When it interacts with a prey organism, it **gains the prey's points** and sets the prey's points to -1 (effectively killing it).
  - Reproduces when it reaches **8000 points**, creating a new predator with 7500 points and subtracting 8000 points from the parent.
- **Strategy:** Hunts prey to maintain energy levels and reproduce.

## Interaction

- Predators consume nearby prey.
- Prey move and reproduce quickly, but can be eliminated by predators through interaction.
- This dynamic creates a balance (or imbalance) of population over time, simulating a simple predator-prey ecosystem.

## Visual Representation

- The world is displayed on a grid using a web canvas.
- **Red squares** represent predators.
- **Blue squares** represent prey.
- **White squares** are empty cells.

## Summary

This simulation demonstrates basic ecological principles such as:
- Resource consumption
- Population growth and decline
- Reproduction thresholds
- Species interaction and survival

