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
#include "Player.h"

#define BACKGROUND_SPEED 100
#define PLAYER_SPEED 300
int DIRECTION = 0;

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
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_night");

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

	//Player
	auto player = ResourceManagers::GetInstance()->GetTexture("shipfinal");
	m_Player = std::make_shared<Sprite2D>(model, shader, player);
	m_Player->Set2DPosition(screenWidth / 2, 500);
	m_Player->SetSize(152, 152);

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
	obj->SetSize(152, 152);
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
	if (bIsPressed)
	{
		switch (key)
		{
		case(KEY_RIGHT):
			DIRECTION = MOVE_RIGHT;
			break;
		case(KEY_MOVE_RIGHT):
			DIRECTION = MOVE_RIGHT;
			break;
		case(KEY_LEFT) :
			DIRECTION = MOVE_LEFT;
			break;
		case(KEY_MOVE_LEFT):
			DIRECTION = MOVE_LEFT;
			break;
		case(KEY_UP):
			DIRECTION = MOVE_UP;
			break;
		case(KEY_MOVE_FORWORD):
			DIRECTION = MOVE_UP;
			break;
		case(KEY_DOWN):
			DIRECTION = MOVE_DOWN;
			break;
		case(KEY_MOVE_BACKWORD):
			DIRECTION = MOVE_DOWN;
			break;
		default:
			break;
		}
	} else
		DIRECTION = 0;
		
}
void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Moving(int key, GLfloat deltaTime)
{
	//Handle player moving
	Vector2 oldPos = m_Player->Get2DPosition();//(x,y)
	if (key == KEY_RIGHT) {
		//m_hero->ChangeState(CharacterStateTypes::CHARACTER_STATE_Walk);
		int newPosX = oldPos.x - 8;
		//if (MAP_WIDTH / 2 + newPosX < screenWidth) {
		//newPosX = screenWidth - MAP_WIDTH / 2;
		/*Vector2 oldHeroPos = m_hero->Get2DPosition();
		m_hero->Set2DPosition(oldHeroPos.x + 16, oldHeroPos.y);*/
		m_Player->Set2DPosition(newPosX, oldPos.y);
	}
	else if (key == KEY_LEFT) {
		//m_hero->ChangeState(CharacterStateTypes::CHARACTER_STATE_Walk);
		int newPosX = oldPos.x + 8;
		//if (MAP_WIDTH / 2 - newPosX < 0)
		//newPosX = MAP_WIDTH / 2;
		m_Player->Set2DPosition(newPosX, oldPos.y);
	}
	else if (key == KEY_DOWN) {
		//m_hero->ChangeState(CharacterStateTypes::CHARACTER_STATE_Walk);
		int newPosY = oldPos.y + 8;
		//if (MAP_HEIGHT / 2 + newPosY < screenHeight)
		//newPosY = screenHeight - MAP_HEIGHT / 2;
		m_Player->Set2DPosition(oldPos.x, newPosY);
	}
	else if (key == KEY_UP) {
		//m_hero->ChangeState(CharacterStateTypes::CHARACTER_STATE_Walk);
		int newPosY = oldPos.y - 8;
		//if (MAP_HEIGHT / 2 - newPosY < 0)
		//newPosY = MAP_HEIGHT / 2;
		m_Player->Set2DPosition(oldPos.x, newPosY);
	}
}

void GSPlay::Update(float deltaTime)
{
	//Hanlde animation
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}
	//Hanlde background
	for (auto bg : m_listSprite2D)
	{
		bg->Update(deltaTime);
		bg->Set2DPosition(screenWidth / 2, bg->Get2DPosition().y + BACKGROUND_SPEED *deltaTime);
		if (bg->Get2DPosition().y >= screenHeight * 3 / 2) {
			bg->Set2DPosition(screenWidth / 2, bg->Get2DPosition().y - 2 * screenHeight);
		}
	}
	//Handle player moving
	if (DIRECTION)
	{
		Vector2 oldPos = m_Player->Get2DPosition();//(x,y)
		int newPosX;
		int newPosY;
		switch (DIRECTION)
		{
			case(MOVE_RIGHT):
			{
				if (oldPos.x >= screenWidth) {
					newPosX = oldPos.x;
				}
				else {
					newPosX = oldPos.x + PLAYER_SPEED * deltaTime;
				}
				m_Player->Set2DPosition(newPosX, oldPos.y);
				break;
			};

			case(MOVE_LEFT):
			{
				if (oldPos.x <= 0) {
					newPosX = oldPos.x;
				}
				else {
					newPosX = oldPos.x - PLAYER_SPEED * deltaTime;
				}
				m_Player->Set2DPosition(newPosX, oldPos.y);
				break;
			};

			case(MOVE_DOWN):
			{
				if (oldPos.y >= screenHeight) {
					newPosY = oldPos.y;
				}
				else {
					newPosY = oldPos.y + PLAYER_SPEED * deltaTime;
				}
				m_Player->Set2DPosition(oldPos.x, newPosY);
				break;
			};

			case(MOVE_UP):
			{
				if (oldPos.y <= 0) {
					newPosY = oldPos.y;
				}
				else {
					newPosY = oldPos.y - PLAYER_SPEED * deltaTime;
				}
				m_Player->Set2DPosition(oldPos.x, newPosY);
				break;
			};

			default:
				break;
		}
		m_Player->Update(deltaTime);
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
	m_Player->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}