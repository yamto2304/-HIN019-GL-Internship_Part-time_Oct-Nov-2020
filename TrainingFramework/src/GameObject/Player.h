#pragma once
#include "Sprite2D.h"

class Player : public Sprite2D
{
public:
	Player(std::shared_ptr<Models> model,
		std::shared_ptr<Shaders> shader, 
		std::shared_ptr<Texture> texture);
	~Player();

	//void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	void HandleKeyEvents(int key, bool bIsPressed);
	void Update(GLfloat deltaTime);
	//bool IsHandle();

private:
	//void(*m_pBtClick)();
	//bool	m_isHandle;
};

