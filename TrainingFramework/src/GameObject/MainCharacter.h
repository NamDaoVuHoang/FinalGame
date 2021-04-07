#pragma once
#include "Character.h"
class MainCharacter :
    public Character
{
public:
    MainCharacter();
    ~MainCharacter();

    bool is_Playing_attack = false;

    GLfloat travel = 0.0f;
    bool is_LockScreen = false;
    int current_health = 0;
    int current_health_bar = 2;
    std::shared_ptr<AnimationSprite> health_bar[3];
    GLfloat vertex[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    void Init();
    void Update(GLfloat deltaTime);
    void Draw();
    void HandleKeyEvents(int key, bool bIsPressed);
    bool GetIs_Attacking();
    int GetCurrentAttackFrame();
    bool HasAttackHitbox();
    GLfloat* GetAttackHitbox();
    GLfloat* GetHitbox();
    void SetIsTakingDamge(bool is_TakingDamage);
    void SetIsLockScreen(bool is_LockScreen);
    GLfloat GetTravel();
};

