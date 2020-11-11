#pragma once
#include "Sprite2D.h"
#include "GameStates\GameStatebase.h"

enum EnemyState { INACTIVE, ACTIVE, DESTROYING};

class Enemy : public Sprite2D
{
public:
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~Enemy();

	void Update(GLfloat deltaTime);

	void ChangeEnemyState(EnemyState state);

	Vector2 makeRandom();

private:
	std::vector<std::shared_ptr<Sprite2D>> m_ListState;
	std::shared_ptr<Sprite2D> m_eActiveState;
};