#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include "app/app.h"
#include "Star.h"
#include <vector>

std::vector<Star*> stars;
int selectedStarIndex = 0;

// Function to create a star at a specific position
void CreateStar(float x, float y, StarState state = BIRTH) {
    Star* newStar = new Star(x, y, state);
    stars.push_back(newStar);
}

// Initialize the game
void Init() {
    // Create one star of each type to start with
    CreateStar(200.0f, 200.0f, BIRTH);
    CreateStar(400.0f, 200.0f, GLOW);
    CreateStar(600.0f, 200.0f, DEATH);
    CreateStar(800.0f, 200.0f, REBIRTH);
}

// Update game state
void Update(float deltaTime) {
    // Update all stars
    for (auto star : stars) {
        star->Update(deltaTime);
    }

    // Handle input for creating new stars
    if (App::IsKeyPressed('A')) {
        float mouseX, mouseY;
        App::GetMousePos(mouseX, mouseY);

        // Convert from normalized coordinates to virtual coordinates
#if APP_USE_VIRTUAL_RES
        mouseX = (mouseX + 1.0f) * APP_VIRTUAL_WIDTH / 2.0f;
        mouseY = (mouseY + 1.0f) * APP_VIRTUAL_HEIGHT / 2.0f;
#endif

        // Create a new star at mouse position
        CreateStar(mouseX, mouseY);
    }

    // Cycle through star states with B button
    if (App::IsKeyPressed('B') && !stars.empty()) {
        if (++selectedStarIndex >= static_cast<int>(stars.size())) {
            selectedStarIndex = 0;
        }

        // Cycle the selected star's state
        Star* selected = stars[selectedStarIndex];
        StarState currentState = selected->GetState();
        selected->SetState(StarState((currentState + 1) % 4));
    }

    // Clear all stars with X button
    if (App::IsKeyPressed('X')) {
        for (auto star : stars) {
            delete star;
        }
        stars.clear();
        selectedStarIndex = 0;
    }
}


// Render the game
void Render() {
    // Draw all stars
    for (auto star : stars) {
        star->Draw();
    }

    // Draw instructions
    App::Print(100, 700, "StarWeaver Game", 1.0f, 1.0f, 1.0f);
    App::Print(100, 670, "Press A to create a star at mouse position", 1.0f, 1.0f, 1.0f);
    App::Print(100, 640, "Press B to cycle selected star's state", 1.0f, 1.0f, 1.0f);
    App::Print(100, 610, "Press X to clear all stars", 1.0f, 1.0f, 1.0f);

    // Display star count and states
    char buffer[100];
    sprintf(buffer, "Stars: %d", (int)stars.size());
    App::Print(100, 580, buffer, 1.0f, 1.0f, 1.0f);

    // Display state names
    App::Print(200, 150, "BIRTH", 0.2f, 0.4f, 1.0f);
    App::Print(400, 150, "GLOW", 1.0f, 1.0f, 0.2f);
    App::Print(600, 150, "DEATH", 1.0f, 0.2f, 0.2f);
    App::Print(800, 150, "REBIRTH", 1.0f, 1.0f, 1.0f);
}

// Clean up
void Shutdown() {
    for (auto star : stars) {
        delete star;
    }
    stars.clear();
}