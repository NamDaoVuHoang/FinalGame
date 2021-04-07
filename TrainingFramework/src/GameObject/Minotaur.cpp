#include "Minotaur.h"
#include "AnimationSprite.h"
#include "Hitbox.h"
using namespace std;

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


Minotaur::Minotaur() {};
Minotaur::~Minotaur() {
};


void Minotaur::InitAttackHitbox() {
	for (int i = 1; i <= 5; i++) {
		m_list_attacking[0]->SetHitboxX(80.0f, i);
		m_list_attacking[0]->SetHitboxY(90.0f, i);
		m_list_attacking[0]->SetCHitboxX(70.0f, i);
		m_list_attacking[0]->SetCHitboxY(0.0f, i);
	}
	for (int i = 1; i <= 2; i++) {
		m_list_attacking[1]->SetHitboxX(80.0f, i);
		m_list_attacking[1]->SetHitboxY(45.0f, i);
		m_list_attacking[1]->SetCHitboxX(70.0f, i);
		m_list_attacking[1]->SetCHitboxY(22.5f, i);
	}
	for (int i = 3; i <= 6; i++) {
		m_list_attacking[2]->SetHitboxX(235.0f, i);
		m_list_attacking[2]->SetHitboxY(90.0f, i);
		m_list_attacking[2]->SetCHitboxX(0.0f, i);
		m_list_attacking[2]->SetCHitboxY(0.0f, i);
	}
};
void Minotaur::InitFlipAttackHitbox() {
	for (int i = 1; i <= 5; i++) {
		m_list_flip_attacking[0]->SetHitboxX(80.0f, i);
		m_list_flip_attacking[0]->SetHitboxY(90.0f, i);
		m_list_flip_attacking[0]->SetCHitboxX(-70.0f, i);
		m_list_flip_attacking[0]->SetCHitboxY(0.0f, i);
	}
	for (int i = 1; i <= 2; i++) {
		m_list_flip_attacking[1]->SetHitboxX(80.0f, i);
		m_list_flip_attacking[1]->SetHitboxY(45.0f, i);
		m_list_flip_attacking[1]->SetCHitboxX(-70.0f, i);
		m_list_flip_attacking[1]->SetCHitboxY(22.5f, i);
	}
	for (int i = 3; i <= 6; i++) {
		m_list_flip_attacking[2]->SetHitboxX(235.0f, i);
		m_list_flip_attacking[2]->SetHitboxY(90.0f, i);
		m_list_flip_attacking[2]->SetCHitboxX(0.0f, i);
		m_list_flip_attacking[2]->SetCHitboxY(0.0f, i);
	}
};

void Minotaur::InitAttack() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");

	m_list_attacking[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 3, (0.17f));

	m_list_attacking[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 4, (0.25f));

	m_list_attacking[2] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 6, (0.07f));

	for (int i = 0; i < num_attacks; i++) {
		m_list_attacking[i]->SetDamage(1.0f);
		m_list_attacking[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_attacking[i]->SetSize(270, 270);
	}
	
	

	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");

	m_list_flip_attacking[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 3, (0.17f));

	m_list_flip_attacking[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 4, (0.25f));

	m_list_flip_attacking[2] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 9, 6, (0.07f));

	for (int i = 0; i < num_attacks; i++) {
		m_list_flip_attacking[i]->SetDamage(1.0f);
		m_list_flip_attacking[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_flip_attacking[i]->SetSize(270, 270);
	}
	InitAttackHitbox();
	InitFlipAttackHitbox();
}

void Minotaur::InitTaunt() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");

	m_list_taunting[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 2, (0.1f));

	m_list_taunting[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 5, (0.1f));

	for (int i = 0; i < num_taunts; i++) {
		m_list_taunting[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_taunting[i]->SetSize(270, 270);
	}

	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");

	m_list_flip_taunting[0] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 2, (0.1f));

	m_list_flip_taunting[1] = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 5, (0.1f));

	for (int i = 0; i < num_taunts; i++) {
		m_list_flip_taunting[i]->Set2DPosition(c_current_width, c_current_height);
		m_list_flip_taunting[i]->SetSize(270, 270);
	}
	
}

