#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "GameButton.h"

#define BACKGROUND_SPEED 500

extern int screenWidth; //need get on Graphic engine   ||480
extern int screenHeight; //need get on Graphic engine  ||800

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(m_BackGround);
	
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth * 3 / 2, screenHeight * 3 / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	m_listSprite2D.push_back(m_BackGround);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 250);
	button->SetSize(200, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	m_score = std::make_shared< Text>(shader, font, "score: 10000", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
	obj->Set2DPosition(240, 400);
	obj->SetSize(52, 52);
	m_listSpriteAnimations.push_back(obj);
}

void GSPlay::Exit()
{

}

void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}
	for (auto bg : m_listSprite2D)
	{
		bg->Update(deltaTime);
		bg->Set2DPosition(bg->Get2DPosition().x - BACKGROUND_SPEED *deltaTime, screenHeight / 2);
		if (bg->Get2DPosition().x <= -screenWidth / 2) {
			bg->Set2DPosition(bg->Get2DPosition().x + 2 * screenWidth, screenHeight / 2);
		}
	}
}

void GSPlay::Draw()
{
	for (auto back_ground : m_listSprite2D)
	{
		back_ground->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	}
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}