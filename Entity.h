
#pragma once

#include "Transform.h"
#include "Rigidbody.h"
#include "Render.h"
#include "Controller.h"
#include "Collider.h"
#include "Dependent.h"
#include "LifeTime.h"
#include <string>

#define entityFree(e)  do { \
						compFree(e, transform); \
						compFree(e, rigidbody); \
						compFree(e, render); \
						compFree(e, controller); \
						compFree(e, collider); \
						compFree(e, dependent); \
						compFree(e, lifeTime); \
						e->active = false; \
						} while (0)


struct Entity
{
	std::string name;
	bool active;
	bool newEntity;
	bool deleteEntity;

	int factoryIndex;
	Transform *transform;
	Rigidbody *rigidbody;
	Render    *render;
	Controller *controller;
	Collider *collider;
	Dependent *dependent;
	LifeTime *lifeTime;

	

	Entity(int UID) : factoryIndex(UID), active(false), newEntity(true), deleteEntity(false),
		transform(0),
		rigidbody(0),
		render(0),
		controller(0),
		collider(0),
		dependent(0),
		lifeTime(0) { }
};