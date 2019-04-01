#include "CollisionListener.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "BroadCaster.h"
#include <iostream>

using namespace std;
void CollisionListener::BeginContact(b2Contact * contact)
{
	if (contact->IsTouching())
	{
		b2Fixture *a = contact->GetFixtureA();
		b2Fixture *b = contact->GetFixtureB();

		b2Body* aBody = a->GetBody();
		b2Body* bBody = b->GetBody();

		bodyUserData *bud = (bodyUserData*)aBody->GetUserData();
		bodyUserData *bud1 = (bodyUserData*)bBody->GetUserData();
		if (bud && bud1)
		{
			//check if bullet collide with bricks
			if (bud->bodyType == OT_Bullet && bud1->bodyType == OT_StaticPlayer)
				BroadCaster::Get()->SendEvent("BulletCollided");
			if (bud1->bodyType == OT_Bullet && bud->bodyType == OT_StaticPlayer)
				BroadCaster::Get()->SendEvent("BulletCollided");
			
			//check if bricks and pacman collide or not
			if ((bud->bodyType == OT_StaticPlayer || bud1->bodyType == OT_StaticPlayer))
			{
				if (bud1->bodyType >= OT_MAX)
				{
					BroadCaster::Get()->SendEvent("PacManCollided");
				}
				else if (bud->bodyType >= OT_MAX)
				{
					BroadCaster::Get()->SendEvent("PacManCollided");
				}
			}

			//check if pacman and bullet collide or not
			if (bud->bodyType == OT_Bullet && bud1->bodyType == OT_Enemy)
			{
				/*if (bud1->bodyType >= OT_MAX )
				{*/
					DelbodyUserData = bud1->id;
					BroadCaster::Get()->SendEvent("KillEnemy");
				//}
			}
			if (bud1->bodyType == OT_Bullet && bud->bodyType == OT_Enemy)
			{
				/*if(bud->bodyType >= OT_MAX )
				{*/
					DelbodyUserData = bud->id;
					BroadCaster::Get()->SendEvent("KillEnemy");
				//}
			}

			//check if player and pacman collide or not
			if ((bud->bodyType == OT_Player || bud1->bodyType == OT_Player))
			{
				if (bud1->bodyType == OT_Enemy)
				{
					DelbodyUserData = bud1->id;
					BroadCaster::Get()->SendEvent("KillPlayer");
				}
				else if (bud->bodyType == OT_Enemy)
				{
					DelbodyUserData = bud->id;
					BroadCaster::Get()->SendEvent("KillPlayer");
				}
			}

			if (bud->bodyType >= OT_MAX && bud1->bodyType == OT_DIAMOND)
			{
				BroadCaster::Get()->SendEvent("ChangeDirection");

			}
			else if (bud1->bodyType >= OT_MAX && bud->bodyType == OT_DIAMOND)
			{
				BroadCaster::Get()->SendEvent("ChangeDirection");
			}

			if (bud->bodyType == OT_Player && bud1->bodyType == OT_DIAMOND)
			{
				DelDiamondId = bud1->id;
				BroadCaster::Get()->SendEvent("HideDiamond");
			}
			else if (bud1->bodyType == OT_Player && bud->bodyType == OT_DIAMOND)
			{
				DelDiamondId = bud->id;
				BroadCaster::Get()->SendEvent("HideDiamond");
			}
		}
	}
}

void CollisionListener::EndContact(b2Contact * contact)
{
	//std::cout << "End Contact" << std::endl;
}

void CollisionListener::PreSolve(b2Contact * contact, const b2Manifold * oldManifold)
{
}

void CollisionListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	/*contact->GetFixtureA()->GetBody()->SetActive(true);
	contact->GetFixtureB()->GetBody()->SetActive(true);*/
}
