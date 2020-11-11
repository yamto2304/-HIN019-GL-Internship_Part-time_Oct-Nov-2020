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
	bool m_isActive;

	//void ChangeBulletState(int state);

private:
	//std::shared_ptr<Sprite2D> bullet;
	
};
 
