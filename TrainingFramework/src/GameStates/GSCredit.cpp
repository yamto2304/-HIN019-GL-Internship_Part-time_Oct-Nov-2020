#include "GSCredit.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isPlayingMusic;

GSCredit::GSCredit()
{
}


GSCredit::~GSCredit()
{
}

void GSCredit::Init()
{
	if (isPlayingMusic) {
		ResourceManagers::GetInstance()->PlaySound("credit", true);
	}
	//ResourceManagers::GetInstance()->PauseSound("mainmenu");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("credit_bg");
	auto shaderText = ResourceManagers::GetInstance()->GetShader("TextShader");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(500, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 50);
	button->SetSize(225,75);
	button->SetOnClick([]() {
		if (isPlayingMusic) {
			ResourceManagers::GetInstance()->PlaySound("mainmenu");
		}
		ResourceManagers::GetInstance()->PauseSound("credit");
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
	m_Text = std::make_shared< Text>(shaderText, font, "MENU", TEXT_COLOR::WHILE, 1.0);
	m_Text->Set2DPosition(screenWidth / 2 - 40, 60);
	m_listText.push_back(m_Text);

	//State game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("timesbi");
	m_Text = std::make_shared< Text>(shader, font, "Space War ", TEXT_COLOR::BLUE, 2.0);
	m_Text->Set2DPosition(Vector2(screenWidth / 2 - 30, 200));
	m_listText.push_back(m_Text);

	m_Text = std::make_shared< Text>(shader, font, "HoangTuan ", TEXT_COLOR::RED, 1.0);
	m_Text->Set2DPosition(Vector2(screenWidth / 2 - 25, 300));
	m_listText.push_back(m_Text);

	m_Text = std::make_shared< Text>(shader, font, "TuanIT2304@gmail.com ", TEXT_COLOR::RED, 1.0);
	m_Text->Set2DPosition(Vector2(screenWidth / 2 - 25, 350));
	m_listText.push_back(m_Text);
}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{

}

void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{

}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSCredit::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCredit::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto text : m_listText) {
		text->Draw();
	}
	
}