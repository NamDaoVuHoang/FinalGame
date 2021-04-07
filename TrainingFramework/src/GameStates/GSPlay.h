#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
using namespace std;

class Demon;
class Horse;
class Character;
class Hitbox;
class Minotaur;
class MainCharacter;
class Sprite2D;
class Sprite3D;
class AnimationSprite;
class Text;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void InitBackground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, string tex, int i);
	void SetNewPostionForBullet();
	bool CheckHitbox(GLfloat x1, GLfloat y1, GLfloat w1, GLfloat h1,
		GLfloat x2, GLfloat y2, GLfloat w2, GLfloat h2);
	void UpdateBackground();

private:

	bool is_Pause = false;
	bool is_Gameover = false;
	bool is_LockScreen = false;
	bool is_Update_demon = false;
	bool is_Update_horse = false;
	bool is_Update_minotaur = false;
	bool is_playing_dead = false;
	bool is_playing_win = false;
	bool is_playing_minotaur_death = false;
	bool is_chosing_difficult = true;
	
	GLfloat demon_death_time = 0.4f;
	GLfloat horse_death_time = 0.4f;
	GLfloat minotaur_death_time = 0.6f;
	GLfloat c_current_width_1;
	GLfloat c_current_heigth_1;
	GLfloat c_current_width_2;
	GLfloat c_current_heigth_2;
	GLfloat travel = 0.0f;
	//GLfloat screen_speed = 100;
	GLfloat* main_hitbox;
	GLfloat* mino_hitbox;
	GLfloat* vertex;
	int num_enemies = 2;
	int num_background = 11;
	string background_string[11] = { "Layer_0010_1","Layer_0009_2","Layer_0008_3","Layer_0007_Lights","Layer_0006_4"
		,"Layer_0005_5","Layer_0004_Lights","Layer_0003_6","Layer_0002_7","Layer_0001_8","Layer_0000_9" };
	std::shared_ptr<Sprite2D> m_gameover_background;
	std::shared_ptr<GameButton> m_back;
	std::shared_ptr<GameButton> m_menu;
	std::shared_ptr<Text> m_menu_text;
 	std::shared_ptr<MainCharacter> m_main_character;
	std::shared_ptr<Minotaur> m_minotaur;
	std::shared_ptr<Demon> m_demon;
	std::shared_ptr<Sprite2D> m_BackGround_1[11];
	std::shared_ptr<Sprite2D> m_BackGround_2[11];
	std::shared_ptr<Horse> m_horse;
	std::shared_ptr<Text>  m_gameover_text;
	std::shared_ptr<Text>  m_youwin_text;
	std::shared_ptr<Text>  m_back_text;
};
