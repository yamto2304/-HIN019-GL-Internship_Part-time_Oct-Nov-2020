#include "Player.h"

extern int screenWidth; //need get on Graphic engine   ||480
extern int screenHeight; //need get on Graphic engine  ||800

Player::Player(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader, 
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	p_Cooldown = PLAYER_COOLDOWN;
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

void Player::Shoot(std::list < std::shared_ptr<Bullet>> listBullet)
{
	Vector2 pos = Get2DPosition();
	for (auto bullet : listBullet) {
		if (bullet->IsActive() == false) {
			auto newTexture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
			bullet->SetTexture(newTexture);
			bullet->Set2DPosition(pos);
			bullet->m_isPlayer = true;
			bullet->m_isActive = true;
			printf("shot in player \n");
			return;
		}
	}
}

GLint Player::GetSize() {
	return PLAYER_SIZE;
}