void Minotaur::Init() {
	num_attacks = 3;
	num_taunts = 2;
	run_speed = 100;
	InitAttack();
	InitTaunt();
	is_FacingRight = false;
	c_current_width = 1700;
	c_current_height = 508;
	hitbox = std::make_shared<Hitbox>(c_current_width, c_current_height, 90.0f, 90.0f);
	//Animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Minotaur");
	m_running = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 8, 1, (0.1f));
	m_running->Set2DPosition(c_current_width, c_current_height);
	m_running->SetSize(270, 270);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");

	//shader = ResourceManagers::GetInstance()->GetShader("AnimationShader1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");

	m_standing = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 0, (0.1f));
	m_standing->Set2DPosition(c_current_width, c_current_height);
	m_standing->SetSize(270, 270);

	m_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 7, 7, (0.3f));
	m_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_takingdamage->SetSize(270, 270);

	m_dying = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 9, (0.1f));
	m_dying->Set2DPosition(c_current_width, c_current_height);
	m_dying->SetSize(270, 270);

	//Animation flip
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShaderFlip1");
	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_running = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 8, 1, (0.1f));
	m_flip_running->Set2DPosition(c_current_width, c_current_height);
	m_flip_running->SetSize(270, 270);

	//texture = ResourceManagers::GetInstance()->GetTexture("knight");
	m_flip_standing = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 5, 0, (0.1f));
	m_flip_standing->Set2DPosition(c_current_width, c_current_height);
	m_flip_standing->SetSize(270, 270);


	m_flip_takingdamage = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 7, 7, (0.3f));
	m_flip_takingdamage->Set2DPosition(c_current_width, c_current_height);
	m_flip_takingdamage->SetSize(270, 270);

	m_flip_dying = std::make_shared<AnimationSprite>(model, shader, texture, 20, 9, 6, 9, (0.1f));
	m_flip_dying->Set2DPosition(c_current_width, c_current_height);
	m_flip_dying->SetSize(270, 270);

	health = 4;
	max_health = 4;
	texture = ResourceManagers::GetInstance()->GetTexture("heart");
	for (int i = 0; i < max_health; i++) {
		health_bar[i] = std::make_shared<AnimationSprite>(model, shader, texture, 1, 5, 5, 0, 0.05f);
		health_bar[i]->Set2DPosition(screenWidth - 30.0f - 21.0f * i, 30.0f);
		health_bar[i]->SetSize(20, 20);
	}

};
void Minotaur::Update(GLfloat deltaTime, GLfloat c_x, GLfloat c_y) {
	if (!is_Alive) {
		m_dying->UpdateDying(deltaTime);
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
		is_Standing = false;
		return;
	}
	if (abs(c_x - c_current_width) >= 110 && !is_Attacking && !is_Taunting) {
		if (c_x < c_current_width) {
			is_FacingRight = false;
		}
		else is_FacingRight = true;
		is_Running = true;
		if (is_FacingRight) {
			GLfloat s = deltaTime * run_speed;
			c_current_width += s;
			c_current_width = min(c_current_width, screenWidth - 30);
			m_running->Set2DPosition(c_current_width, c_current_height);
			m_running->UpdateRunning(deltaTime, is_Running);
		}
		else {
			GLfloat s = deltaTime * run_speed;
			c_current_width -= s;
			c_current_width = max(c_current_width, 30);
			m_flip_running->Set2DPosition(c_current_width, c_current_height);
			m_flip_running->UpdateRunning(deltaTime, is_Running);
		}
	}
	else {
		is_Running = false;
		m_running->SetCurrentFrames(0);
		if (!is_Attacking && !is_Taunting) {
			chosen_attack = rand() % 3;
			if (chosen_attack <= 1) chosen_taunt = 0;
			else chosen_taunt = 1;
			is_Taunting = true;
		}
		if (is_Taunting) {
			if (is_FacingRight) m_list_taunting[chosen_taunt]->UpdateTaunting(deltaTime,&is_Taunting);
			else m_list_flip_taunting[chosen_taunt]->UpdateTaunting(deltaTime, &is_Taunting);
		}
		if (!is_Taunting) {
			if (!is_Attacking) is_Attacking = true;
			if (is_FacingRight) {
				m_list_attacking[chosen_attack]->UpdateAttacking(deltaTime, &is_Attacking);
				if (m_list_attacking[chosen_attack]->GetCurrentFrame() == 1)
					ResourceManagers::GetInstance()->PlaySound("main_attack");
			}
			else {
				m_list_flip_attacking[chosen_attack]->UpdateAttacking(deltaTime, &is_Attacking);
				if (m_list_flip_attacking[chosen_attack]->GetCurrentFrame() == 1) 
					ResourceManagers::GetInstance()->PlaySound("main_attack");
			}
			if (!is_Attacking) {
				is_Standing = true;
				standing_time = 0.5f;
				if (c_x < c_current_width) {
					is_FacingRight = false;
				}
				else is_FacingRight = true;
			}
		}
	}
};

