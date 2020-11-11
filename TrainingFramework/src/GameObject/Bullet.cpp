#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_isActive = true;
}


Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltaTime)
{

}

//void Bullet::ChangeBulletState(int state)
//{
//	switch (state) {
//	case BINACTIVE:
//		bullet->Set2DPosition(300,100);
//		break;
//	case BACTIVE:
//	default:
//		break;
//	}
//}

bool Bullet::IsActive()
{
	return m_isActive;
}