#pragma once
#include "Sprite2D.h"
#include "Player.h"

//enum BulletState { BACTIVE, BINACTIVE};

class Bullet : public Sprite2D
{
public:
	Bullet(std::shared_ptr<Models> model,
		std::shared_ptr<Shaders> shader,
		std::shared_ptr<Texture> texture);
	~Bullet();
	void Update(GLfloat deltaTime);
	bool IsActive();
	bool IsPlayer();

	bool m_isActive;
	bool m_isPlayer;
	bool m_isFastShip;
	
	int GetSpeed();
	int GetSize();
	int damage;
//	void FastAttack(std::shared_ptr<Player> player, GLfloat deltaTime);
	void CheckPosition();
	//void ChangeBulletState(int state);

private:
	std::shared_ptr<Bullet> bullet;
	//std::shared_ptr<Player> player;
	
};
 
