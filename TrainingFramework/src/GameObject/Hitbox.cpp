#include "Hitbox.h"

Hitbox::Hitbox() {
};

Hitbox::~Hitbox() {
};

Hitbox::Hitbox(GLfloat hitbox_x, GLfloat hitbox_y, GLfloat c_hitbox_x, GLfloat c_hitbox_y)
{
	this->hitbox_x = hitbox_x;
	this->hitbox_y = hitbox_y;
	this->c_hitbox_x = c_hitbox_x;
	this->c_hitbox_y = c_hitbox_y;
}
void Hitbox::Update(GLfloat hitbox_x, GLfloat hitbox_y, GLfloat c_hitbox_x, GLfloat c_hitbox_y) {
	this->hitbox_x = hitbox_x;
	this->hitbox_y = hitbox_y;
	this->c_hitbox_x = c_hitbox_x;
	this->c_hitbox_y = c_hitbox_y;
};

void Hitbox::setHitbox_x(GLfloat hitbox_x) {
	//printf("%f", hitbox_x);
	this->hitbox_x = hitbox_x;
	//printf("%f", hitbox_x);
};
void Hitbox::setHitbox_y(GLfloat hitbox_y) {
	this->hitbox_y = hitbox_y;
};
void Hitbox::setCHitbox_x(GLfloat c_hitbox_x) {
	this->c_hitbox_x = c_hitbox_x;
};
void Hitbox::setCHitbox_y(GLfloat c_hitbox_y) {
	this->c_hitbox_y = c_hitbox_y;
};

GLfloat Hitbox::getHitbox_x() {
	return hitbox_x;
};
GLfloat Hitbox::getHitbox_y() {
	return hitbox_y;
};
GLfloat Hitbox::getCHitbox_x() {
	return c_hitbox_x;
};
GLfloat Hitbox::getCHitbox_y() {
	return c_hitbox_y;
};


