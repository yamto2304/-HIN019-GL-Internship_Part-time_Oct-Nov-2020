#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "GameButton.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

#include "soloud.h"
#include "soloud_wav.h"

#include "stdio.h"

int DIRECTION = 0;
float timeAction = 0;
float m_time = 0;
bool isEnemyDestroy = false;

extern int screenWidth; //need get on Graphic engine   ||480
extern int screenHeight; //need get on Graphic engine  ||700

std::shared_ptr<Texture> newTexture;

GSPlay::GSPlay()
{
}

GSPlay::~GSPlay()
{

}

bool GSPlay::CheckCollision(std::shared_ptr<Sprite2D> obj1, std::shared_ptr<Sprite2D> obj2)
{
    
    // Set player hit box
    /*GLint x1p = player->Get2DPosition().x - PLAYER_SIZE / 2;
        GLint x2p = player->Get2DPosition().x + PLAYER_SIZE / 2;
        GLint y1p = player->Get2DPosition().y - PLAYER_SIZE / 2;
        GLint y2p = player->Get2DPosition().y + PLAYER_SIZE / 2;*/

    //Set enemy hitbox
    /*GLint x1e = enemy->Get2DPosition().x - ENEMY_SIZE / 2;
    GLint x2e = enemy->Get2DPosition().x + ENEMY_SIZE / 2;
    GLint y1e = enemy->Get2DPosition().y - ENEMY_SIZE / 2;
    GLint y2e = enemy->Get2DPosition().y + ENEMY_SIZE / 2;*/

    // Set bullet hit box
    /*GLint x1b = bullet->Get2DPosition().x - BULLET_SIZE / 2;
    GLint x2b = bullet->Get2DPosition().x + BULLET_SIZE / 2;
    GLint y1b = bullet->Get2DPosition().y - BULLET_SIZE / 2;
    GLint y2b = bullet->Get2DPosition().y + BULLET_SIZE / 2;*/

	Vector2 pos1 = obj1->Get2DPosition();
	Vector2 pos2 = obj2->Get2DPosition();
	
	//int distance = (sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y))
	if (( sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <= obj1->GetSize() + obj2->GetSize())) {
		return 1;
	}

    return 0;
}



void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg1");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
     //BackGround
    {
        m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
        m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
        m_BackGround->SetSize(screenWidth, screenHeight);
        m_listSprite2D.push_back(m_BackGround);

        m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
        m_BackGround->Set2DPosition(screenWidth * 3 / 2, screenHeight * 3 / 2);
        m_BackGround->SetSize(screenWidth, screenHeight);
        m_listSprite2D.push_back(m_BackGround);

		ResourceManagers::GetInstance()->PlaySound("bground");
    }

    //Player
    {
        texture = ResourceManagers::GetInstance()->GetTexture("shipfinal");
        m_Player = std::make_shared<Player>(model, shader, texture);
        m_Player->Set2DPosition(screenWidth / 2, 500);
        m_Player->SetSize(152, 152);
		m_Player->p_Cooldown = 0;
    }

    //InitBullet
    {
   //     for (int i = 1; i < 3; i++) {
   //         texture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
   //         m_Bullet = std::make_shared<Bullet>(model, shader, texture);
			//m_Bullet->Set2DPosition(100, 100);
   //         //m_Bullet->Set2DPosition(m_Player->Get2DPosition().x, m_Player->Get2DPosition().y - 75);
   //         m_Bullet->SetSize(40, 40);
   //         m_Bullet->m_isActive = false;
   //         m_listBullet.push_back(m_Bullet);
   //     }
    }

    //Enemy
    {
        texture = ResourceManagers::GetInstance()->GetTexture("enemy");
        m_Enemy = std::make_shared<Enemy>(model, shader, texture);
        m_Enemy->Set2DPosition(screenWidth / 2, 250);
        m_Enemy->SetSize(40, 40);
    }

    //back button
    {
        texture = ResourceManagers::GetInstance()->GetTexture("btn_home");
        std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
        button->Set2DPosition(screenWidth / 6, 50);
        button->SetSize(100, 75);
        button->SetOnClick([]() {
            GameStateMachine::GetInstance()->PopState();
            });
        m_listButton.push_back(button);
    }

    //text game title
    {
        shader = ResourceManagers::GetInstance()->GetShader("TextShader");
        std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

        m_score = std::make_shared< Text>(shader, font, "score: 10000", TEXT_COLOR::RED, 1.0);
        m_score->Set2DPosition(Vector2(5, 25));
    }

    // Animation
    {
        shader = ResourceManagers::GetInstance()->GetShader("Animation");
        texture = ResourceManagers::GetInstance()->GetTexture("coin1");
        std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.1f);
        obj->Set2DPosition(240, 400);
        obj->SetSize(152, 152);
        m_listSpriteAnimations.push_back(obj);
    }
    
}

