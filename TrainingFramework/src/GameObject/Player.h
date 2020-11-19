#pragma once
#include "Sprite2D.h"
#include "GameStates\GameStatebase.h"
#include "Bullet.h"

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model,
		std::shared_ptr<Shaders> shader, 
		std::shared_ptr<Texture> texture);
	~Player();

	GLint GetSize();

	void HandleKeyEvents(int key, bool bIsPressed);
	void Update(GLfloat deltaTime);
	
	GLfloat p_Cooldown;
	void Shoot(std::list < std::shared_ptr<Bullet>> listBullet, int damage);
	bool isActive;
	int HP;
private:
	std::list < std::shared_ptr<Bullet>> listBullet;
};

