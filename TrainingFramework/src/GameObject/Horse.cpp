#include "Horse.h"
#include "AnimationSprite.h"
#include "Hitbox.h"
using namespace std;

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


Horse::Horse() {};
Horse::~Horse() {
	if (is_Galloping) ResourceManagers::GetInstance()->PauseSound("Gallop");
};


void Horse::InitAttackHitbox() {
	for (int i = 0; i < 4; i++) {
		m_attacking->SetHitboxX(70.0f, i);
		m_attacking->SetHitboxY(70.0f, i);
		m_attacking->SetCHitboxX(0.0f, i);
		m_attacking->SetCHitboxY(0.0f, i);
	}
};

void Horse::InitFlipAttackHitbox() {
	for (int i = 0; i < 4; i++) {
		m_flip_attacking->SetHitboxX(70.0f, i);
		m_flip_attacking->SetHitboxY(70.0f, i);
		m_flip_attacking->SetCHitboxX(0.0f, i);
		m_flip_attacking->SetCHitboxY(0.0f, i);
	}
}


void Horse::Init() {
	//num_attacks = 3;
	//num_taunts = 2;
	run_speed = 150;
	//InitTaunt();
	is_FacingRight = false;
	c_current_width = 900;
	c_current_height = 510;
	hitbox = std::make_shared<Hitbox>(c_current_width, c_current_height, 80.0f, 80.0f);
	//Animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderflip1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("nightmare-running");
	m_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 1, 4, 4, 0, (0.1f));
	m_attacking->Set2DPosition(c_current_width, c_current_height);
	m_attacking->SetSize(80.0f, 80.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-standing");
	m_standing = std::make_shared<AnimationSprite>(model, shader, texture, 1, 4, 4, 0, (0.1f));
	m_standing->Set2DPosition(c_current_width, c_current_height);
	m_standing->SetSize(80.0f, 80.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-death");
	m_dying = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_dying->Set2DPosition(c_current_width, c_current_height);
	m_dying->SetSize(80.0f, 80.0f);
	m_dying->SetCurrentFrames(1);
	//Animation flip
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-running");

	m_flip_attacking = std::make_shared<AnimationSprite>(model, shader, texture, 1, 4, 4, 0, (0.1f));
	m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
	m_flip_attacking->SetSize(80.0f, 80.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-standing");

	m_flip_standing = std::make_shared<AnimationSprite>(model, shader, texture, 1, 4, 4, 0, (0.1f));
	m_flip_standing->Set2DPosition(c_current_width, c_current_height);
	m_flip_standing->SetSize(80.0f, 80.0f);

	texture = ResourceManagers::GetInstance()->GetTexture("nightmare-death");
	m_flip_dying = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, (0.1f));
	m_flip_dying->Set2DPosition(c_current_width, c_current_height);
	m_flip_dying->SetSize(80.0f, 80.0f);
	m_flip_dying->SetCurrentFrames(1);

	health = 1;
	max_health = 1;
	//texture = ResourceManagers::GetInstance()->GetTexture("heart");
	InitAttackHitbox();
	InitFlipAttackHitbox();
};
void Horse::Update(GLfloat deltaTime) {
	if (!is_Alive) {
		if (is_Galloping) {
			ResourceManagers::GetInstance()->PauseSound("Gallop");
			is_Galloping = false;
		}
		m_dying->UpdateDying(deltaTime);
		return;
	}
	if (health == 0) {
		is_Alive = false;
		//m_dying->Update(deltaTime);
		return;
	}
	//if (not_taking_damage_time > 0) not_taking_damage_time -= deltaTime;
	//if (is_TakingDamage) taking_damage_time = taking_damage_time - deltaTime;

	standing_time = max(0, standing_time - deltaTime);
	if (standing_time > 0) {
		return;
	}
	else {
		if (!is_Galloping) {
			ResourceManagers::GetInstance()->PlaySound("Gallop");
			is_Galloping = true;
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
			ResourceManagers::GetInstance()->PauseSound("Gallop");
			is_Galloping = false;
		}
		c_current_width = min(c_current_width, screenWidth - 30);
		m_attacking->Set2DPosition(c_current_width, c_current_height);
		m_attacking->Update(deltaTime);
	}
	else {
		//is_Attacking = true;
		GLfloat s = deltaTime * run_speed;
		c_current_width -= s;
		if (c_current_width < 30) {
			is_Attacking = false;
			is_Standing = true;
			is_FacingRight = true;
			ResourceManagers::GetInstance()->PauseSound("Gallop");
			is_Galloping = false;
		}
		c_current_width = max(c_current_width, 30);
		m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
		m_flip_attacking->Update(deltaTime);
	}
};

void Horse::Draw() {
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
			}
			else {
				m_standing->Set2DPosition(c_current_width, c_current_height);
				m_standing->Draw();
			}
		}
		else {
			if (is_Attacking) {
				m_flip_attacking->Set2DPosition(c_current_width, c_current_height);
				m_flip_attacking->Draw();
			}
			else {
				m_flip_standing->Set2DPosition(c_current_width, c_current_height);
				m_flip_standing->Draw();
			}
		}
	}

};
void Horse::HandleKeyEvents(int key, bool bIsPressed) {
};

