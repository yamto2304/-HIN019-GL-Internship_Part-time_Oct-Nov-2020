#pragma once
#include "Sprite2D.h"

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
	
	int GetSpeed();
	int GetSize();

	//void ChangeBulletState(int state);

private:
	std::shared_ptr<Bullet> bullet;
	
};
 
