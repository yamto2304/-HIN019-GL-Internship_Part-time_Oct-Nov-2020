#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void SetNewPostionForBullet();

	bool CheckCollision(std::shared_ptr<Sprite2D> obj1, std::shared_ptr<Sprite2D> obj2);

	

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Enemy> Boss;
	
	std::shared_ptr<Enemy> m_Enemy;
	std::shared_ptr<Bullet> m_FastEnemy;
	std::shared_ptr<Bullet> m_Bullet;

	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Text>  m_text;

	std::list<std::shared_ptr<GameButton>>	m_listButton;

	std::list < std::shared_ptr<Enemy>> m_listEnemy;
	std::list < std::shared_ptr<Bullet>> m_listFastEnemy;
	std::list < std::shared_ptr<Bullet>> m_listBullet;
	std::list < std::shared_ptr<Text>> m_listText;

	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;

};

