#include "stdafx.h"
#include "bat.h"
#include "batAttackState.h"
#include "batDamagedState.h"
#include "batIdleState.h"
#include "batMoveState.h"
#include "batDeathState.h"

batState * batDeathState::inputHandle(bat * bat)
{
	return nullptr;
}

void batDeathState::update(bat * bat)
{
}

void batDeathState::enter(bat * bat)
{
}

void batDeathState::exit(bat * bat)
{
}
