#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
using namespace std;

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
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

private:
	int num_background = 11;
	string background_string[11] = { "Layer_0010_1","Layer_0009_2","Layer_0008_3","Layer_0007_Lights","Layer_0006_4"
		,"Layer_0005_5","Layer_0004_Lights","Layer_0003_6","Layer_0002_7","Layer_0001_8","Layer_0000_9" };
	//std::shared_ptr<Sprite2D> m_BackGround[11];
	std::shared_ptr<Sprite2D> m_BackGround_1;
	//std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Sprite2D> m_headlogo;
	std::list<std::shared_ptr<GameButton>>	m_listButton_1;
	std::shared_ptr<Text>  m_Text_gameName;
	std::list<std::shared_ptr<Text>> m_list_Text_button;

};

