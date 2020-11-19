#include "GSIntro.h"

#include "soloud.h"
#include "soloud_wav.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


GSIntro::GSIntro()
{
	m_time = 0;
}


GSIntro::~GSIntro()
{
}


void GSIntro::Init()
{
	ResourceManagers::GetInstance()->PlaySound("intro");

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("logo1");

	m_logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_logo->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_logo->SetSize(screenWidth, 320);
}

void GSIntro::Exit()
{
	
}


void GSIntro::Pause()
{
	
}

void GSIntro::Resume()
{
	
}


void GSIntro::HandleEvents()
{
	
}

void GSIntro::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSIntro::HandleTouchEvents(int x, int y, bool bIsPressed)
{

}

void GSIntro::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 2)
	{
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		m_time = 0;
	}
}

void GSIntro::Draw()
{
	m_logo->Draw();
}
