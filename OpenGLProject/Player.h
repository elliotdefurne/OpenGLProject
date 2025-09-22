#pragma once
#include "Entity.h"

class Player : public Entity{
	public:
		Player(Renderer* renderer) : Entity(renderer) {};
		~Player() = default;
		void update() override;
		void draw() override;
		void proccessDirectionKey(int direction);
};

