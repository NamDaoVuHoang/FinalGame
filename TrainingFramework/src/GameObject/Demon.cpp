#include "Demon.h"
#include "AnimationSprite.h"
#include "Hitbox.h"
using namespace std;

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Demon::Demon() {};
Demon::~Demon() {
	if (is_Fire) ResourceManagers::GetInstance()->PauseSound("Burn");
};


void Demon::InitAttackHitbox() {
	for (int i = 1; i < 4; i++) {
		m_fire->SetHitboxX(80.0f, i);
		m_fire->SetHitboxY(80.0f, i);
		m_fire->SetCHitboxX(45.0f, i);
		m_fire->SetCHitboxY(0.0f, i);
	}
};

void Demon::InitFlipAttackHitbox() {
	for (int i = 1; i < 4; i++) {
		m_flip_fire->SetHitboxX(80.0f, i);
		m_flip_fire->SetHitboxY(80.0f, i);
		m_flip_fire->SetCHitboxX(-45.0f, i);
		m_flip_fire->SetCHitboxY(0.0f, i);
	}
}


void Demon::Init() {
	//num_attacks = 3;
	//num_taunts = 2;
	run_speed = 150;
	//InitTaunt();
	is_FacingRight = false;
	c_current_width = 1300;
	c_current_height = 460;
	hitbox = std::make_shared<Hitbox>(c_current_width, c_current_height, 90.0f, 90.0f);
	//Animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderflip1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("demon-attack-no-breath");
	m_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 1, 8, 8, 0, (0.1f));
	m_attacking->Set2DPosition(c_current_width, c_current_height);
	m_attacking->SetSize(200.0f, 200.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("demon-standing");
	m_standing = std::make_shared<AnimationSprite>(model, shader, texture, 1, 6, 6, 0, (0.1f));
	m_standing->Set2DPosition(c_current_width, c_current_height + 30);
	m_standing->SetSize(140.0f, 140.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("breath");
	m_fire = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_fire->Set2DPosition(c_current_width, c_current_height + 20);
	m_fire->SetSize(100.0f, 100.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-death");
	m_dying = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_dying->Set2DPosition(c_current_width, c_current_height);
	m_dying->SetSize(150.0f, 150.0f);
	m_dying->SetCurrentFrames(1);


	//Animation flip
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	texture = ResourceManagers::GetInstance()->GetTexture("demon-attack-no-breath");
	m_flip_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 1, 8, 8, 0, (0.1f));
	m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
	m_flip_attacking->SetSize(200.0f, 200.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("demon-standing");

	m_flip_standing = std::make_shared<AnimationSprite>(model, shader, texture, 1, 6, 6, 0, (0.1f));
	m_flip_standing->Set2DPosition(c_current_width, c_current_height + 30);
	m_flip_standing->SetSize(140.0f, 140.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("breath");
	m_flip_fire = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_flip_fire->Set2DPosition(c_current_width, c_current_height + 20);
	m_flip_fire->SetSize(100.0f, 100.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-death");
	m_flip_dying = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_flip_dying->Set2DPosition(c_current_width, c_current_height);
	m_flip_dying->SetSize(150.0f, 150.0f);
	m_flip_dying->SetCurrentFrames(1);

	health = 2;
	max_health = 2;
	texture = ResourceManagers::GetInstance()->GetTexture("heart");
	for (int i = 0; i < max_health; i++) {
		health_bar[i] = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, 0.05f);
		health_bar[i]->Set2DPosition(screenWidth - 30.0f - 21.0f * i, 30.0f);
		health_bar[i]->SetSize(20, 20);
	}
	InitAttackHitbox();
	InitFlipAttackHitbox();
};
void Demon::Update(GLfloat deltaTime) {
	if (!is_Alive) {
		m_dying->UpdateDying(deltaTime);
		if (is_Fire) {
			ResourceManagers::GetInstance()->PauseSound("Burn");
		}
		return;
	}
	if (health == 0) {
		is_Alive = false;
		//m_dying->Update(deltaTime);
		return;
	}
	if (not_taking_damage_time > 0) not_taking_damage_time -= deltaTime;
	if (is_TakingDamage) taking_damage_time = taking_damage_time - deltaTime;
	if (taking_damage_time <= 0) {
		//health--;
		taking_damage_time = 0.3f;
		is_TakingDamage = false;
	}

	standing_time = max(0, standing_time - deltaTime);
	if (standing_time > 0) {
		return;
	}
	else {
		if (!is_Fire) {
			ResourceManagers::GetInstance()->PlaySound("Burn");
			is_Fire = true;
		}
		is_Standing = false;
		is_Attacking = true;
	}
	if (is_FacingRight) {
		//is_Attacking = true;
		GLfloat s = deltaTime * run_speed;
		c_current_width += s;
		if (c_current_width > screenWidth - 30) {
			is_Attacking = false;
			is_Standing = true;
			is_FacingRight = false;
			ResourceManagers::GetInstance()->PauseSound("Burn");
			is_Fire = false;
		}
		c_current_width = min(c_current_width, screenWidth - 30);
		//m_attacking->Set2DPosition(c_current_width, c_current_height);
		m_attacking->UpdateAttackingDemon(deltaTime);
		m_fire->UpdateFire(deltaTime);
	}
	else {
		//is_Attacking = true;
		GLfloat s = deltaTime * run_speed;
		c_current_width -= s;
		if (c_current_width < 30) {
			is_Attacking = false;
			is_Standing = true;
			is_FacingRight = true;
			ResourceManagers::GetInstance()->PauseSound("Burn");
			is_Fire = false;
		}
		c_current_width = max(c_current_width, 30);
		//m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
		m_flip_attacking->UpdateAttackingDemon(deltaTime);
		m_flip_fire->UpdateFire(deltaTime);
	}
};

void Demon::Draw() {
	if (!is_Alive) {
		if (is_FacingRight) {
			m_dying->Set2DPosition(c_current_width, c_current_height);
			m_dying->Draw();
		}
		else {
			m_flip_dying->Set2DPosition(c_current_width, c_current_height);
			m_flip_dying->Draw();
		}
	}
	else {
		if (is_FacingRight) {
			if (is_Attacking) {
				m_attacking->Set2DPosition(c_current_width, c_current_height);
				m_attacking->Draw();
				m_fire->Set2DPosition(c_current_width + 70, c_current_height + 55);
				m_fire->Draw();
			}
			else {
				m_standing->Set2DPosition(c_current_width, c_current_height + 30);
				m_standing->Draw();
			}
		}
		else {
			if (is_Attacking) {
				m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
				m_flip_attacking->Draw();
				m_flip_fire->Set2DPosition(c_current_width - 70, c_current_height + 55);
				m_flip_fire->Draw();
			}
			else {
				m_flip_standing->Set2DPosition(c_current_width, c_current_height + 30);
				m_flip_standing->Draw();
			}
		}
		if (is_Update) {
			for (int i = 0; i < max_health; i++) {
				health_bar[i]->Draw();
			}
		}
	}

};
void Demon::HandleKeyEvents(int key, bool bIsPressed) {
};

GLfloat* Demon::GetAttackHitbox() {
	int l = this->GetCurrentAttackFrame();
	//std::shared_ptr<GLfloat> vertex_hitbox[4];
	GLfloat x = 0;
	GLfloat y = 0;
	//printf("%f %f ", c_current_height, m_list_attacking[chosen_attack]->getCHitbox_y(l));
	if (is_FacingRight) {
		x = c_current_width + 40 + m_fire->getCHitbox_x(l);
		y = c_current_height + 55 + m_fire->getCHitbox_y(l);
		vertex[2] = m_fire->getHitbox_x(l);
		vertex[3] = m_fire->getHitbox_y(l);
	}
	else {
		x = c_current_width - 40 + m_flip_fire->getCHitbox_x(l);
		y = c_current_height + 55 +  m_flip_fire->getCHitbox_y(l);
		vertex[2] = m_flip_fire->getHitbox_x(l);
		vertex[3] = m_flip_fire->getHitbox_y(l);
	}
	vertex[0] = x;
	vertex[1] = y;
	//printf("%f %f\n", vertex[0], vertex[1]);
	//printf("%f %f ", c_current_width, c_current_height);

	return vertex;
}

GLfloat* Demon::GetHitbox() {
	hitbox->Update(c_current_width, c_current_width, hitbox->getCHitbox_x(), hitbox->getHitbox_y());
	//printf("YES");
	vertex[0] = c_current_width;
	vertex[1] = c_current_height;
	vertex[2] = hitbox->getCHitbox_x();
	vertex[3] = hitbox->getCHitbox_y();
	return vertex;
}

void Demon::SetIsTakingDamge(bool is_TakingDamage) {
	//printf("%s\n", this->is_TakingDamage ? "true" : "false");
	if (not_taking_damage_time <= 0) {
		current_health += 4;
		health_bar[current_health_bar]->SetCurrentFrames(current_health);
		//printf("YES");
		if (current_health == 4) {
			current_health = 0;
			current_health_bar--;
			health--;
		}
		not_taking_damage_time = 0.8f;
		this->is_TakingDamage = is_TakingDamage;
	}
};


bool Demon::GetIs_Attacking() {
	//printf("Here");
	return is_Attacking;
};

int Demon::GetCurrentAttackFrame() {
	if (is_FacingRight) return m_fire->GetCurrentFrame();
	else m_flip_fire->GetCurrentFrame();
}


bool Demon::HasAttackHitbox() {
	if (!this->GetIs_Attacking()) return false;
	//printf("%d\n", m_attacking->getHitbox_x(this->GetCurrentAttackFrame()));
	if (m_fire->getHitbox_x(this->GetCurrentAttackFrame()) > 0 ||
		m_fire->getHitbox_y(this->GetCurrentAttackFrame()) > 0) {
		return true;
	}
	return false;
}

