#pragma once
#include "Core.h"
#include "Entity.h"



coreDef(Factory)

std::vector<Entity> m_entities;

Entity *newEntity()
{
	for (int i = 0; i < m_entities.size(); ++i)
		if (!m_entities[i].active && !m_entities[i].newEntity)
		{
			m_entities[i].newEntity = true;
			return &m_entities[i];
		}

	m_entities.push_back(Entity(m_entities.size()));
	return &m_entities.back();
}

bool step()
{
	for (int i = 0; i < m_entities.size(); ++i)
	{
		// new entities now allowed to update for the next frame
		if (m_entities[i].newEntity)
		{
			m_entities[i].active = true;
			m_entities[i].newEntity = false;			
		}
		// old entities allowed to be removed for next frame
		if (m_entities[i].deleteEntity)
		{
			m_entities[i].active = false;
			m_entities[i].deleteEntity = false;
		}
	}
	return true;
}

bool init() 
{
	m_entities.reserve(64);
	return true; 
}
bool term() { return true; }

public:

	std::vector<Entity> &getEntities() { return m_entities; }

	void FreeEntity(Entity *e)
	{
		e->deleteEntity = true;
	}

	Entity *MakeTank(float x, float y, int faction, char up = 'W', char down = 'S', char left = 'A' , char right = 'D', char tLeft = 'Q', char tRight = 'E', char Fire = ' ')
	{
		Entity *tank = newEntity();
		Entity *turret = newEntity();

		compMake(tank, controller);
		compMake(tank, collider);
		compMake(tank, transform);
		compMake(tank, rigidbody);
		compMake(tank, render);
		compMake(tank, dependent);

		compMake(turret, controller);
		compMake(turret, transform);
		compMake(turret, render);
		compMake(turret, rigidbody);
		compMake(turret, collider);

	
		tank->dependent->child = turret;

		tank->transform->position().x = x;
		tank->transform->position().y = y;
		tank->transform->position().z = 0;

		tank->controller->forward = up;
		tank->controller->reverse = down;
		tank->controller->turn_Left = left;
		tank->controller->turn_Right = right;
		tank->controller->fire = 0;

		tank->collider->faction = faction;
		tank->controller->torque = 500;
		tank->collider->shape = MakeCircle(0,0,40);
		//tank->collider->shape = MakeRect(0, 0, -30, -30, 30, 30); 
		tank->rigidbody->mass = 500;
		tank->rigidbody->drag = 300;

		tank->render->shader = "Flat";
		if (faction == 1)
			tank->render->mesh = "Tank1";
		else tank->render->mesh = "Tank2";

		tank->name = tank->render->mesh;
		

		///Turret info
		turret->controller->speed = 0;
		turret->controller->torque = 10;
		turret->rigidbody->drag = 10;
		turret->collider->faction = tank->collider->faction;
		turret->collider->shape.type = Shape::eNone;
		turret->controller->turn_Left = tLeft;
		turret->controller->turn_Right = tRight;
		turret->controller->fire = Fire;

		turret->transform->m_parent = tank->transform;
		turret->render->mesh = "Turret";
		turret->render->shader = "Flat";
		turret->name = turret->render->mesh;

		return tank;
	}


	Entity *MakeBullet(Transform *source, int faction, float speed)
	{
		Entity *bullet = newEntity();

		bullet->name = "Bullet";

		compMake(bullet, transform);
		compMake(bullet, render);
		compMake(bullet, collider);
		compMake(bullet, rigidbody);
		compMake(bullet, controller);
		compMake(bullet, lifeTime);

		bullet->transform->m_local = source->m_global;
		bullet->render->mesh = "Bullet";
		bullet->render->shader = "Flat";
		bullet->collider->faction = faction;
		//bullet->collider->shape = MakeCircle(0,0,7);
		bullet->collider->shape = MakeRect(0, 0, -20, -10, 20, 40);
		bullet->rigidbody->velocity = bullet->transform->up() * speed;

		bullet->rigidbody->drag = 8;
		bullet->rigidbody->mass = 4;
		bullet->lifeTime->totalLife = 5;

		bullet->controller->clear();

	    return bullet;
	}

	Entity *MakeAsteroid(float x, float y, int faction)
	{
		Entity *asteroid = newEntity();

		compMake(asteroid, collider);
		compMake(asteroid, transform);
		compMake(asteroid, rigidbody);
		compMake(asteroid, render);
		compMake(asteroid, dependent);

		asteroid->transform->position().x = x;
		asteroid->transform->position().y = y;

		asteroid->collider->faction = faction;

		asteroid->render->mesh = "Asteroid";
		asteroid->render->shader = "Flat";

		return asteroid;
	}


	Entity *CreatePlane(float x, float y, vec3 n, int faction)
	{
		Entity *plane = newEntity();

		compMake(plane, collider);
		compMake(plane, transform);

		plane->collider->faction = faction;
		plane->collider->shape = MakePlane(x, y, n);
		return plane;
	}
	
	Entity *CreateCircle(float x, float y, int r, int faction)
	{
		Entity *circle = newEntity();

		compMake(circle, collider);
		compMake(circle, transform);

		circle->collider->faction = faction;
		circle->collider->shape = MakeCircle(x, y, r);
		return circle;
	}

	Entity *CreateRect(float x, float y, int faction)
	{
		Entity *rect = newEntity();

		compMake(rect, collider);
		compMake(rect, transform);

		rect->collider->faction = faction;
		rect->transform->position() = vec3Make(x, y, 0);
		rect->collider->shape = MakeRect(0,0,25,25,-25,-25);

		return rect;
	}

coreEndDef