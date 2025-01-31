#include "stdafx.h"
#include "app/app.h"
#include "Star.h"
#include <vector>

std::vector<Star*> stars;
const int MAX_STARS = 5;

void Init() {
    // Create initial stars at random positions
    for (int i = 0; i < MAX_STARS; i++) {
        float x = FRAND_RANGE(100.0f, APP_VIRTUAL_WIDTH - 100.0f);
        float y = FRAND_RANGE(100.0f, APP_VIRTUAL_HEIGHT - 100.0f);
        stars.push_back(new Star(x, y));
    }
}

void Update(float deltaTime) {
    // Update all stars
    for (auto star : stars) {
        star->Update(deltaTime);
    }

    // Handle input
    if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)) {
        // Cycle selected star's state
        if (!stars.empty()) {
            Star* selected = stars[0]; // For simplicity, always select first star
            StarState currentState = selected->GetState();
            selected->SetState(StarState((currentState + 1) % 4));
        }
    }
}

void Render() {
    // Draw all stars
    for (auto star : stars) {
        star->Draw();
    }

    // Draw instructions
    App::Print(10, 10, "Press A to cycle star state");
}

void Shutdown() {
    // Clean up
    for (auto star : stars) {
        delete star;
    }
    stars.clear();
}