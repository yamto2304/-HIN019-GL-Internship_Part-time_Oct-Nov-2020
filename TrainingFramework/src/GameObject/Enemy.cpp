#include "Enemy.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"
#include "Sprite2D.h"
#include <time.h>

//#include "Singleton.h"

extern GLint screenWidth;
extern GLint screenHeight;

Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	//std::shared_ptr<Texture> newTexture;
	//switch (state) {
	//case INACTIVE:
	//	newTexture = ResourceManagers::GetInstance()->GetTexture("enemy");
	//	//ChangeState(INACTIVE);
	//	SetSize(40, 40);
	//	break;
	//case ACTIVE:
	//	newTexture = ResourceManagers::GetInstance()->GetTexture("enemy");
	//	//ChangeState(ACTIVE);
	//	
	//	SetSize(40, 40);
	//	break;
	//case DESTROYING:
	//	newTexture = ResourceManagers::GetInstance()->GetTexture("explosion");
	//	//ChangeState(DESTROYING);
	//	
	//	SetSize(40, 40);
	//	break;
	//default:
	//	break;
	//}
	//SetTexture(newTexture);
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime) {
	m_eActiveState->Update(deltaTime);
}

void Enemy::ChangeEnemyState(EnemyState state) {
	switch (state) {
	case INACTIVE:
		m_eActiveState = m_ListState[0];
		break;
	case ACTIVE:
		m_eActiveState = m_ListState[1];
		break;
	case DESTROYING:
		m_eActiveState = m_ListState[2];
		break;
	default:
		break;
	}
}

Vector2 Enemy::makeRandom() {
	srand((unsigned)time(0));
	return Vector2(900 + rand() % 400, 370);
}