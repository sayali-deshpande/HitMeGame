#include "Bullet.h"

std::vector<Bullet*> Bullet::bulletList;
std::vector<b2Body*> Bullet::deleteBodies;
Bullet::Bullet()
{
	//BroadCaster::Get()->AddListner(this);
}

Bullet::~Bullet()
{
	RemoveComponent(m_sprite);
	RemoveComponent(m_physics);
}

void Bullet::Init(b2Vec2 vec)
{
	m_sprite = new SpriteComponent(false);
	AddComponent(m_sprite);
	m_physics = new PhysicsComponent();
	AddComponent(m_physics);

	m_sprite->LoadTexture("../assets/bullet.png");
	m_sprite->height = 20;
	m_sprite->width = 20;
	createBody((int)vecPos.x, (int)vecPos.y, 10, 10,this, true);
	m_sprite->srcRect.x = 200;
	m_sprite->srcRect.y = 200;
	alive = true;
	bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_Bullet;
	GetBody()->SetUserData(bud);
}

void Bullet::update()
{
	if (alive)
	{
  		GetBody()->SetAwake(true);
		GetBody()->SetGravityScale(0);

		//b2Vec2 VecPos = GetBody()->GetPosition();
		float VelocityX = dirVec.x * 0.1;
		float VelocityY = dirVec.y * 0.1;

		//GetBody()->SetLinearVelocity(b2Vec2(VelocityX, VelocityY));
		GetBody()->SetLinearVelocity(b2Vec2(VelocityX, -VelocityY));

		alive = 0;
	}

	/*CheckIfOutOfScope();*/
	
}

void Bullet::render()
{
	update();
}

void Bullet::FireBullet()
{
	Init(vecPos);
	setAwake(true);
	CheckBeforeDraw();
}

void Bullet::OnEvent(InputKey key/*const Event &e*/)
{
}

void Bullet::PassMessage(std::string str)
{
	if (str == "BulletCollided")
	{
		/*cout << "Bullet collide";*/
		RemoveBullet();
	}
	else if (str == "DeleteBullet")
	{

	}
}

void Bullet::SetPosition(b2Vec2 PlayerPos)
{
	if (PlayerFaceDirection == SDL_FLIP_NONE) //If Player is pointing towards right
	{
		vecPos.x = PlayerPos.x + 96; // height
		vecPos.y = PlayerPos.y + 35; //half of width
	}
	else if (PlayerFaceDirection == SDL_FLIP_HORIZONTAL)
	{
		vecPos.x = PlayerPos.x; // height
		vecPos.y = PlayerPos.y + 35; //half of width
	}

	SDL_GetMouseState(&MouseXpos, &MouseYpos);
	angleX = MouseXpos - vecPos.x;
	angleY = MouseYpos - vecPos.y;

	float vector_length = sqrt(angleX*angleX + angleY*angleY);

	dirVec.x = angleX / vector_length;
	dirVec.y = angleY / vector_length;

	alive = true;
}

bool Bullet::CheckIfOutOfScope(Bullet* b)
{
	int x = (b->GetBody()->GetPosition().x   * meterToPixel) - m_sprite->width / 2;
	int y = (b->GetBody()->GetPosition().y   * meterToPixel) - m_sprite->height / 2;

	// check if bullet is going out of screen height or width
	if ((x > SCREEN_WIDTH - 10) || (y >= -10) || x < 0)
	{
		//RemoveBullet();
		return true;
	}
	else
		return false;
}

void Bullet::addBullet(Bullet* b1, b2Vec2 pos)
{
	RemoveBullet();
	GameObject::EntityList.push_back(b1);
	b1->SetType(OT_Bullet);
	b1->SetPosition(pos);
	
	Bullet::bulletList.push_back(b1);

	BroadCaster::Get()->AddListner(b1);
}

void Bullet::RemoveBullet()
{
	if (!Bullet::bulletList.empty())
	{
		Bullet *temp = Bullet::bulletList.at(0);
		temp->m_sprite->UnloadTexture();
	
		Bullet::deleteBodies.push_back(temp->GetBody());
		BroadCaster::Get()->RemoveListner(temp);
		
		std::vector<GameObject*>::iterator objItr = GameObject::EntityList.begin();
		while (objItr != GameObject::EntityList.end())
		{
			if ((*objItr)->GetID() == temp->GetID())
			{
				(*objItr)->isDead = true;
			}
			objItr++;
		}
		Bullet::bulletList.pop_back();
		//delete temp;
	}
}

void Bullet::CheckBeforeDraw()
{
	DeleteBodiesIfAny();

	if (!Bullet::bulletList.empty())
	{
		for (bulletItr = Bullet::bulletList.begin(); bulletItr != Bullet::bulletList.end() /*&& (*bulletItr)->alive*/;bulletItr++)
		{
			int i = 0;
			if ((*bulletItr)->alive!=true && (*bulletItr)->CheckIfOutOfScope(*bulletItr))
			{
				RemoveBullet();
			}
			else
			(*bulletItr)->update();
			i++;
		}
	}
}

void Bullet::DeleteBodiesIfAny()
{
	int i = Bullet::deleteBodies.size() - 1;
	while (Bullet::deleteBodies.size() != 0)
	{
			b2Body *b = Bullet::deleteBodies.at(i);
			Bullet::deleteBodies.pop_back();;
			b->SetUserData(NULL);
			b->GetWorld()->DestroyBody(b);
			//world->DestroyBody(b);
			i--;
	}
}
