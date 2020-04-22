#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "SDL/include/SDL_scancode.h"
#define Gravity -9,8

ModulePlayer::ModulePlayer()
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 162, 1, 12, 16 });

	// move right

	rightAnim.PushBack({ 200,1,15,16 });
	rightAnim.PushBack({ 162,1,16,16 });
	rightAnim.loop = true;
	rightAnim.speed = 0.3f;


	// move left

	leftAnim.PushBack({ 81,1,15,16 });
	leftAnim.PushBack({ 122,1,15,16 });
	
	leftAnim.loop = true;
	leftAnim.speed = 0.3f;


	// jump 

	jumpAnim.PushBack({ 240,1,16,15 });
	jumpAnim.loop = false;
	jumpAnim.speed = 0.1f;

	// jump right
	jumprightAnim.PushBack({ 239,0,18,16 });
	jumprightAnim.loop = true;
	jumprightAnim.speed = 0.1f;


	// jump LEFT
	jumpleftAnim.PushBack({ 40,0,17,15 });
	jumpleftAnim.loop = true;
	jumpleftAnim.speed = 0.1f;

	
	// move upwards
	upAnim.PushBack({ 161, 40, 13, 16 });
	upAnim.PushBack({ 201, 40, 14, 15 });
	upAnim.PushBack({ 240, 42, 16, 12 });
	upAnim.PushBack({ 280, 40, 16, 15 });
	upAnim.loop = false;
	upAnim.speed = 0.1f;
	 

	
	// Move down
	downAnim.PushBack({ 0, 40, 16, 15 });
	downAnim.PushBack({ 40, 42, 16, 15 });
	downAnim.PushBack({ 81, 40, 16, 15 });
	downAnim.PushBack({ 122, 40, 16, 16 });
	downAnim.loop = false;
	downAnim.speed = 0.1f;

	// Hammer Left
	hammerleftAnim.PushBack({ 116, 80, 25, 16 });
	hammerleftAnim.PushBack({ 81, 72, 15, 30 });
	hammerleftAnim.PushBack({ 35, 80, 26, 16 });
	hammerleftAnim.PushBack({ 2, 72, 13, 30 });
	hammerleftAnim.loop = true;
	downAnim.speed = 0.1f;

	// Hammer right
	hammerrightAnim.PushBack({ 155, 80, 25, 16 });
	hammerrightAnim.PushBack({ 200, 73, 15, 30 });
	hammerrightAnim.PushBack({ 235, 80, 26, 16 });
	hammerrightAnim.PushBack({ 155, 80, 25, 16 });
	hammerrightAnim.PushBack({ 281, 73, 13, 30 });
	
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/sprites.png");
	currentAnimation = &idleAnim;

	//laserFx = App->audio->LoadFx("Assets/laser.wav");
	//explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 1;
	position.y = 233;
	
	
	collider = App->collisions->AddCollider({ position.x, position.y, 12, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	// If no up/down movement detected, set the current animation back to idle

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idleAnim;

	collider->SetPos(position.x, position.y);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) {
		salt = true;
		posintsalt = position.y;
		if (currentAnimation != &jumpAnim)
		{
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
	}
	
	if (salt) { position.y -= 1; ++saltat; }
	if (saltat >= 16) { salt = false; baixa = true; saltat = 0; }
	if (baixa) { position.y += 1; ++baixat; }
	if (baixat >= 16) { baixa = false; baixat = 0; }

	if (baixat == 0 && saltat == 1)
	{
		if (currentAnimation != &idleAnim)
		{
			idleAnim.Reset();
			currentAnimation = &idleAnim;
		}
	}
	if (salt || baixa)
	{
		if (currentAnimation == &jumpAnim && App->input->keys[SDL_SCANCODE_SPACE])
		{
			jumpAnim.Reset();
			currentAnimation = &jumpAnim;
		}
		if (currentAnimation != &jumpAnim && App->input->keys[SDL_SCANCODE_D])
		{
			jumprightAnim.Reset();
			currentAnimation = &jumprightAnim;
		}
		if (currentAnimation != &jumpAnim && App->input->keys[SDL_SCANCODE_A])
		{
			jumpleftAnim.Reset();
			currentAnimation = &jumpleftAnim;
		}
	}

		
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && c2->type == Collider::Type::WALL)
	{
		ground = true;
	}

	if (c1 == collider && c2->type == Collider::Type::STAIR)
	{
		stair = true;
	}


	if (stair == false && ground == false)
	{
		position.y += speed;
	}

	if (stair == true)
	{
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}


	}


	if (ground == true)
	{
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;

			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}

		}
	}

	if (ground == true && stair == true)
	{
		if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
		{
			position.y -= speed;
			if (currentAnimation != &upAnim)
			{
				upAnim.Reset();
				currentAnimation = &upAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			position.y += speed;
			if (currentAnimation != &downAnim)
			{
				downAnim.Reset();
				currentAnimation = &downAnim;
			}
		}
		if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			position.x -= speed;

			if (currentAnimation != &leftAnim)
			{
				leftAnim.Reset();
				currentAnimation = &leftAnim;
			}
		}

		if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			position.x += speed;
			if (currentAnimation != &rightAnim)
			{
				rightAnim.Reset();
				currentAnimation = &rightAnim;
			}

		}
	}


	


	
		

	
}


