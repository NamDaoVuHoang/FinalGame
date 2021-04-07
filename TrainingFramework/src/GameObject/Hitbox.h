#pragma once
#include "GameManager/ResourceManagers.h"
using namespace std;
class Hitbox
{
public:
	Hitbox();
	Hitbox(GLfloat hitbox_x, GLfloat hitbox_y, GLfloat c_hitbox_x, GLfloat c_hitbox_y);
	~Hitbox();

	void setHitbox_x(GLfloat hitbox_x);
	void setHitbox_y(GLfloat hitbox_y);
	void setCHitbox_x(GLfloat c_hitbox_x);
	void setCHitbox_y(GLfloat c_hitbox_y);

	GLfloat getHitbox_x();
	GLfloat getHitbox_y();
	GLfloat getCHitbox_x();
	GLfloat getCHitbox_y();

	void Update(GLfloat hitbox_x, GLfloat hitbox_y, GLfloat c_hitbox_x, GLfloat c_hitbox_y);

private:
	GLfloat hitbox_x = 0.0f;
	GLfloat hitbox_y = 0.0f;
	GLfloat c_hitbox_x = 0.0f;
	GLfloat c_hitbox_y = 0.0f;
};

