#include "Player.h"

void Player::Init()
{
	spriteComponent = new SpriteComponent(true);
	physicsComponent = new PhysicsComponent();
	AddComponent(spriteComponent);

	AddComponent(physicsComponent);

	spriteComponent->LoadTexture("../assets/hero_spritesheet.png");

	spriteComponent->height = 75;
	spriteComponent->width = 96;
	createBody(0, 0, 96, 75,this, true);
	spriteComponent->srcRect.x = 0;
	spriteComponent->srcRect.y = 100 + 1;
	Play("Idle");
	setAwake(true);

	SetType(OT_Player);
	
	bodyUserData *bud = new bodyUserData();
	bud->bodyType = OT_Player;
	GetBody()->SetUserData(bud);
}

Player::Player()
{
	Animation idle = Animation(0, 1, 200);
	Animation walk = Animation(3, 5, 600);
	Animation die = Animation(5, 2, 600);

	animations.emplace("Idle", idle);
	animations.emplace("Walk", walk);
	animations.emplace("Die", die);
	SetState(EntityState::Idle);
}

Player:: ~Player()
{
	RemoveComponent(spriteComponent);
	RemoveComponent(physicsComponent);
}

void Player::update()
{
	if (spriteComponent->m_animated)
	{
		int textureHeight, textureWidth;
		int frameHeight, frameWidth;

		SDL_QueryTexture(tex, NULL, NULL, &textureWidth, &textureHeight);
		frameWidth = textureWidth / 6;
		frameHeight = textureHeight / 5;

		spriteComponent->srcRect.h = spriteComponent->box.h = 100/*frameHeight*/;
		spriteComponent->srcRect.w = spriteComponent->box.w = frameWidth;

		uint32 ticks = SDL_GetTicks() / m_speed;
		ticks = ticks % m_frames;
		spriteComponent->srcRect.x = ticks * 96;
		const uint8 *state = SDL_GetKeyboardState(NULL);
		if (spriteComponent->srcRect.x >= (textureWidth - 96) && (InputManager::Get()->isKeyUp(KEYBOARD_KEY_LEFT) || InputManager::Get()->isKeyUp(KEYBOARD_KEY_RIGHT)) && this->GetCurrentState() == EntityState::Idle) //after the set of frames get executed stop the animation
		{
			Play("Idle");
			spriteComponent->srcRect.y = spriteComponent->srcRect.x = 0;
			walk = false;
		}
	}
}

void Player::Play(const char * animName)
{
	m_frames = animations[animName].frames;
	animIndex = animations[animName].index;
	m_speed = animations[animName].speed;
}

void Player::HandleInput(SDL_Event * e)
{
}

void Player::OnEvent(InputKey key)
{
	switch (key)
	{
		walk = false;
	case KEYBOARD_KEY_LEFT:
		if (InputManager::Get()->isKeyDown(KEYBOARD_KEY_LEFT))
		{
			float x = GetBody()->GetPosition().x;
			x = (x *meterToPixel) - spriteComponent->width / 2;
			if ((x < 0) )
			{
				break;
			}
			else
			{
				SetState(EntityState::WalkLeft);
				GetBody()->SetAwake(true);
				b2Vec2 pos = this->GetBody()->GetLinearVelocity();
				float velChange = -0.1f - pos.x;
				float force = GetBody()->GetMass() * velChange / (1 / FRAME_RATE);
				this->GetBody()->ApplyForce(b2Vec2(force, 0), this->GetBody()->GetWorldCenter(), true);
				spriteComponent->SetRenderFlip(SDL_FLIP_HORIZONTAL);
				PlayerFaceDirection = SDL_FLIP_HORIZONTAL;

				if (!walk)
				{
					Play("Walk");
					PlayerFaceDirection = SDL_FLIP_HORIZONTAL;
					spriteComponent->SetRenderFlip(SDL_FLIP_HORIZONTAL);
					spriteComponent->srcRect.y = 3 * 100;
					spriteComponent->srcRect.x = 0;
					walk = true;
				}

			}
			
		}
	case KEYBOARD_KEY_RIGHT:
		if (InputManager::Get()->isKeyDown(KEYBOARD_KEY_RIGHT) || GetCurrentState() == EntityState::WalkRight)
		{
			float x = GetBody()->GetPosition().x;
			float y = GetBody()->GetPosition().y;

				x = (x *meterToPixel) - spriteComponent->width / 2;
				if (x > SCREEN_WIDTH - 100)
					break;
				else
				{
					SetState(EntityState::WalkRight);
					GetBody()->SetAwake(true);
					b2Vec2 pos = GetBody()->GetLinearVelocity();
					float velChange = 0.1f - pos.x;
					float force = this->GetBody()->GetMass() * velChange / (1 / FRAME_RATE);
					this->GetBody()->ApplyForce(b2Vec2(force, 0), this->GetBody()->GetWorldCenter(), true);
					spriteComponent->SetRenderFlip(SDL_FLIP_NONE);
					PlayerFaceDirection = SDL_FLIP_NONE;

					if (!walk)
					{
						Play("Walk");
						spriteComponent->SetRenderFlip(SDL_FLIP_NONE);
						PlayerFaceDirection = SDL_FLIP_NONE;
						spriteComponent->srcRect.y = 3 * 100;
						spriteComponent->srcRect.x = 0;
						walk = true;
					}
				}
		}
	case KEYBOARD_KEY_UP:
		if (InputManager::Get()->isKeyDown(KEYBOARD_KEY_UP))
				{
					SetState(EntityState::GoUp);
					setAwake(true);
					
					b2Vec2 pos = this->GetBody()->GetLinearVelocity();
					pos.y = 0.9f;
					GetBody()->SetLinearVelocity(pos);
					GetBody()->SetFixedRotation(true);
				}
		break;
	case MOUSE_BUTTON_LEFT:
		{
			Bullet* b1 = new Bullet();
			b1->addBullet(b1, GetPlayerPosition());
			b1->FireBullet();
			break;
		}
	default:
		break;
	}
	SetState(EntityState::Idle);
}

void Player::PassMessage(std::string message)
{
	if (message == "GetPlayerPosition")
	{

	}
	if (message == "KillPlayer")
	{
		if (!DelPlayer)
		{
			SetState(EntityState::Death);
			Play("Die");
			PlayerFaceDirection = SDL_FLIP_HORIZONTAL;
			spriteComponent->SetRenderFlip(SDL_FLIP_HORIZONTAL);
			spriteComponent->srcRect.y = 5 * 100;
			spriteComponent->srcRect.x = 0;
 			DelPlayer = true;
			isDead = true;
			cout << endl << "Pacman killed Player" << endl;
			update();
			spriteComponent->render();
		}
	}
}

b2Vec2 Player::GetPlayerPosition()
{
	b2Vec2 pos = GetBody()->GetPosition();
	
	b2Vec2 vec;
	vec.x = (pos.x   * meterToPixel) - spriteComponent->width / 2;
	vec.y = (pos.y  * -meterToPixel) - spriteComponent->height / 2;

	return vec;
}

void Player::deletePlayer()
{
	b2Body* b = this->GetBody();
	b->SetUserData(NULL);
	b->GetWorld()->DestroyBody(b);

	BroadCaster::Get()->RemoveListner(this);
	this->isDead = true;
	DelPlayer = false;
}

