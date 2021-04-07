#include "GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSSetting::GSSetting()
{

}


GSSetting::~GSSetting()
{
}


void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader1");
	//m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	
	auto texture = ResourceManagers::GetInstance()->GetTexture("Background");
	m_BackGround_1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround_1->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround_1->SetSize(screenWidth, screenHeight);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("EmptyButton");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 500);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::shared_ptr<Text> text_button = std::make_shared<Text>(shader, font, "Back", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 80, 505));
	m_list_Text_button.push_back(text_button);

	text_button = std::make_shared<Text>(shader, font, "This was created by Nam", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 160, 255));
	m_list_text.push_back(text_button);

	text_button = std::make_shared<Text>(shader, font, "With help of Gameloft's crew", TEXT_COLOR::BLACK, 0.9);
	text_button->Set2DPosition(Vector2(screenWidth / 2 - 160, 325));
	m_list_text.push_back(text_button);

	ResourceManagers::GetInstance()->PlaySound("Main", true);
}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{
	ResourceManagers::GetInstance()->PauseSound("Main");
}

void GSSetting::Resume()
{
	ResourceManagers::GetInstance()->PlaySound("Main", true);
}


void GSSetting::HandleEvents()
{

}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSetting::Update(float deltaTime)
{
	//m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSSetting::Draw()
{
	//m_BackGround->Draw();
	/*for (int i = 0; i < num_background; i++) {
		m_BackGround[i]->Draw();
	}*/
	m_BackGround_1->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
	for (auto it : m_list_Text_button)
	{
		it->Draw();
	}
	for (auto it : m_list_text) {
		it->Draw();
	}
}
