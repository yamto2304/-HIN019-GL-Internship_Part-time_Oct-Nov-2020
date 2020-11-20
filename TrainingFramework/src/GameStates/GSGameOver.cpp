#include "GSGameOver.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int score;
extern int highscore;

GSGameOver::GSGameOver()
{
}


GSGameOver::~GSGameOver()
{
}

void GSGameOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture
	("highscore");
	auto shaderText = ResourceManagers::GetInstance()->GetShader("TextShader");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(400, 400);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 50);
	button->SetSize(150, 50);
	button->SetOnClick([]() {
		ResourceManagers::GetInstance()->PauseSound("bground");
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
	});
	m_listButton.push_back(button);

	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("ariblk");
	m_text = std::make_shared< Text>(shaderText, font, "MENU", TEXT_COLOR::WHILE, 0.8);
	m_text->Set2DPosition(screenWidth / 2 - 35, 55);
	//m_listText.push_back(m_text);
	
	//m_listButton.push_back(button);
	//title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	if (score > highscore) {
		highscore = score;
		title = std::make_shared< Text>(shader, font, "High Score:", TEXT_COLOR::RED, 1.5);
	}
	else {
		title = std::make_shared< Text>(shader, font, "Your Score:", TEXT_COLOR::RED, 1.5);
	}
	//title = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 3.0);
	title->Set2DPosition(Vector2(screenWidth / 2 - 100, screenHeight / 2 - 100));
	//State game score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_TextScore = std::make_shared< Text>(shader, font, std::to_string(score), TEXT_COLOR::RED, 3.0);
	m_TextScore->Set2DPosition(Vector2(screenWidth / 2 - 100, screenHeight / 2 ));

}
void GSGameOver::Exit()
{
}


void GSGameOver::Pause()
{

}

void GSGameOver::Resume()
{

}


void GSGameOver::HandleEvents()
{

}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSGameOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_TextScore->Draw();
	m_text->Draw();
	title->Draw();
}