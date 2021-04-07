#include "GSPlay.h"

#include "Demon.h"
#include "Horse.h"
#include "MainCharacter.h"
#include "Minotaur.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "AnimationSprite.h"
#include "Text.h"
#include "Hitbox.h"
#include "GameButton.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}
void GSPlay::InitBackground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, string tex, int i) {
	auto texture = ResourceManagers::GetInstance()->GetTexture(tex);
	m_BackGround_1[i] = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround_1[i]->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround_1[i]->SetSize(screenWidth, screenHeight);
	m_BackGround_2[i] = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround_2[i]->Set2DPosition(3.0 * screenWidth / 2, screenHeight / 2);
	m_BackGround_2[i]->SetSize(screenWidth, screenHeight);
	//m_BackGround->push_back(n_BackGround);
}

void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	//m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	for (int i = 0; i < num_background; i++) {
		//auto texture = ResourceManagers::GetInstance()->GetTexture(background_string[i]);
		InitBackground(model,shader,background_string[i],i);
	}

	auto texture = ResourceManagers::GetInstance()->GetTexture("Setting");
	/*m_setting = std::make_shared<GameButton>(model, shader, texture);
	m_setting->Set2DPosition(screenWidth / 2, 30);
	m_setting->SetSize(30, 30);
	m_setting->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Setting);
		});*/
	//m_listButton.push_back(button);

	//text game title
	texture = ResourceManagers::GetInstance()->GetTexture("gameover");
	m_gameover_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameover_background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_gameover_background->SetSize(screenWidth, screenHeight);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("times");
	m_gameover_text = std::make_shared< Text>(shader, font, "Game Over", TEXT_COLOR::WHILE, 3.0);
	m_gameover_text->Set2DPosition(screenWidth / 2 - 170, screenHeight / 2);

	//std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("times");
	m_youwin_text = std::make_shared< Text>(shader, font, "You Win", TEXT_COLOR::WHILE, 3.0);
	m_youwin_text->Set2DPosition(screenWidth / 2 - 140, screenHeight / 2);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	texture = ResourceManagers::GetInstance()->GetTexture("MenuButton");
	m_menu = std::make_shared<GameButton>(model, shader, texture);
	m_menu->Set2DPosition(screenWidth / 2, screenHeight/2 + 80);
	m_menu->SetSize(200, 50);
	m_menu->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});

	c_current_width_1 = screenWidth / 2;
	c_current_heigth_1 = screenWidth / 2;
	c_current_width_2 = 3.0 * screenWidth / 2;
	c_current_heigth_2 = screenWidth / 2;
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_menu_text = std::make_shared< Text>(shader, font, "Menu", TEXT_COLOR::WHILE, 1.0);
	m_menu_text->Set2DPosition(screenWidth / 2 - 80, screenHeight/2 + 80);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	texture = ResourceManagers::GetInstance()->GetTexture("EmptyButton");
	m_back = std::make_shared<GameButton>(model, shader, texture);
	m_back->Set2DPosition(screenWidth / 2, 30);
	m_back->SetSize(120, 30);
	m_back->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	//m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_back_text = std::make_shared<Text>(shader, font, "Back", TEXT_COLOR::BLACK, 0.54f);
	m_back_text->Set2DPosition(Vector2(screenWidth / 2 - 48, 35));
	//m_list_Text_button.push_back(text_button);

	m_main_character = std::make_shared<MainCharacter>();
	m_main_character->Init();

	m_minotaur = std::make_shared<Minotaur>();
	m_minotaur->Init();

	m_horse = std::make_shared<Horse>();
	m_horse->Init();

	m_demon = std::make_shared<Demon>();
	m_demon->Init();

	ResourceManagers::GetInstance()->PlaySound("Battle");
}

void GSPlay::Exit()
{
	ResourceManagers::GetInstance()->PauseSound("Battle");
	if (is_playing_dead) ResourceManagers::GetInstance()->PauseSound("Dead");
	if (is_playing_win) ResourceManagers::GetInstance()->PauseSound("Win");
}


void GSPlay::Pause()
{
	is_Pause = true;
	ResourceManagers::GetInstance()->PauseSound("Battle");
	if (is_playing_dead) ResourceManagers::GetInstance()->PauseSound("Dead");
	if (is_playing_win) ResourceManagers::GetInstance()->PauseSound("Win");
}

void GSPlay::Resume()
{
	is_Pause = false;
	ResourceManagers::GetInstance()->PlaySound("Battle",true);
}


