#include "Enemy.h"

#include <cstdlib>
#include <ctime>

//#include "Singleton.h"

extern GLint screenWidth;
extern GLint screenHeight;

Enemy::Enemy(std::shared_ptr<Models> model,
	std::shared_ptr<Shaders> shader,
	std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	e_Cooldown = ENEMY_COOLDOWN;
	isEnemyDestroy = false;
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime) {
	
}

void Enemy::Shoot(std::list<std::shared_ptr<Bullet>> listBullet, int damage) {
	Vector2 pos = Get2DPosition();
	for (auto bullet : listBullet) {
		if (bullet->IsActive() == false){
			bullet->m_isActive = true;
			auto newTexture = ResourceManagers::GetInstance()->GetTexture("enemy_bullet");
			bullet->SetSize(10, 36);
			bullet->m_isBossBonus = false;
			if (isBoss) {
				newTexture = ResourceManagers::GetInstance()->GetTexture("bossbullet");
				bullet->SetSize(25, 50);
			}
			
			bullet->SetTexture(newTexture);
			bullet->Set2DPosition(pos.x, pos.y + ENEMY_SIZE);
			
			bullet->m_isPlayer = false;
			//bullet->m_isActive = true;
			bullet->damage = damage;
			break;
		}
	}
}

//BossShoot
void Enemy::BossShoot(std::list<std::shared_ptr<Bullet>> listBullet, int damage,GLfloat deltaTime, int direct) {
	Vector2 pos = Get2DPosition();
	
	for (auto bullet : listBullet) {
		auto newTexture = ResourceManagers::GetInstance()->GetTexture("bossbullet");
		//bullet->m_isBossBonus = true;
		bullet->m_isActive = true;
		bullet->SetTexture(newTexture);
		bullet->SetSize(25, 50); 
		GLfloat newPosX = pos.x + direct*deltaTime*ENEMY_BULLET_SPEED;
		bullet->Set2DPosition(newPosX, newPosX);
		break;
	}
}
//Basic enemy
void Enemy::Moving(GLfloat deltaTime) {
	if (e_isActive) {
		int direc = 1;
		//Handle moving random
		Vector2 oldPosEnemy = Get2DPosition();
		if (oldPosEnemy.y < -BULLET_SIZE || oldPosEnemy.y > screenHeight + BULLET_SIZE || oldPosEnemy.x < -BULLET_SIZE || oldPosEnemy.x > screenWidth + BULLET_SIZE) {

			Set2DPosition(0,0);
			e_isActive = true;
		}
		else {
			int newPosEnemyX = oldPosEnemy.x + direc * ENEMY_SPEED * deltaTime;
			int newPosEnemyY = newPosEnemyX*newPosEnemyX*newPosEnemyX - 12 * newPosEnemyX*newPosEnemyX + 47 * newPosEnemyX - 54;

			Vector2 p = makeRandom();
			//printf("%d %d \n", p.x, p.y);

			Set2DPosition(newPosEnemyX, newPosEnemyX);
		}

	}
}

//FastEnemy
void Enemy::FastMoving(GLfloat deltaTime) {
	if (e_isActive) {
		Vector2 oldPosEnemy = Get2DPosition();
		/*if (oldPosEnemy.y < -BULLET_SIZE || oldPosEnemy.y > screenHeight + BULLET_SIZE || oldPosEnemy.x < -BULLET_SIZE || oldPosEnemy.x > screenWidth + BULLET_SIZE) {

			Set2DPosition(ENEMY_GATE_1);

		}*/
		//else {
			int newPosEnemyX = oldPosEnemy.x + ENEMY_SPEED * deltaTime;
			int newPosEnemyY = newPosEnemyX*newPosEnemyX*newPosEnemyX - 12 * newPosEnemyX*newPosEnemyX + 47 * newPosEnemyX - 54;

			//printf("%d %d \n", p.x, p.y);

			Set2DPosition(newPosEnemyX, newPosEnemyX);
		//}
	}
}

//FastEnemy
void Enemy::BossAttack(std::list<std::shared_ptr<Bullet>> listBullet, int damage, bool isLeftSide) {
	Vector2 pos = Get2DPosition();
	for (auto bullet : listBullet) {
		if (bullet->IsActive() == false) {
			bullet->m_isPlayer = false;
			bullet->m_isActive = true;
			bullet->damage = damage;
			//bullet->m_isBossBonus = false;
			auto newTexture = ResourceManagers::GetInstance()->GetTexture("enemy_fast");
			bullet->SetSize(25, 50);
			
			bullet->SetTexture(newTexture);
			if (isLeftSide) {
				bullet->Set2DPosition(pos.x - 180, pos.y - 120);
				printf("shot left\n");
			}
			else {
				bullet->Set2DPosition(pos.x + 180, pos.y - 120);
				printf("shot right\n");
			}
			if (pos.y < -BULLET_SIZE || pos.y > screenHeight + BULLET_SIZE || pos.x < -BULLET_SIZE || pos.x > screenWidth + BULLET_SIZE) {
				bullet->Set2DPosition(BASE_BULLET_POSITION);
				bullet->m_isActive = false;
			}
			break;
		}
	}
}

void Enemy::Destroying(GLfloat deltaTime) {
	timeExplose += deltaTime;
	if (timeExplose > 2.0) {
		auto newTexture = ResourceManagers::GetInstance()->GetTexture("enemy");
		SetTexture(newTexture);
		Set2DPosition(screenWidth / 2, 250);
		isEnemyDestroy = false;
		e_isActive = true;
		timeExplose = 0;
	}
}

GLint Enemy::GetSize() {
	return ENEMY_SIZE;
}

Vector2 Enemy::makeRandom() {
	srand(time(NULL));
	return Vector2(rand() % 5 + 1,rand() % 5 + 1);
}

