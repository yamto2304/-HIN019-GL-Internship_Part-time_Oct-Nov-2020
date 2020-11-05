#include "Player.h"

extern int screenWidth; //need get on Graphic engine   ||480
extern int screenHeight; //need get on Graphic engine  ||800

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	/*m_pBtClick = nullptr;
	m_isHandle = false;*/
}


Player::~Player()
{
}

void Player::HandleKeyEvents(int key, bool bIsPressed)
{
	
}

void Player::Update(GLfloat deltaTime)
{
		
}

void Player::Moving(int key, GLfloat deltaTime) 
{
	
}