void GSPlay::HandleEvents()
{
	//printf("%f\n", "s");
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{	
	m_main_character->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (is_Gameover) {
		m_menu->HandleTouchEvents(x, y, bIsPressed);
		//if (m_menu->IsHandle()) return;
	}
	else m_back->HandleTouchEvents(x, y, bIsPressed);
}

bool GSPlay::CheckHitbox(GLfloat x1, GLfloat y1, GLfloat w1, GLfloat h1,
		GLfloat x2, GLfloat y2, GLfloat w2, GLfloat h2) {
	//printf("%f %f %f %f %f %f %f %f\n",x1, y1, w1, h1, x2, y2, w2, h2);
	return ((x1 + w1 / 2 >= x2 - w2 / 2) && 
		(x2 + w2 / 2 >= x1 - w1 / 2) &&
		(y1 + h1 / 2 >= y2 - h2 / 2) &&
		(y2 + h2 / 2 >= y1 - h1 / 2));
}

void GSPlay::UpdateBackground() {
	//std::cout << is_LockScreen << "\n";
	if (!is_LockScreen) {
		travel = m_main_character->GetTravel();
		c_current_width_1 -= travel;
		c_current_width_2 -= travel + 0.001f; 
		//printf("%f %f\n", c_current_width_1, c_current_width_2);
		if (c_current_width_2 < screenWidth / 2) {
			c_current_width_1 += screenWidth;
			c_current_width_2 += screenWidth;
		}
		m_horse->SetCurrentX(m_horse->GetCurrentX() - travel);
		m_minotaur->SetCurrentX(m_minotaur->GetCurrentX() - travel);
		m_demon->SetCurrentX(m_demon->GetCurrentX() - travel);
	}
}

void GSPlay::Update(float deltaTime)
{	
	if (!m_horse->Is_Alive() && horse_death_time > 0) horse_death_time -= deltaTime;
	if (!m_minotaur->Is_Alive() && minotaur_death_time > 0) minotaur_death_time -= deltaTime;
	if (!m_demon->Is_Alive() && demon_death_time > 0) demon_death_time -= deltaTime;
	m_main_character->SetIsLockScreen(is_LockScreen);
	if (!is_Pause) {
		m_main_character->Update(deltaTime);
		if (!is_Update_horse && m_horse->GetCurrentX() <= m_main_character->GetCurrentX() + 400 && (m_horse->Is_Alive()||horse_death_time > 0)) {
			is_Update_horse = true;	
		}
		if (is_Update_horse && horse_death_time > 0) {
			m_horse->Update(deltaTime);
			m_horse->is_Update = true;
			if (m_horse->Is_Alive())
				is_LockScreen = true;
			else is_LockScreen = false;
		}
		if (!is_Update_minotaur && m_minotaur->GetCurrentX() <= m_main_character->GetCurrentX() + 400 && (m_minotaur->Is_Alive()||minotaur_death_time > 0)) {
			is_Update_minotaur = true;
		}
		if (is_Update_minotaur && minotaur_death_time > 0) {
			m_minotaur->Update(deltaTime, m_main_character->GetCurrentX(), m_main_character->GetCurrentY());
			m_minotaur->is_Update = true;
			if (m_minotaur->Is_Alive())
				is_LockScreen = true;
			else is_LockScreen = false;
		}
		if (!is_Update_demon && m_demon->GetCurrentX() <= m_main_character->GetCurrentX() + 400 && (m_demon->Is_Alive() || demon_death_time > 0)) {
			is_Update_demon = true;
		}
		if (is_Update_demon && demon_death_time > 0) {
			m_demon->Update(deltaTime);
			m_demon->is_Update = true;
			if (m_demon->Is_Alive())
				is_LockScreen = true;
			else is_LockScreen = false;
		}
		//printf("%s\n", m_horse->HasAttackHitbox() ? "true" : "false");
			if (is_Update_horse && m_horse->Is_Alive()) {
				vertex = m_horse->GetAttackHitbox();
				main_hitbox = m_main_character->GetHitbox();
				
				//printf("%f*vertex, *(vertex+1), *(vertex+2), *(vertex+3));
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *main_hitbox, *(main_hitbox + 1), *(main_hitbox + 2), *(main_hitbox + 3))) {
					m_main_character->SetIsTakingDamge(true);
				}
			}
			if (is_Update_minotaur && m_minotaur->Is_Alive()) {
				//printf("YES");
				//m_main_character->GetAttackHitbox();
				
				vertex = m_minotaur->GetAttackHitbox();
				main_hitbox = m_main_character->GetHitbox();
				//*mino_hitbox = Hitbox(*vertex, *(vertex+1), *(vertex+2), *(vertex+3));
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *main_hitbox, *(main_hitbox + 1), *(main_hitbox + 2), *(main_hitbox + 3))) {
					m_main_character->SetIsTakingDamge(true);
				}
			}
			if (is_Update_demon && m_demon->Is_Alive()) {
				vertex = m_demon->GetAttackHitbox();
				main_hitbox = m_main_character->GetHitbox();

				//printf("%f*vertex, *(vertex+1), *(vertex+2), *(vertex+3));
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *main_hitbox, *(main_hitbox + 1), *(main_hitbox + 2), *(main_hitbox + 3))) {
					m_main_character->SetIsTakingDamge(true);
				}
			}
		if (!m_main_character->Is_Alive()) {
			is_Gameover = true;
			return;
		}
		if (m_main_character->HasAttackHitbox()) {
			vertex = m_main_character->GetAttackHitbox();
			if (is_Update_horse) {
				mino_hitbox = m_horse->GetHitbox();
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *mino_hitbox, *(mino_hitbox + 1), *(mino_hitbox + 2), *(mino_hitbox + 3))) {
					m_horse->SetIsTakingDamge(true);
				}
				if (!m_horse->Is_Alive()) {
					//printf("YES");
					is_LockScreen = false;
					is_Update_horse = false;
				}
			}
			if (is_Update_minotaur) {
				mino_hitbox = m_minotaur->GetHitbox();
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *mino_hitbox, *(mino_hitbox + 1), *(mino_hitbox + 2), *(mino_hitbox + 3))) {
					m_minotaur->SetIsTakingDamge(true);
				}
				if (!m_minotaur->Is_Alive()) {
					is_LockScreen = false;
					is_Update_minotaur = false;
				}
			}
			if (is_Update_demon) {
				mino_hitbox = m_demon->GetHitbox();
				if (this->CheckHitbox(*vertex, *(vertex + 1), *(vertex + 2), *(vertex + 3), *mino_hitbox, *(mino_hitbox + 1), *(mino_hitbox + 2), *(mino_hitbox + 3))) {
					m_demon->SetIsTakingDamge(true);
				}
				if (!m_demon->Is_Alive()) {
					//printf("YES");
					is_LockScreen = false;
					is_Update_demon = false;
				}
			}
		//if (m_horse->Get)
		}
	}
	UpdateBackground();
}

