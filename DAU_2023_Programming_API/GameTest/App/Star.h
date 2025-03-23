#pragma once
#include "app/SimpleSprite.h"

enum StarState {
    BIRTH,
    GLOW,
    DEATH,
    REBIRTH
};

class Star {
public:
    Star(float x, float y, StarState initialState); // Constructor with three arguments
    ~Star();

    void Update(float deltaTime);
    void Draw();
    void SetState(StarState newState);
    StarState GetState() const { return m_currentState; }
    void GetPosition(float& x, float& y) const;
    void SetPosition(float x, float y);

private:
    CSimpleSprite* m_sprite;
    StarState m_currentState;
    float m_stateTimer;
    float m_scale;
    float m_brightness;

    static const float STATE_DURATION;
    static const float BIRTH_SCALE_RATE;
    static const float DEATH_SCALE_RATE;

    void UpdateBirth(float deltaTime);
    void UpdateGlow(float deltaTime);
    void UpdateDeath(float deltaTime);
    void UpdateRebirth(float deltaTime);
};
