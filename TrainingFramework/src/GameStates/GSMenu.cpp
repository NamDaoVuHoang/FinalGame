#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}

/*void GSMenu::InitBackground(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, string tex, int i) {
	auto texture = ResourceManagers::GetInstance()->GetTexture(tex);
	m_BackGround[i] = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround[i]->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround[i]->SetSize(screenWidth, screenHeight);
	//m_BackGround->push_back(n_BackGround);
}*/


void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	//auto texture = ResourceManagers::GetInstance()->GetTexture("TextureShader1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	//m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	/*for (int i = 0; i < num_background; i++) {
		//auto texture = ResourceManagers::GetInstance()->GetTexture(background_string[i]);
		InitBackground(model, shader, background_string[i], i);
	}*/

	auto texture = ResourceManagers::GetInstance()->GetTexture("Background");
	m_BackGround_1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround_1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround_1->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("EmptyButton");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 300);
	button->SetSize(200, 50);
 	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Play);
		});
	m_listButton_1.push_back(button);

	//setting button
	texture = ResourceManagers::GetInstance()->GetTexture("EmptyButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 400);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Setting);
		});
	m_listButton_1.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("EmptyButton");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		exit(0);
		});
	 m_listButton_1.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "KNIGHT", TEXT_COLOR::BLACK, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(screenWidth / 2 - 80, 120));

	std::shared_ptr<Text> text_button = std::make_shared<Text>(shader, font, "Start", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 80, 305));
	m_list_Text_button.push_back(text_button);

	text_button = std::make_shared<Text>(shader, font, "Credits", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 80, 405));
	m_list_Text_button.push_back(text_button);

	text_button = std::make_shared<Text>(shader, font, "Exit", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 80, 505));
	m_list_Text_button.push_back(text_button);

	ResourceManagers::GetInstance()->PlaySound("Main", true);
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{
	ResourceManagers::GetInstance()->PauseSound("Main");
}

void GSMenu::Resume()
{
	ResourceManagers::GetInstance()->PlaySound("Main",true);
}


void GSMenu::HandleEvents()
{
	
}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton_1)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	//m_BackGround->Update(deltaTime);
	for (auto it : m_listButton_1)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	/*for (int i = 0; i < num_background; i++) {
		m_BackGround[i]->Draw();
	}*/
	m_BackGround_1->Draw();
	//m_headlogo->Draw();
	for (auto it : m_listButton_1)
	{
		//printf("YES\n");
		it->Draw();
	}
	
	//m_Text_gameName->Draw();
	for (auto it : m_list_Text_button)
	{
		it->Draw();
	}
}
