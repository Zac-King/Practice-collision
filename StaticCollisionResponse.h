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
			auto &oCollider = o->collider->shape;
			auto &eCollider = e->collider->shape;

			vec3 N = oCollider.plane.normal;

			if (e->collider->shape.type == Shape::eCircle && o->collider->shape.type == Shape::eCircle)
			{
				N = normal( (eCollider.circle.position + e->transform->position()) - (oCollider.circle.position + o->transform->position()) );
			}
 			if (e->collider->shape.type == Shape::eRect && o->collider->shape.type == Shape::eRect)
			{
				float diffx1 = abs(o->collider->shape.rect.min.x - e->collider->shape.rect.max.x);
				float diffx2 = abs(e->collider->shape.rect.min.x - o->collider->shape.rect.max.x);
				float diffy1 = abs(o->collider->shape.rect.min.y - e->collider->shape.rect.max.y);
				float diffy2 = abs(e->collider->shape.rect.min.y - e->collider->shape.rect.max.y);

				return ((diffx1 < diffx2 ? diffx1 : diffx2) +
					(diffy1 < diffy2 ? diffy1 : diffy2)) / 2;

				N = normal((eCollider.rect.position + e->transform->position()) - (oCollider.rect.position + o->transform->position()));	
			}
			//if (e->collider->shape.type == Shape::eRect && o->collider->shape.type == Shape::eCircle)
			//{
			//	vec3 min = e->transform->position() + e->collider->shape.rect.min;
			//	vec3 min = e->transform->position() + e->collider->shape.rect.max;
			//}

			vec3 P = N * vec3Dot(e->rigidbody->velocity / -1, N);
			e->rigidbody->velocity = P * 2 + e->rigidbody->velocity;
		}
	}
}

sysEndDef