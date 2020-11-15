#pragma once
#include "Sprite2D.h"
#include "GameStates\GameStatebase.h"
#include "Bullet.h"

enum EnemyState { INACTIVE, ACTIVE, DESTROYING};

class Enemy : public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model,
		std::shared_ptr<Shaders> shader,
		std::shared_ptr<Texture> texture);
	~Enemy();

	void Update(GLfloat deltaTime);

	Vector2 makeRandom();

	void Shoot(std::list<std::shared_ptr<Bullet>> listBullet, std::list<std::shared_ptr<Bullet>> listActiveBullet);

	GLfloat e_Cooldown;

	GLint GetSize();
private:
	std::vector<std::shared_ptr<Sprite2D>> m_ListState;
	std::list < std::shared_ptr<Bullet>> listBullet;
	std::list < std::shared_ptr<Bullet>> listActiveBullet;
};