void GSPlay::Draw()
{	
		//printf("%s\n", is_FacingRight);
		//printf("%f %f\n", c_current_width_1, c_current_width_2);
		if (!is_Gameover) {
			for (int i = 0; i < num_background; i++) {
				m_BackGround_1[i]->Set2DPosition(c_current_width_1, screenHeight / 2);
				m_BackGround_1[i]->Draw();
				m_BackGround_2[i]->Set2DPosition(c_current_width_2, screenHeight / 2);
				m_BackGround_2[i]->Draw();
			}
			if (m_demon->Is_Alive() || demon_death_time > 0) m_demon->Draw();
			if (m_minotaur->Is_Alive() || minotaur_death_time > 0) m_minotaur->Draw();
			else {
				is_Gameover = true;
				if (!is_playing_minotaur_death) {
					ResourceManagers::GetInstance()->PlaySound("deaths");
					is_playing_minotaur_death = true;
				}
			}
			//std::cout << "YES";
			if (m_horse->Is_Alive() || horse_death_time > 0) m_horse->Draw();
			m_back->Draw();
			m_back_text->Draw();

		}
		else {
			ResourceManagers::GetInstance()->PauseSound("Battle");

			m_gameover_background->Draw();
			if (!m_minotaur->Is_Alive()) {
				m_youwin_text->Draw();
				if (!is_playing_win) {
					ResourceManagers::GetInstance()->PlaySound("Win");
					is_playing_win = true;
				}
			}
			else {
				m_gameover_text->Draw();
				if (!is_playing_dead) {
					ResourceManagers::GetInstance()->PlaySound("Dead");
					is_playing_dead = true;
				}
			}
			m_menu->Draw();
			//m_menu_text->Draw();
		}
		m_main_character->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}