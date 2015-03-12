#pragma once

sysDef(StaticCollisionResponse)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
	{	return e && e->active && e->collider && e->rigidbody;	}


void update(Entity *e)
{
	for each(auto o in e->collider->contacts)
	{
		if (!o->rigidbody)
		{
			auto &Collider = o->collider->shape;

			vec3 P = Collider.plane.normal * vec3Dot(e->rigidbody->velocity / -1, Collider.plane.normal);
			e->rigidbody->velocity = P * 2 + e->rigidbody->velocity;
		}
	}
}

sysEndDef