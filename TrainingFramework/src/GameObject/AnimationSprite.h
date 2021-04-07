#pragma once
#include "Sprite2D.h"

class Hitbox;

class AnimationSprite :
    public Sprite2D
{
public:
    AnimationSprite();
    AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,
        int numFrames, float frameTimes);
    AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture,
        int numColumns, int numFrames, int maxFrames, int currentRows, float frameTimes);
    ~AnimationSprite();
    void Draw();
    void Update(GLfloat deltatime);
    void UpdateStanding(GLfloat deltatime);
    void UpdateRunning(GLfloat deltatime,bool is_Running);
    void UpdateAttacking(GLfloat deltatime, bool*  is_Attacking);
    void UpdateBlocking(GLfloat deltatime, bool is_Blocking);
    void UpdateTaunting(GLfloat deltatime, bool* is_Taunting);
    void UpdateHealth(GLfloat deltatime);
    void UpdateFire(GLfloat deltatime);
    void UpdateAttackingDemon(GLfloat deltatime);
    void UpdateDying(GLfloat deltatime);

    void Set2DPosition(GLfloat x, GLfloat y) ;
    void Set2DPosition(Vector2 pos);
    void SetHitboxX(GLfloat hitbox_x, int i);
    void SetHitboxY(GLfloat hitbox_y, int i);
    void SetCHitboxX(GLfloat c_hitbox_x, int i);
    void SetCHitboxY(GLfloat c_hitbox_y, int i);
    GLfloat getHitbox_x(int i);
    GLfloat getHitbox_y(int i);
    GLfloat getCHitbox_x(int i);
    GLfloat getCHitbox_y(int i);
    void SetDamage(float damage);

    void SetCurrentFrames(int frame);
    int  GetCurrentFrame();
protected:

    std::shared_ptr<Hitbox> hitbox[11];

    float damage;
    int m_numRows;
    int m_numFrames;
    float m_currentTimes;
    float m_frameTimes;
    int m_currentFrames;
    int m_currentRows;
    int m_maxFrames;
};

