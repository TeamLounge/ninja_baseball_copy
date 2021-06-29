#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDamagedState::inputHandle(glove * glove)
{
	return nullptr;
}

void gloveDamagedState::update(glove * glove)
{
}

void gloveDamagedState::enter(glove * glove)
{
}

void gloveDamagedState::exit(glove * glove)
{
}
