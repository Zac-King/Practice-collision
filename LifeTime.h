#pragma once
#include "Component.h"

compDef(LifeTime)

float timer;
int totalLife;

LifeTime() : timer(0), totalLife(3) {}

compEndDef