#include "Character.h"
#include "Hitbox.h"
#include "AnimationSprite.h"

Character::Character() {}
Character::~Character() {}

void Character::Init() {
};

void Character::Update() {
};

void Character::Draw(GLfloat deltatime) {
};

void Character::HandleKeyEvents(int key, bool bIsPressed) {
};

bool Character::Is_Alive() {
	return is_Alive;
}
GLfloat Character::GetCurrentX() {
	return c_current_width;
}

GLfloat Character::GetCurrentY() {
	return c_current_height;
}


void Character::SetCurrentX(GLfloat c_current_width) {
	this->c_current_width = c_current_width;
}

//bool Character::HasAttackHitbox() {