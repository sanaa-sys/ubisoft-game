#include "stdafx.h"
#include "Star.h"
#include "app/app.h"
#include <math.h>

const float Star::STATE_DURATION = 5.0f;
const float Star::BIRTH_SCALE_RATE = 0.2f;
const float Star::DEATH_SCALE_RATE = 0.3f;

Star::Star(float x, float y, StarState initialState) :
    m_currentState(initialState),
    m_stateTimer(0.0f),
    m_scale(0.1f),
    m_brightness(0.2f)
{
    // Assuming we have a star sprite sheet with 4 animations for each state
    m_sprite = App::CreateSprite(".\\TestData\\Test.bmp", 4, 4);
    m_sprite->SetPosition(x, y);
    m_sprite->SetScale(m_scale);

    // Create animations for each state
    float speed = 1.0f / 8.0f;
    m_sprite->CreateAnimation(BIRTH, speed, { 0 });
    m_sprite->CreateAnimation(GLOW, speed, { 1 });
    m_sprite->CreateAnimation(DEATH, speed, { 2 });
    m_sprite->CreateAnimation(REBIRTH, speed, { 3 });

    m_sprite->SetAnimation(initialState);
}

Star::~Star() {
    delete m_sprite;
}

void Star::Update(float deltaTime) {
    m_stateTimer += deltaTime;

    switch (m_currentState) {
    case BIRTH: UpdateBirth(deltaTime); break;
    case GLOW: UpdateGlow(deltaTime); break;
    case DEATH: UpdateDeath(deltaTime); break;
    case REBIRTH: UpdateRebirth(deltaTime); break;
    }

    m_sprite->Update(deltaTime);
}

void Star::UpdateBirth(float deltaTime) {
    m_scale += BIRTH_SCALE_RATE * deltaTime;
    m_brightness += 0.1f * deltaTime;
    m_sprite->SetScale(m_scale);

    if (m_stateTimer >= STATE_DURATION) {
        SetState(GLOW);
    }
}

void Star::UpdateGlow(float deltaTime) {
    // Pulsating effect
    m_brightness = 0.8f + 0.2f * sinf(m_stateTimer * 2.0f);

    if (m_stateTimer >= STATE_DURATION) {
        SetState(DEATH);
    }
}

void Star::UpdateDeath(float deltaTime) {
    m_scale -= DEATH_SCALE_RATE * deltaTime;
    m_brightness -= 0.1f * deltaTime;
    m_sprite->SetScale(m_scale);

    if (m_scale <= 0.1f) {
        SetState(REBIRTH);
    }
}

void Star::UpdateRebirth(float deltaTime) {
    m_scale += BIRTH_SCALE_RATE * deltaTime;
    m_brightness += 0.15f * deltaTime;
    m_sprite->SetScale(m_scale);

    if (m_stateTimer >= STATE_DURATION) {
        SetState(GLOW);
    }
}

void Star::Draw() {
    m_sprite->SetColor(m_brightness, m_brightness, m_brightness);
    m_sprite->Draw();
}

void Star::SetState(StarState newState) {
    m_currentState = newState;
    m_stateTimer = 0.0f;
    m_sprite->SetAnimation(newState);
}

void Star::GetPosition(float& x, float& y) const {
    m_sprite->GetPosition(x, y);
}

void Star::SetPosition(float x, float y) {
    m_sprite->SetPosition(x, y);
}