void Minotaur::Draw() {
	if (!is_Alive){
		m_dying->Set2DPosition(c_current_width, c_current_height);
		m_dying->Draw();
	}
	else {
		if (is_FacingRight) {
			if (is_Running) {
				m_running->Set2DPosition(c_current_width, c_current_height);
				m_running->Draw();
			}
			else if (is_Taunting) {
				m_list_taunting[chosen_taunt]->Set2DPosition(c_current_width, c_current_height);
				m_list_taunting[chosen_taunt]->Draw();
			}
			else if (is_Attacking) {
				m_list_attacking[chosen_attack]->Set2DPosition(c_current_width, c_current_height);
				m_list_attacking[chosen_attack]->Draw();
			}
			else {
				m_standing->Set2DPosition(c_current_width, c_current_height);
				m_standing->Draw();
			}
		}
		else {
			if (is_Running) {
				m_flip_running->Set2DPosition(c_current_width, c_current_height);
				m_flip_running->Draw();
			}
			else if (is_Taunting) {
				m_list_flip_taunting[chosen_taunt]->Set2DPosition(c_current_width, c_current_height);
				m_list_flip_taunting[chosen_taunt]->Draw();
			}
			else if (is_Attacking) {
				m_list_flip_attacking[chosen_attack]->Set2DPosition(c_current_width, c_current_height);
				m_list_flip_attacking[chosen_attack]->Draw();
			}
			else {
				m_flip_standing->Set2DPosition(c_current_width, c_current_height);
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
void Minotaur::HandleKeyEvents(int key, bool bIsPressed) {
};

GLfloat* Minotaur::GetAttackHitbox() {
	int l = this->GetCurrentAttackFrame();
	//std::shared_ptr<GLfloat> vertex_hitbox[4];
	GLfloat x = 0;
	GLfloat y = 0;
	//printf("%f %f ", c_current_height, m_list_attacking[chosen_attack]->getCHitbox_y(l));
	if (is_FacingRight) {
		x = c_current_width + m_list_attacking[chosen_attack]->getCHitbox_x(l);
		y = c_current_height + m_list_attacking[chosen_attack]->getCHitbox_y(l);
		vertex[2] = m_list_attacking[chosen_attack]->getHitbox_x(l);
		vertex[3] = m_list_attacking[chosen_attack]->getHitbox_y(l);
	}
	else {
		x = c_current_width + m_list_flip_attacking[chosen_attack]->getCHitbox_x(l);
		y = c_current_height + m_list_flip_attacking[chosen_attack]->getCHitbox_y(l);
		vertex[2] = m_list_flip_attacking[chosen_attack]->getHitbox_x(l);
		vertex[3] = m_list_flip_attacking[chosen_attack]->getHitbox_y(l);
	}
	vertex[0] = x;
	vertex[1] = y;
	//printf("%f %f\n", vertex[0], vertex[1]);
	//printf("%f %f ", c_current_width, c_current_height);
	
	return vertex;
}

GLfloat*  Minotaur::GetHitbox() {
	hitbox->Update(c_current_width, c_current_width, hitbox->getCHitbox_x(), hitbox->getHitbox_y());
	//printf("YES");
	vertex[0] = c_current_width;
	vertex[1] = c_current_height;
	vertex[2] = hitbox->getCHitbox_x();
	vertex[3] = hitbox->getCHitbox_y();
	return vertex;
}

void Minotaur::SetIsTakingDamge(bool is_TakingDamage) {
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


bool Minotaur::GetIs_Attacking() {
	//printf("Here");
	return is_Attacking;
};

int Minotaur::GetCurrentAttackFrame() {
	if (is_FacingRight) return m_list_attacking[chosen_attack]->GetCurrentFrame();
	else m_list_flip_attacking[chosen_attack]->GetCurrentFrame();
}

bool Minotaur::HasAttackHitbox() {
	if (!this->GetIs_Attacking()) return false;
	//printf("%d %d\n", chosen_attack, m_list_attacking[chosen_attack]->GetCurrentFrame());
	if (m_list_attacking[chosen_attack]->getHitbox_x(this->GetCurrentAttackFrame()) > 0 ||
		m_list_attacking[chosen_attack]->getHitbox_y(this->GetCurrentAttackFrame()) > 0) {
		return true;
	}
	return false;
}

