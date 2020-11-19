#include "GSMenu.h"
#include "soloud.h"
#include "soloud_wav.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isPlayingMusic;

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}

void GSMenu::Init()
{
	if (isPlayingMusic) {
		ResourceManagers::GetInstance()->PlaySound("mainmenu");
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bgmain4");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto shaderText = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);

	//BackGround
	
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	//button 
	texture = ResourceManagers::GetInstance()->GetTexture("button");
	
	//play button
	{
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth / 2, 200);
		button->SetSize(BUTTON_SIZE);
		button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
			ResourceManagers::GetInstance()->PauseSound("mainmenu");
		});
		m_listButton.push_back(button);

		//PLay text
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_Text = std::make_shared< Text>(shaderText, font, "PLAY", TEXT_COLOR::WHILE, 1.0);
		m_Text->Set2DPosition(screenWidth / 2 - 35, 210);
		m_listText.push_back(m_Text);
	}
	

	//setting button
	{
		//texture = ResourceManagers::GetInstance()->GetTexture("button");
		button = std::make_shared<GameButton>(model, shader, texture);
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth / 2, 300);
		button->SetSize(BUTTON_SIZE);
		button->SetOnClick([]() {
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
		});
		m_listButton.push_back(button);

		//Setting text
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_Text = std::make_shared< Text>(shaderText, font, "SETTING", TEXT_COLOR::WHILE, 1.0);
		m_Text->Set2DPosition(screenWidth / 2 - 60, 310);
		m_listText.push_back(m_Text);
	}
	

	//credit button
	{
		
		button = std::make_shared<GameButton>(model, shader, texture);
		
		button->Set2DPosition(screenWidth / 2, 400);
		button->SetSize(BUTTON_SIZE);
		button->SetOnClick([]() {
			/*if (isPlayingMusic) {
				ResourceManagers::GetInstance()->PlaySound("credit");
			}*/
			ResourceManagers::GetInstance()->PauseSound("mainmenu");
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
		});
		m_listButton.push_back(button);

		//Credit text
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_Text = std::make_shared< Text>(shaderText, font, "CREDIT", TEXT_COLOR::WHILE, 1.0);
		m_Text->Set2DPosition(screenWidth / 2 - 45, 410);
		m_listText.push_back(m_Text);
	}
	

	//exit button
	{
		//texture = ResourceManagers::GetInstance()->GetTexture("button");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth / 2, 500);
		button->SetSize(300, 100);
		button->SetOnClick([]() {
			exit(0);
		});
		m_listButton.push_back(button);

		//Quit text
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_Text = std::make_shared< Text>(shaderText, font, "QUIT", TEXT_COLOR::WHILE, 1.0);
		m_Text->Set2DPosition(screenWidth / 2 - 35, 510);
		m_listText.push_back(m_Text);
	}

	

	

	

	

	
	

}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
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
