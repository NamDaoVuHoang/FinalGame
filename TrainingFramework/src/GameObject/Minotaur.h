#pragma once
#include "Character.h"
class Minotaur :
    public Character
{
public:
    Minotaur();
    ~Minotaur();

    void InitAttack();
    void InitAttackHitbox();
    void InitFlipAttackHitbox();
    void InitTaunt();
    void Init();
    void Update(GLfloat deltaTime, GLfloat c_x, GLfloat c_y);
    void Draw();
    void HandleKeyEvents(int key, bool bIsPressed);
    bool GetIs_Attacking();
    int GetCurrentAttackFrame();
    bool HasAttackHitbox();
    GLfloat* GetAttackHitbox();
    GLfloat* GetHitbox();
    void SetIsTakingDamge(bool is_TakingDamage);
    //GLfloat GetCCurrentWidth();
    //void UpdatePosition();
    bool is_Update = false;

protected:

    int current_health = 0;
    int current_health_bar = 3;
    std::shared_ptr<AnimationSprite> health_bar[4];
    GLfloat vertex[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    int chosen_attack = 0;
    int chosen_taunt = 0;
    int num_attacks = 0;
    int num_taunts = 0;
    float standing_time = 1.0f;
    bool is_Standing = true;
    bool is_Taunting = false;

    std::shared_ptr<AnimationSprite> m_list_attacking[4];
    std::shared_ptr<AnimationSprite> m_list_flip_attacking[4];
    std::shared_ptr<AnimationSprite> m_list_taunting[4];
    std::shared_ptr<AnimationSprite> m_list_flip_taunting[4];

};

