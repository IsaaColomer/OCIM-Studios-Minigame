#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"

ModuleScene::ModuleScene()
{
	//Background lvl 2
	background = {0,0,224,256 };

	//Barrel fire lvl 2
	//barrelFire = { 416, 136, 16, 32};
}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Level4_Background.png");
	//App->audio->PlayMusic("Assets/stage1.ogg", 1.0f);


	//Floor 0 colliders
	App->collisions->AddCollider({ 0, 248, 224, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 8, 208, 48, 8 }, Collider::Type::WALL);

	
	App->collisions->AddCollider({ 8, 216, 8, 32 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 16, 176, 8, 32 }, Collider::Type::STAIR); 
	
	//Bottom collider
	/*App->collisions->AddCollider({ 0, 231, 227, 8 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 7, 192, 49, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 63, 192, 97, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 167, 192, 49, 8 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 63, 152, 97, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 15, 152, 41, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 167, 152, 41, 8 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 23, 111, 33, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 63, 111, 97, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 167, 111, 33, 8 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 31, 72, 25, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 63, 72, 97, 8 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 167, 72, 25, 8 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 55, 31, 113, 8 }, Collider::Type::WALL);*/

	// Stair
	/*App->collisions->AddCollider({ 8, 216, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 104, 200, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 208, 200, 8, 33 }, Collider::Type::STAIR);

	App->collisions->AddCollider({ 16, 159, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 72, 159, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 144, 159, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 200, 159, 8, 33 }, Collider::Type::STAIR);

	App->collisions->AddCollider({ 24, 118, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 192, 118, 8, 33 }, Collider::Type::STAIR);

	App->collisions->AddCollider({ 32, 79, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 184, 79, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 64, 79, 8, 33 }, Collider::Type::STAIR);
	App->collisions->AddCollider({ 152, 79, 8, 33 }, Collider::Type::STAIR);*/

	// Stair D
	/*App->collisions->AddCollider({ 8, 193, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 104, 193, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 208, 193, 8, 40 }, Collider::Type::STAIRD);

	App->collisions->AddCollider({ 16, 153, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 72, 153, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 144, 153, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 200, 153, 8, 40 }, Collider::Type::STAIRD);

	App->collisions->AddCollider({ 24, 112, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 192, 112, 8, 40 }, Collider::Type::STAIRD);

	App->collisions->AddCollider({ 32, 73, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 184, 73, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 64, 73, 8, 40 }, Collider::Type::STAIRD);
	App->collisions->AddCollider({ 152, 73, 8, 40 }, Collider::Type::STAIRD);*/
	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	//// Enemies ---
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	//// TODO 1: Add a new wave of red birds
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 735, 120);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 750, 120);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 775, 120);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 790, 120);

	//// TODO 2: Add a new wave of brown cookies
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 830, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 850, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 870, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 890, 100);

	//App->enemies->AddEnemy(ENEMY_TYPE::MECH, 900, 195);


	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x += 3;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, &background, NULL);
	//App->render->Blit(bgTexture, 104, 112, &barrelFire, NULL);

	return update_status::UPDATE_CONTINUE;
}