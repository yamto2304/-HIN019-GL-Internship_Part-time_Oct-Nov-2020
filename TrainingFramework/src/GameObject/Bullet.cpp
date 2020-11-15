#include "Bullet.h"



#include "Player.h"
#include "Enemy.h"


Bullet::Bullet(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	/*m_isActive = true;
	m_isPlayer = true;*/
	std::shared_ptr<Texture> newTexture;
	/*if (IsPlayer()) {
		newTexture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
	}
	else
	{
		newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
	}
	SetTexture(newTexture);*/
}


Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltaTime)
{
	if (IsActive()) {
		Vector2 pos = Get2DPosition();
		pos.y = pos.y + GetSpeed() * deltaTime;
		Set2DPosition(pos);
	}
}


bool Bullet::IsActive()
{
	return m_isActive;
}

bool Bullet::IsPlayer()
{
	return m_isPlayer;
}

int Bullet::GetSize() {
	return BULLET_SIZE;
}

int Bullet::GetSpeed() {
	if (m_isPlayer)
		return PLAYER_BULLET_SPEED;
	return ENEMY_BULLET_SPEED;
}