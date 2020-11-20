#pragma once
#include "Sprite2D.h"
#include "GameStates\GameStatebase.h"
#include "Bullet.h"

class Enemy : public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model,
		std::shared_ptr<Shaders> shader,
		std::shared_ptr<Texture> texture);
	~Enemy();

	void Update(GLfloat deltaTime);

	Vector2 makeRandom();

	void Shoot(std::list<std::shared_ptr<Bullet>> listBullet, int damage);
	void BossShoot(std::list<std::shared_ptr<Bullet>> listBullet, int damage, GLfloat deltaTime, int direct);
	void Moving(GLfloat deltaTime);
	void FastMoving(GLfloat deltaTime);
	void Destroying(GLfloat deltaTime);
	void BossAttack(std::list<std::shared_ptr<Bullet>> listBullet, int damage, bool isLeftSide);

	GLfloat e_Cooldown;

	GLint GetSize();

	GLfloat timeExplose = 0;
	bool e_isActive;
	bool isBoss;
	bool isEnemyDestroy;
	int HP;
private:
	std::vector<std::shared_ptr<Sprite2D>> m_ListState;
	std::list < std::shared_ptr<Bullet>> listBullet;
};