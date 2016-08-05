#include <fstream>
#include <iostream>
#include <SDL_image.h>

#include "GameObject.h"
#include "Manager.h"

GameObject::GameObject(void)
	: target(nullptr)
	, active(true)
	, surf(nullptr)
	, img(nullptr)
	, angle(0)
	, targetPoint(nullptr)
	, roatationSpeed(100)
	, pos({ 0,0,0,0 })
	, position(0, 0)
	, velocity(0, 0)
	, accel(0, 50)
	, clip({ 0,0,0,0 })
	, frame(0)
	, prev(0)
	, timer(0)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::Init(string txtfile, SDL_Rect* dest)
{
	img = Manager::LoadTexture(txtfile, &pos);
	prev = SDL_GetTicks();
	timer = 0;
}

//true if eats up a key, false otherwise
bool GameObject::Update()
{
	Uint32 now = SDL_GetTicks();
	dt = (now - prev) / 1000.0;
	timer += dt;
	prev = now;

	if (!active)
		return false;

	FollowTarget();

	//angle += roatationSpeed * dt;


	UpdateAnimation();

	return false;
}
void GameObject::FollowTarget()
{
	if (target == nullptr)
		return;

	target_behavior = TargetBehavior::NONE;

	float angle = 180 * SDL_GetTicks() / 1000.0f;
	float rotate_angle = (offset.th + angle) * M_PI / 180;


	Vector2 target_pivot = target->position + Vector2(target->pos.w, target->pos.h) / 2;



	Vector2 center;
	center.x = offset.r * cos(rotate_angle) + target_pivot.x;
	center.y = offset.r * sin(rotate_angle) + target_pivot.y;

	position = center - Vector2(pos.w, pos.h) / 2;

}

void GameObject::Render()
{
	pos.x = (int)position.x;
	pos.y = (int)position.y;
	if (active)
	{
		Manager::RenderTextureEx(img, nullptr, &pos, angle, nullptr);
	}

}

void GameObject::Move(int direction)
{
	//Enter movement logic here
	if (direction & KEYS::UP) {}
	if (direction & KEYS::DOWN) {}
	if (direction & KEYS::LEFT) {}
	if (direction & KEYS::RIGHT) {}
}

void GameObject::UpdateAnimation()
{
	// Input animation logic (clip animation) here
	if (timer > 1.0 / FPS) // 66ms ~ 1/15 sec
	{
		frame++;
		timer = 0;
	}
}