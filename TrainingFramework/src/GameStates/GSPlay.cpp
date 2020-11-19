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
GLfloat CD = 1.0;
//float timeAction = 0;
float m_timeExplose = 0;

extern int score = 0;
extern bool isPlayingMusic  = true;
bool BossMode = false;
bool GameOver = false;

GLfloat fastAttackCD = 0;
//bool isEnemyDestroy = false;

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
	Vector2 pos1 = obj1->Get2DPosition();
	Vector2 pos2 = obj2->Get2DPosition();
	if (( sqrt((pos1.x - pos2.x)*(pos1.x - pos2.x) + (pos1.y - pos2.y)*(pos1.y - pos2.y)) <= obj1->GetSize() + obj2->GetSize())) {
		return 1;
	}
    return 0;
}


void GSPlay::Init()
{
	score = 0;
	CD = 1.50;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg1");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto shaderText = ResourceManagers::GetInstance()->GetShader("TextShader");
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

		if (isPlayingMusic) {
			if(!BossMode)
				ResourceManagers::GetInstance()->PlaySound("bground", true);
			else 
				ResourceManagers::GetInstance()->PlaySound("bgboss", true);
		}
		
		ResourceManagers::GetInstance()->PauseSound("mainmenu");

    }

    //Player
    {
        texture = ResourceManagers::GetInstance()->GetTexture("shipfinal");
        m_Player = std::make_shared<Player>(model, shader, texture);
        m_Player->Set2DPosition(screenWidth / 2, 500);
        m_Player->SetSize(75, 75);
		m_Player->isActive = true;
    }

    //InitBullet
    {
        for (int i = 1; i < 30; i++) {
            texture = ResourceManagers::GetInstance()->GetTexture("player_bullet");
            m_Bullet = std::make_shared<Bullet>(model, shader, texture);
			m_Bullet->Set2DPosition(BASE_BULLET_POSITION);
            m_Bullet->SetSize(40, 40);
            m_Bullet->m_isActive = false;
            m_listBullet.push_back(m_Bullet);
        }
    }
	
    //BasicEnemy
    {
		for (int i = 1; i < 2; i++) {
			texture = ResourceManagers::GetInstance()->GetTexture("enemy");
			m_Enemy = std::make_shared<Enemy>(model, shader, texture);
			m_Enemy->Set2DPosition(BASE_ENEMY_POSITION);
			m_Enemy->SetSize(40, 40);
			m_Enemy->e_isActive = true;
			m_Enemy->isBoss = false;
			m_Enemy->HP = HP_ENEMY_BASIC;
			m_listEnemy.push_back(m_Enemy);
		}
    }
	//FastEnemy
	{
		for (int i = 1; i < 11; i++) {
			texture = ResourceManagers::GetInstance()->GetTexture("enemy_fast");
			m_FastEnemy = std::make_shared<Bullet>(model, shader, texture);
			m_FastEnemy->Set2DPosition(100, 400);
			m_FastEnemy->SetSize(35, 70);
			m_FastEnemy->m_isActive = false;
			m_FastEnemy->m_isPlayer = false;
			m_FastEnemy->m_isFastShip = true;
			m_listFastEnemy.push_back(m_FastEnemy);
		}
	}
	//Boss 
	{
		texture = ResourceManagers::GetInstance()->GetTexture("boss_ship2");
		Boss = std::make_shared<Enemy>(model, shader, texture);
		Boss->Set2DPosition(240, -200);
		Boss->SetSize(180, 180);
		Boss->e_isActive = false;
		Boss->isBoss = true;
		Boss->HP = 25;
	}
    //back button
    {
        texture = ResourceManagers::GetInstance()->GetTexture("button");
        std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
        button->Set2DPosition(screenWidth / 6, 50);
		button->SetSize(150, 50);
        button->SetOnClick([]() {
			ResourceManagers::GetInstance()->PauseSound("bground");
			BossMode = false;
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
            });
        m_listButton.push_back(button);

		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_text = std::make_shared< Text>(shaderText, font, "MENU", TEXT_COLOR::WHILE, 0.8);
		m_text->Set2DPosition(screenWidth / 6 - 35, 55);
		m_listText.push_back(m_text);
    }
	//HP
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth / 6, 650);
		button->SetSize(150, 50);
		m_listButton.push_back(button);

		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_HP = std::make_shared< Text>(shaderText, font, "HP: " + std::to_string(m_Player->HP), TEXT_COLOR::WHILE, 0.8);
		m_HP->Set2DPosition(screenWidth / 6 - 40, 655);
		//m_listText.push_back(m_text);
	}
	////Score
	{
		texture = ResourceManagers::GetInstance()->GetTexture("button");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(5 * screenWidth / 6 - 5, 650);
		button->SetSize(150, 50);
		
		m_listButton.push_back(button);

		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
		m_score = std::make_shared< Text>(shaderText, font, "Score: " + 0, TEXT_COLOR::WHILE, 0.8);
		m_score->Set2DPosition(5 * screenWidth / 6 - 35, 655);
		//m_listText.push_back(m_text);
	}
    //text game title
    //{
    //    shader = ResourceManagers::GetInstance()->GetShader("TextShader");
    //    std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

    //    m_score = std::make_shared< Text>(shader, font, "Score:" + 0, TEXT_COLOR::RED, 1.0);
    //    m_score->Set2DPosition(Vector2(5, 25));
    //}

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

	//score
	m_score->setText("Score: " + std::to_string(score));
	m_score->Update(deltaTime);
	m_HP->setText("HP: " + std::to_string(m_Player->HP));
	m_HP->Update(deltaTime);

	//Player shooting
	{
		if (m_Player->p_Cooldown <= 0) {
			//m_Player->Shoot(m_listBullet, PLAYER_DAMAGE);
			if (isPlayingMusic) {
				ResourceManagers::GetInstance()->PlaySound("fire");
			}
			m_Player->p_Cooldown = PLAYER_COOLDOWN;
			//printf("player shot \n");
		}
		else {
			m_Player->p_Cooldown -= deltaTime;
			//printf("player cooldown \n");
		}
	}
	//Player colision
	//Vs Bullet
	for (auto bullet : m_listBullet) {
		if (bullet->IsActive() && CheckCollision(bullet, m_Player) && bullet->m_isPlayer == false) {
			bullet->m_isActive = false;
			bullet->Set2DPosition(BASE_BULLET_POSITION);
			m_Player->HP -= bullet->damage;
			printf(" player hp = %d \n", m_Player->HP);
		}
	}
	//Vs fast enemy
	for (auto bullet : m_listFastEnemy) {
		if (bullet->IsActive() && CheckCollision(bullet, m_Player) && bullet->m_isPlayer == false) {
			bullet->m_isActive = false;
			bullet->Set2DPosition(BASE_BULLET_POSITION);
			m_Player->HP -= bullet->damage;
			printf(" player hp = %d \n", m_Player->HP);
		}
	}
	//Vs basic enemy
	for (auto enemy : m_listEnemy) {
		if (enemy->e_isActive && CheckCollision(enemy, m_Player)) {
			//enemy->Set2DPosition(BASE_ENEMY_POSITION);
			m_Player->HP -= 5;
			printf(" player hp = %d \n", m_Player->HP);
			newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
			if (isPlayingMusic) {
				ResourceManagers::GetInstance()->PlaySound("bossshoot");
			}
			enemy->SetTexture(newTexture);
			enemy->isEnemyDestroy = true;
			enemy->e_isActive = false;
			enemy->HP = HP_ENEMY_BASIC;
			score += 13;
		}
	}
	//GameOver
		if (m_Player->HP <= 0) {
			m_Player->isActive = false;
			newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
			m_Player->SetTexture(newTexture);
			//if (m_Player->isActive) {
			if (isPlayingMusic && m_Player->isActive) {
				ResourceManagers::GetInstance()->PlaySound("bossshoot");
				m_Player->isActive = false;
			}
			if (CD <= 0) {
				BossMode = false;
				m_Player->HP = HP_PLAYER;
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
				m_Player->isActive = true;
				CD = 1.0;
			}
			else {
				CD -= deltaTime;
				//printf("cooldown \n");
			}
		}
	
	//basic enemy shooting
	{
		for (auto enemy : m_listEnemy) {
			if (enemy->e_isActive) {
				enemy->Moving(deltaTime);
				if (enemy->e_Cooldown <= 0) {
					enemy->Shoot(m_listBullet, DAMAGE_ENEMY_BASIC);
					//enemy->BossAttack(m_listFastEnemy, 5, false);
					enemy->e_Cooldown = ENEMY_COOLDOWN;
					//printf("shot \n");
				}
				else {
					enemy->e_Cooldown -= deltaTime;
					//printf("cooldown \n");
				}
			}
		}
	}

	//Handle bullet move and colision
	//Boss
	for (auto bullet : m_listBullet) {
		if (bullet->m_isActive == true && CheckCollision(bullet, Boss) == true && Boss->e_isActive == true && bullet->IsPlayer())
		{
			Boss->HP -= bullet->damage;
			if (isPlayingMusic) {
				ResourceManagers::GetInstance()->PlaySound("bossshoot");
			}
			bullet->m_isActive = false;
			bullet->Set2DPosition(BASE_BULLET_POSITION);
			//
			printf("hp = %d \n", Boss->HP);
			if (Boss->HP <= 0) {
				newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
				if (isPlayingMusic) {
					ResourceManagers::GetInstance()->PlaySound("explosion");
				}
				Boss->SetTexture(newTexture);
				Boss->e_isActive = false;
				Boss->isEnemyDestroy = true;
				//Boss->HP = HP_ENEMY_BASIC;
				score += 50;
				
				if (CD <= 0) {
					GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
				}
				else {
					CD -= deltaTime;
					//printf("cooldown \n");
				}
				
			}

		}
	}
	if (Boss->isEnemyDestroy) {
		if (CD <= 0) {
			BossMode = false;
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_GameOver);
		}
		else {
			CD -= deltaTime;
			//printf("cooldown \n");
		}
	}
	for (auto bullet : m_listBullet) {
		if (bullet->IsActive()) {
			Vector2 posBullet = bullet->Get2DPosition();
			posBullet.y = posBullet.y + bullet->GetSpeed() * deltaTime;
			bullet->Set2DPosition(posBullet);
			//bullet->CheckPosition();
			if (posBullet.y < -BULLET_SIZE || posBullet.y > screenHeight + BULLET_SIZE || posBullet.x < -BULLET_SIZE || posBullet.x > screenWidth + BULLET_SIZE) {
				bullet->Set2DPosition(BASE_BULLET_POSITION);
				bullet->m_isActive = false;
			}

			//printf("fire \n");
		}
		bullet->Update(deltaTime);
		//colision
		for (auto enemy : m_listEnemy) {
			enemy->Update(deltaTime);
			if (bullet->IsPlayer() && CheckCollision(bullet, enemy) && enemy->e_isActive) 
			{
				enemy->HP -= bullet->damage;
				bullet->m_isActive = false;
				bullet->Set2DPosition(BASE_BULLET_POSITION);
				if (isPlayingMusic) {
					ResourceManagers::GetInstance()->PlaySound("fire");
				}
				//printf( " %d \n", enemy->HP);
				if (enemy->HP <= 0) {
					newTexture = ResourceManagers::GetInstance()->GetTexture("exfinal");
					if (isPlayingMusic) {
						ResourceManagers::GetInstance()->PlaySound("bossshoot");
					}
					enemy->SetTexture(newTexture);
					enemy->isEnemyDestroy = true;
					enemy->e_isActive = false;
					enemy->HP = HP_ENEMY_BASIC;
					score+=13;
				}
				
			};

		if (enemy->isEnemyDestroy)
			{
				enemy->Destroying(deltaTime);
			}
		}
	}
		
	//Boss mode
	if (score == 26) {
		BossMode = true;
		
		//ResourceManagers::GetInstance()->PlaySound("bgboss", true);
		for (auto enemy : m_listEnemy)
		{
			enemy->e_isActive = false;
			enemy->Destroying(deltaTime);
		}
		Vector2 bossPos = Boss->Get2DPosition();
		if (bossPos.y <= 100) 
		{
			Boss->e_isActive = false;
			Boss->Set2DPosition(bossPos.x, bossPos.y + ENEMY_SPEED*deltaTime);
		}
		else {
			Boss->e_isActive = true;
			score++;
		}
	}

	//Boss shoot
	if (Boss->e_isActive) 
	{
			if (Boss->e_Cooldown <= 0) {
				Boss->Shoot(m_listBullet, DAMAGE_BOSS);
				/*if (isPlayingMusic) {
					ResourceManagers::GetInstance()->PlaySound("bossshoot");
				}*/
				if (Boss->Get2DPosition().y >= 50) {
					Boss->BossAttack(m_listFastEnemy, 5, true);
					Boss->BossAttack(m_listFastEnemy, 5, false);
				}
				
				Boss->e_Cooldown = ENEMY_COOLDOWN;
				//printf("shot \n");
			}
			else {
				Boss->e_Cooldown -= deltaTime;
				//printf("cooldown \n");
			}
	}
	Boss->Update(deltaTime);	

	for (auto enemy : m_listFastEnemy)
		enemy->Update(deltaTime);
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
	m_HP->Draw();
    m_Player->Draw();
	Boss->Draw();

	for (auto fastEnemy : m_listFastEnemy) {
		fastEnemy->Draw();
	}

	for (auto enemy : m_listEnemy) {
		enemy->Draw();
	}

	for (auto bullet : m_listBullet) {
		bullet->Draw();
	}

	for (auto text : m_listText) {
		text->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}