//nothing
void GSPlay::Exit()
{
    
}
//nothing
void GSPlay::Pause()
{

}
//nothing
void GSPlay::Resume()
{

}
//nothing
void GSPlay::HandleEvents()
{

}


void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
    if (bIsPressed)
    {
        switch (key)
        {
        case(KEY_RIGHT):
        case(KEY_MOVE_RIGHT):
            DIRECTION |= MOVE_RIGHT;
            break;
        case(KEY_LEFT) :
        case(KEY_MOVE_LEFT):
            DIRECTION |= MOVE_LEFT;
            break;

        case(KEY_UP):
        case(KEY_MOVE_FORWORD):
            DIRECTION |= MOVE_UP;
            break;

        case(KEY_DOWN):
        case(KEY_MOVE_BACKWORD):
            DIRECTION |= MOVE_DOWN;
            break;
        default:
            break;
        }
    } else
        switch (key)
        {
        case(KEY_RIGHT):
        case(KEY_MOVE_RIGHT):
            DIRECTION ^= MOVE_RIGHT;
            break;
        case(KEY_LEFT):
        case(KEY_MOVE_LEFT):
            DIRECTION ^= MOVE_LEFT;
            break;

        case(KEY_UP):
        case(KEY_MOVE_FORWORD):
            DIRECTION ^= MOVE_UP;
            break;

        case(KEY_DOWN):
        case(KEY_MOVE_BACKWORD):
            DIRECTION ^= MOVE_DOWN;
            break;
        default:
            break;
        }
        
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
    for (auto it : m_listButton)
    {
        (it)->HandleTouchEvents(x, y, bIsPressed);	
        if ((it)->IsHandle()) break;
    }
}

