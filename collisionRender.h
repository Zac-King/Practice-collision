#pragma once
#include "SystemDef.h"
#include "crenderutils.h"

sysDef(collisionRender)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->transform && e->collider;
}

void update(Entity *e)
{
	e->collider->shape.orgin = e->transform->globalPosition();
	Asset::instance().drawShape(e->collider->shape, vec4Color(1, 1, 1, 1));
}


sysEndDef