#include "Enemy.h"


#include <time.h>

//#include "Singleton.h"

extern GLint screenWidth;
extern GLint screenHeight;

Enemy::Enemy(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	e_Cooldown = ENEMY_COOLDOWN;
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime) {
	/*if (e_Cooldown <= 0) {
		Shoot();
		e_Cooldown = 0.5f;
	}
	else {
		e_Cooldown -= deltaTime;
	}*/
}

void Enemy::Shoot(std::list<std::shared_ptr<Bullet>> listBullet, std::list<std::shared_ptr<Bullet>> listActiveBullet) {
	Vector2 pos = Get2DPosition();

	for (auto bullet : listBullet) {
			auto newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
			bullet->SetTexture(newTexture);
			bullet->Set2DPosition(pos);
			bullet->m_isPlayer = false;
			//bullet->m_isActive = true;
			
			listActiveBullet.push_back(bullet);
			//listBullet.pop_back(bullet);
			break;
			//}
	}
}

GLint Enemy::GetSize() {
	return ENEMY_SIZE;
}

Vector2 Enemy::makeRandom() {
	srand((unsigned)time(0));
	return Vector2(900 + rand() % 400, 370);
}

