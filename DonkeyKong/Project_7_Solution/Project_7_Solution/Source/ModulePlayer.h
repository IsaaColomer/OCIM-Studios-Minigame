#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:

	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// 
	
	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;
	// The speed in which we move the player (pixels per frame)
	int speed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleAnim;
	Animation leftAnim;
	Animation jumpAnim;
	Animation jumprightAnim;
	Animation jumpleftAnim;
	Animation rightAnim;
	Animation hammerleftAnim;
	Animation hammerrightAnim;
	Animation upAnim;
	Animation downAnim;

	// The player's collider
	Collider* collider = nullptr;
	Collider* collider2 = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	bool ground = false;
	bool stair = false;

	int posY;
	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;


	bool salt = 0;
	bool baixa = 0;
	int posintsalt = 0;
	int saltat = 0;
	int baixat = 0;
	/*
	float speedJ = 0.5;
	int contador = 0;
	*/
	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;
};

#endif //!__MODULE_PLAYER_H__