#include "Bullet.h"

#include "Player.h"
#include "Enemy.h"

extern int screenWidth; //need get on Graphic engine   ||480
extern int screenHeight; //need get on Graphic engine  ||700


Bullet::Bullet(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{

}


Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltaTime)
{
	/*std::shared_ptr<Player> player;
	if (m_isFastShip && m_isActive) {
		FastAttack(player, deltaTime);
	}*/
}

//void Bullet::FastAttack(std::shared_ptr<Player> player, GLfloat deltaTime) {
//	Vector2 pos = Get2DPosition();
//	Vector2 pPos = player->Get2DPosition();
//	GLfloat direct = abs((pPos.y - pos.y) / (pPos.x - pos.x));
//
//	GLfloat newPosX = pos.x + GetSpeed()*deltaTime;
//	Set2DPosition(newPosX, direct * newPosX);
//
//	if (pos.y < -BULLET_SIZE || pos.y > screenHeight + BULLET_SIZE || pos.x < -BULLET_SIZE || pos.x > screenWidth + BULLET_SIZE) {
//		Set2DPosition(BASE_BULLET_POSITION);
//		m_isActive = false;
//	}
//}

int Bullet::GetSpeed() {
	if (m_isPlayer)
		return PLAYER_BULLET_SPEED;
	return ENEMY_BULLET_SPEED;
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