void GSPlay::Update(float deltaTime)
{
	//Hanlde animation
	{
		for (auto obj : m_listSpriteAnimations)
		{
			obj->Update(deltaTime);
		}
	}

	//Hanlde background moving
	for (auto bg : m_listSprite2D)
	{
		bg->Update(deltaTime);
		bg->Set2DPosition(screenWidth / 2, bg->Get2DPosition().y + BACKGROUND_SPEED *deltaTime);
		if (bg->Get2DPosition().y >= screenHeight * 3 / 2) {
			bg->Set2DPosition(screenWidth / 2, bg->Get2DPosition().y - 2 * screenHeight);//hard code
		}
	}

	//Handle player moving
	if (DIRECTION)
	{
		Vector2 oldPos = m_Player->Get2DPosition();//(x,y)
		int newPosX;
		int newPosY;
		switch (DIRECTION)
		{
		case(MOVE_RIGHT):
		{
			if (oldPos.x >= screenWidth) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x + PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(newPosX, oldPos.y);
			break;
		};
		case(MOVE_LEFT):
		{
			if (oldPos.x <= 0) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x - PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(newPosX, oldPos.y);
			break;
		};
		case(MOVE_DOWN):
		{
			if (oldPos.y >= screenHeight) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y + PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(oldPos.x, newPosY);
			break;
		};
		case(MOVE_UP):
		{
			if (oldPos.y <= 0) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y - PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(oldPos.x, newPosY);
			break;
		};
		case(MOVE_LEFT_UP):
		{
			//UP
			if (oldPos.y <= 0) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y - PLAYER_SPEED * deltaTime;
			}

			//LEFT
			if (oldPos.x <= 0) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x - PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(newPosX, newPosY);
			break;
		}
		case(MOVE_LEFT_DOWN):
		{
			//LEFT
			if (oldPos.x <= 0) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x - PLAYER_SPEED * deltaTime;
			}
			//DOWN
			if (oldPos.y >= screenHeight) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y + PLAYER_SPEED * deltaTime;
			}

			m_Player->Set2DPosition(newPosX, newPosY);
			break;
		}
		case(MOVE_RIGHT_UP):
		{
			//UP
			if (oldPos.y <= 0) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y - PLAYER_SPEED * deltaTime;
			}
			//RIGHT
			if (oldPos.x >= screenWidth) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x + PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(newPosX, newPosY);
			break;
		}
		case(MOVE_RIGHT_DOWN):
		{
			//DOWN
			if (oldPos.y >= screenHeight) {
				newPosY = oldPos.y;
			}
			else {
				newPosY = oldPos.y + PLAYER_SPEED * deltaTime;
			}
			//RIGHT
			if (oldPos.x >= screenWidth) {
				newPosX = oldPos.x;
			}
			else {
				newPosX = oldPos.x + PLAYER_SPEED * deltaTime;
			}
			m_Player->Set2DPosition(newPosX, newPosY);
			break;
		}
		default:
			break;
		}
		m_Player->Update(deltaTime);
	}

	//Handle enemy moving
	{
		//int enemyDirX = rand() % 10;
		//int enemyDirY = rand() % 10;
		//Vector2 oldPosEnemy = m_Enemy->Get2DPosition();
		//int newPosEnemyX = oldPosEnemy.x + ENEMY_SPEED * enemyDirX * deltaTime / 20;
		//int newPosEnemyY = oldPosEnemy.y + ENEMY_SPEED * enemyDirY * deltaTime / 20;
		//m_Enemy->Set2DPosition(newPosEnemyX, newPosEnemyY);
	}

	//Player shooting
	if (m_Player->p_Cooldown <= 0) {
		Vector2 pPos = m_Player->Get2DPosition();
		//m_Player->Shoot;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto newTexture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
		m_Bullet = std::make_shared<Bullet>(model, shader, newTexture);
		m_Bullet->m_isPlayer = true;
		m_Bullet->m_isActive = true;
		m_Bullet->Set2DPosition(pPos);
		m_Bullet->SetSize(40, 40);
		m_listBullet.push_back(m_Bullet);

		m_Player->p_Cooldown = PLAYER_COOLDOWN;
		printf("shoot \n");
	}
	else {
		m_Player->p_Cooldown -= deltaTime;
		printf("cooldown \n");
	}

	for (auto bullet : m_listBullet) {
		
		/*if (bullet->IsActive() == true) {
			Vector2 pos = bullet->Get2DPosition();
			pos.y = pos.y + deltaTime*(bullet->GetSpeed());
			bullet->Set2DPosition(pos);
		}*/
		bullet->Update(deltaTime);
	}

		// for (auto bullet : m_listBullet)
		// {
		//     //for (auto enemy : m_listEnemy) {
	 //            m_Bullet->Update(deltaTime);
				 //Vector2 oldPosBullet = bullet->Get2DPosition();
				 //Vector2 oldPosB = bullet->Get2DPosition();
		//         if (bullet->IsActive() && CheckCollision(bullet, m_Enemy) && !isEnemyDestroy)
		//         {

		//            // bullet->m_isActive = false;
		//             bullet->Set2DPosition(240, 500);
				 //	//ResourceManagers::GetInstance()->PlaySound("fire");
				 //	//bullet->m_isActive = true;
				 //	
		//         }
				 //else if (oldPosB.y < 0) {
				 //	bullet->Set2DPosition(240, 500);
				 //	bullet->m_isActive = true;
				 //}
		//         else {
		//             
		//             int newPosBulletY = oldPosB.y - BULLET_SPEED * deltaTime / 2;

		//             bullet->Set2DPosition(oldPosB.x, newPosBulletY);
		//         }
		//         
		//     //}
		// }

		 //Handle enemy state

		//m_Enemy->Update(deltaTime);
		/*for (auto bullet : m_listActiveBullet) {
			if (bullet->IsActive()) {
				Vector2 pos = bullet->Get2DPosition();
				pos.y = pos.y + bullet->GetSpeed() * deltaTime / 2;
				bullet->Set2DPosition(pos);
				printf("fire \n");
			}
			bullet->Update(deltaTime);
		}*/

		/*if (m_Enemy->e_Cooldown <= 0) {
			m_Enemy->Shoot(m_listBullet, m_listActiveBullet);
			m_Enemy->e_Cooldown = ENEMY_COOLDOWN;
			printf("shot \n");
		}
		else {
			m_Enemy->e_Cooldown -= deltaTime;
			printf("cooldown \n");
		}*/

		//m_Enemy->Shoot(m_listBullet);

	  //  if (CheckCollision(m_Bullet, m_Enemy) && !isEnemyDestroy)
	  //  {
	  //      newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
			//ResourceManagers::GetInstance()->PlaySound("fire");
	  //      //m_Enemy->ChangeEnemyState(DESTROYING);
	  //      m_Enemy->SetTexture(newTexture);
	  //      isEnemyDestroy = true;
	  //  };
	  //  if (isEnemyDestroy) {
	  //      m_time += deltaTime;
	  //      if (m_time > 0.5) {
	  //          newTexture = ResourceManagers::GetInstance()->GetTexture("enemy");
	  //          m_Enemy->SetTexture(newTexture);
	  //          m_Enemy->Set2DPosition(screenWidth / 2, 250);
			//	isEnemyDestroy = false;
	  //          m_time = 0;
	  //      }
	  //  }
	
}

void GSPlay::Draw()
{
    //Background
    for (auto back_ground : m_listSprite2D)
    {
        back_ground->Draw();
    }
    //button
    for (auto it : m_listButton)
    {
        it->Draw();
    }
    //animation
    /*for (auto obj : m_listSpriteAnimations)
    {
        obj->Draw();
    }*/

    m_score->Draw();

    m_Player->Draw();

    m_Enemy->Draw();

    m_Bullet->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}