#pragma once
#include "GameManager/ResourceManagers.h"
using namespace std;

class Text;
class Hitbox;
class Sprite2D;
class Sprite3D;
class AnimationSprite;

class Character
{
public:
	Character();
	~Character();

	void Init();
	void Update();
	void Draw(GLfloat deltatime);
	void HandleKeyEvents(int key, bool bIsPressed);
	bool GetIs_Attacking();
	int GetCurrentAttackFrame(); 
	Hitbox GetHitbox();
	AnimationSprite GetAttackAnimation();
	GLfloat GetCurrentX();
	GLfloat GetCurrentY();
	void SetCurrentX(GLfloat c_current_width);
	bool Is_Alive();
protected:
	
	//bool is_Standing = false;
	
	bool is_Running = false;
	bool is_Attacking = false;
	bool is_FacingRight = true;
	bool is_Jumping = false;
	bool is_Falling = false;
	bool is_Alive = true;
	bool is_Blocking = false;
	bool is_TakingDamage = false;
	bool is_Dodging = false;


	int max_health = 0;
	int health = 0;
	GLfloat not_taking_damage_time = 0.0f;
	GLfloat taking_damage_time = 0.3f;
	GLfloat slide_wait_time = 0.5f;
	GLfloat slide_time = 0;
	GLfloat c_current_width = 20;
	GLfloat c_current_height = 520;
	GLfloat run_speed = 100;
	GLfloat slide_speed = 320;
	GLfloat jump_speed = 190;
	GLfloat rise_time = 0;
	GLfloat fall_time = 0;
	
	std::shared_ptr<Text> name;
	std::shared_ptr<Hitbox> hitbox;
	//std::shared_ptr<Text>  m_score;
	//std::shared_ptr<AnimationSprite> m_character;
	std::shared_ptr<AnimationSprite> m_running;
	std::shared_ptr<AnimationSprite> m_attacking;
	std::shared_ptr<AnimationSprite> m_standing;
	std::shared_ptr<AnimationSprite> m_falling;
	std::shared_ptr<AnimationSprite> m_jumping;
	std::shared_ptr<AnimationSprite> m_takingdamage;
	std::shared_ptr<AnimationSprite> m_dying;
	std::shared_ptr<AnimationSprite> m_blocking;

	std::shared_ptr<AnimationSprite> m_flip_running;
	std::shared_ptr<AnimationSprite> m_flip_attacking;
	std::shared_ptr<AnimationSprite> m_flip_standing;
	std::shared_ptr<AnimationSprite> m_flip_falling;
	std::shared_ptr<AnimationSprite> m_flip_jumping;
	std::shared_ptr<AnimationSprite> m_flip_takingdamage;
	std::shared_ptr<AnimationSprite> m_flip_dying;
	std::shared_ptr<AnimationSprite> m_flip_blocking;
};

