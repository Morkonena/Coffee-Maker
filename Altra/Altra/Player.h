//
// Created by Mörkönenä on 30.12.2018
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Common.h"

class Player : public Component
{
public:
	using Component::Component;

	virtual void OnTick() override;
	virtual Type GetType() override;
};

#endif // !PLAYER_H