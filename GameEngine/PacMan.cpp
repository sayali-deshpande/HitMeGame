#include "PacMan.h"

bool PacMan::isAtLeftBoundry()
{
	if (GetPacManXpos() < 50)
		return true;
	else
		return false;
}

bool PacMan::isAtRightBoundry()
{
	if (GetPacManXpos() > SCREEN_WIDTH - 10)
		return true;
	else
		return false;
}

bool PacMan::isAtUpBoundry()
{
	if (GetPacManYpos() >= -50)
		return true;
	else
		return false;
}

bool PacMan::isAtBottomBoundry()
{
	if (GetPacManYpos() <= -SCREEN_HEIGHT -10 && (GetPacManXpos() == 0 || GetPacManXpos() >= -SCREEN_WIDTH - 100))
		return true;
	else
		return false;
}

void PacMan::GetRandomDirection()
{
	
	int randomVal = rand() % 4;
	if (randomVal == previousRandomNum)
	{
		previousRandomNum = randomVal;
		GetRandomDirection();
	}
	previousRandomNum = randomVal;
	switch (randomVal)
	{
	case 0:
	{
		this->SetState(EntityState::WalkLeft);
		MoveLeft();
	}
	break;
	case 1:
	{
		this->SetState(EntityState::WalkRight);
		MoveRight();
	}
	break;
	case 2:
	{
		this->SetState(EntityState::GoUp);
		MoveUp();
	}
	break;
	case 3:
	{
		this->SetState(EntityState::GoDown);
		MoveDown();
	}
	break;
	default: break;
	}
}

PacMan::PacMan()
{
	this->birth = SDL_GetTicks() / 1000;
	xPos = yPos = 0.0f;
	this->changeDirection = false;
	this->FaceDirection = SDL_FLIP_NONE;
	SetState(EntityState::Idle);
	previousRandomNum = 0;
	srand(time(0));
}

PacMan::~PacMan()
{
}

void PacMan::Init()
{
	m_sprite = new SpriteComponent(false);
	AddComponent(m_sprite);
	m_physics = new PhysicsComponent();
	AddComponent(m_physics);

	 xPos = rand() % 600;
	 yPos = rand() % 800;

	m_sprite->LoadTexture("../assets/Pac-Man-PNG-Picture1.png");
	m_sprite->height = 50;
	m_sprite->width = 50;
	createBody(xPos, yPos, 50, 50, this, true);
	m_sprite->srcRect.x = 0;
	m_sprite->srcRect.y = 0;
	m_sprite->srcRect.h = 79;
	m_sprite->srcRect.w = 73;

	SetType(OT_Enemy);

	/*bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_Enemy;
	GetBody()->SetUserData(bud);*/
	GetBody()->SetGravityScale(0);

	this->changeDirection = false;
	SetState(EntityState::WalkRight);

	BroadCaster::Get()->AddListner(this);
}

void PacMan::update()
{
	if ( this->GetCurrentState() == EntityState::GoDown)
	{
		this->SetState(EntityState::GoDown);
		this->MoveDown();
	}
	if ( this->GetCurrentState() == EntityState::WalkLeft)
	{
		this->SetState(EntityState::WalkLeft);
		this->MoveLeft();
	}
	if (GetCurrentState() == EntityState::WalkRight)
	{
		this->SetState(EntityState::WalkRight);
		this->MoveRight();
	}
	if (this->GetCurrentState() == EntityState::GoUp)
	{
		this->SetState(EntityState::GoUp);
		this->MoveUp();
	}
}

void PacMan::render()
{
	b2Vec2 pos = GetBodyPositions();
	m_sprite->box.x = (pos.x   * meterToPixel) - m_sprite->width / 2;
	m_sprite->box.y = (pos.y  * -meterToPixel) - m_sprite->height / 2;

	m_sprite->box.h = m_sprite->height;
	m_sprite->box.w = m_sprite->width;

	//m_sprite->srcRect.h= 100;
	//m_sprite->srcRect.w = 100;

	//m_sprite->srcRect.x = 200;
	//m_sprite->srcRect.y = 200;

	float angle = 0.0f;
	SDL_RenderCopyEx(renderer, this->tex,  &m_sprite->srcRect, &m_sprite->box, angle, NULL, FaceDirection);
}

void PacMan::MoveLeft()
{
	FaceDirection = SDL_FLIP_NONE;
	this->changeDirection = true;
	this->GetBody()->SetAwake(true);
	this->GetBody()->SetLinearVelocity(b2Vec2(-0.03f, 0.0f));
	if (GetPacManXpos() <= 300)
		this->SetState(EntityState::GoDown);
}

void PacMan::MoveRight()
{
	FaceDirection = SDL_FLIP_HORIZONTAL;
	this->GetBody()->SetAwake(true);
	this->GetBody()->SetLinearVelocity(b2Vec2(0.03f, 0.0f));
	if (GetPacManXpos() >= SCREEN_WIDTH - 100)
		this->SetState(EntityState::WalkLeft);
}

void PacMan::MoveUp()
{
	FaceDirection = SDL_FLIP_NONE;
	this->GetBody()->SetAwake(true);
	this->GetBody()->SetLinearVelocity(b2Vec2(0.0f,0.03f));
	if (isAtUpBoundry())
		GetRandomDirection();
//		this->SetState(EntityState::WalkLeft);
}

void PacMan::MoveDown()
{
	FaceDirection = SDL_FLIP_NONE;
	this->changeDirection = true;
	this->GetBody()->SetAwake(true);
	this->GetBody()->SetLinearVelocity(b2Vec2(0.0f, -0.03f));
	if (isAtBottomBoundry())
		GetRandomDirection();
}

void PacMan::OnEvent(InputKey key/*const Event & e*/)
{
}

void PacMan::PassMessage(std::string message)
{
	if (message == "PacManCollided")
	{
		/*cout << endl << "PacMan collieded with Bricks";*/
		GetRandomDirection();
	}
	else if (message == "KillEnemy")
	{
 		bodyUserData *bud = (bodyUserData*)this->GetBody()->GetUserData();
		if (DelbodyUserData == bud->id && isDead == false) {
			this->isDead = true;
		
			BroadCaster::Get()->SendEvent("BulletCollided");
		}
	}
	else if (message == "ChangeDirection")
	{
		GetRandomDirection();
	}
}

float PacMan::GetPacManXpos()
{
	b2Vec2 pos = GetBody()->GetPosition();
	xPos = (pos.x   * meterToPixel) - m_sprite->width / 2;
	return xPos;
}

float PacMan::GetPacManYpos()
{
	b2Vec2 pos = GetBody()->GetPosition();
	yPos = (pos.y   * meterToPixel) - m_sprite->height / 2;
	return yPos;
}
