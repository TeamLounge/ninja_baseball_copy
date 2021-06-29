#include "stdafx.h"
#include "glove.h"
#include "gloveAttackTongueState.h"
#include "gloveDamagedState.h"
#include "gloveDeathState.h"
#include "gloveJumpState.h"
#include "gloveMoveState.h"

gloveState * gloveDeathState::inputHandle(glove * glove)
{
	return nullptr;
}

void gloveDeathState::update(glove * glove)
{
}

void gloveDeathState::enter(glove * glove)
{
}

void gloveDeathState::exit(glove * glove)
{
}
