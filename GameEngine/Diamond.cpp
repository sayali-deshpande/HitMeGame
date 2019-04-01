#include "Diamond.h"
#include "PlayState.h"

int Diamond::objectId = 0;

Diamond::Diamond(int x, int y, int w, int h)
	:xPos(x), yPos(y), height(h), width(w)
{
}

Diamond::~Diamond()
{
}

void Diamond::init()
{
	m_sp = new SpriteComponent(false);
	m_phy = new PhysicsComponent();
	AddComponent(m_sp);
	AddComponent(m_phy);
	SetType(OT_DIAMOND);
	
	m_sp->LoadTexture("../assets/diamond.png");
	createBody(xPos, yPos, width, height, this, true);
	GetBody()->SetAwake(false);
	b2Fixture* fixture = GetBody()->GetFixtureList();

	bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_DIAMOND;
	bud->id = ++objectId;

	GetBody()->SetUserData(bud);

	int srcH, srcW;
	SDL_QueryTexture(tex, NULL, NULL, &srcW, &srcH);

	m_sp->srcRect.x = 0; m_sp->srcRect.y = 0;
	m_sp->srcRect.h = srcH; m_sp->srcRect.w = srcW;
	m_sp->height = height;
	m_sp->width = width;

	BroadCaster::Get()->AddListner(this);
}

void Diamond::update()
{
}

void Diamond::OnEvent(InputKey key)
{
}

void Diamond::PassMessage(std::string message)
{
	if (message == "HideDiamond")
	{
		bodyUserData *bud = (bodyUserData*)this->GetBody()->GetUserData();
		if (DelDiamondId == bud->id && isDead == false)
		{
			this->m_sp->UnloadTexture();
			this->isDead = true;
			DelDiamondId = -1;
			PlayState::NoOfEnemyDied += 10;
		}
	}
}

void Diamond::render()
{
	b2Vec2 pos = GetBodyPositions();
	m_sp->box.x = (pos.x   * meterToPixel) - m_sp->width / 2;
	m_sp->box.y = (pos.y  * -meterToPixel) - m_sp->height / 2;

	m_sp->box.h = m_sp->height;
	m_sp->box.w = m_sp->width;

	float angle = 0.0f;
	SDL_RenderCopyEx(renderer, this->tex, &m_sp->srcRect, &m_sp->box, angle, NULL, SDL_FLIP_NONE);
}

void Diamond::RemoveDiamond()
{
}