GLfloat* Horse::GetAttackHitbox() {
	int l = this->GetCurrentAttackFrame();
	//std::shared_ptr<GLfloat> vertex_hitbox[4];
	GLfloat x = 0;
	GLfloat y = 0;
	//printf("%f %f ", c_current_height, m_list_attacking[chosen_attack]->getCHitbox_y(l));
	if (is_FacingRight) {
		x = c_current_width + m_attacking->getCHitbox_x(l);
		y = c_current_height + m_attacking->getCHitbox_y(l);
		vertex[2] = m_attacking->getHitbox_x(l);
		vertex[3] = m_attacking->getHitbox_y(l);
	}
	else {
		x = c_current_width + m_flip_attacking->getCHitbox_x(l);
		y = c_current_height + m_flip_attacking->getCHitbox_y(l);
		vertex[2] = m_flip_attacking->getHitbox_x(l);
		vertex[3] = m_flip_attacking->getHitbox_y(l);
	}
	vertex[0] = x;
	vertex[1] = y;
	//printf("%f %f\n", vertex[0], vertex[1]);
	//printf("%f %f ", c_current_width, c_current_height);

	return vertex;
}

GLfloat* Horse::GetHitbox() {
	hitbox->Update(c_current_width, c_current_width, hitbox->getCHitbox_x(), hitbox->getHitbox_y());
	//printf("YES");
	vertex[0] = c_current_width;
	vertex[1] = c_current_height;
	vertex[2] = hitbox->getCHitbox_x();
	vertex[3] = hitbox->getCHitbox_y();
	return vertex;
}

void Horse::SetIsTakingDamge(bool is_TakingDamage) {
	//printf("%s\n", this->is_TakingDamage ? "true" : "false");
	if (not_taking_damage_time <= 0) {
		health--;
		//not_taking_damage_time = 0.8f;
		this->is_TakingDamage = is_TakingDamage;
	}
};


bool Horse::GetIs_Attacking() {
	//printf("Here");
	return is_Attacking;
};

int Horse::GetCurrentAttackFrame() {
	if (is_FacingRight) return m_attacking->GetCurrentFrame();
	else m_flip_attacking->GetCurrentFrame();
}

bool Horse::HasAttackHitbox() {
	if (!this->GetIs_Attacking()) return false;
	//printf("%d\n", m_attacking->getHitbox_x(this->GetCurrentAttackFrame()));
	if (m_attacking->getHitbox_x(this->GetCurrentAttackFrame()) > 0 ||
		m_attacking->getHitbox_y(this->GetCurrentAttackFrame()) > 0) {
		return true;
	}
	return false;
}

