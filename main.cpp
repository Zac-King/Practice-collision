#include "Core.h"
#include "System.h"
#include "DependentClear.h"
#include "ccollisionutils.h"

int main()
{
	coreLoad(Window);
	coreLoad(Time);
	coreLoad(Input);
	coreLoad(Camera);
 	coreLoad(Factory);
	coreLoad(Asset);
	
	systemLoad(TransformUpdate);
	systemLoad(Rendering);
	systemLoad(CollisionPrep);
	systemLoad(CollisionDetection);
	systemLoad(StaticCollisionResponse);
	systemLoad(DynamicCollisionResponse);
	systemLoad(RigidbodyDynamics);
	systemLoad(TankDynamics);
	systemLoad(LifeTimeDynamics);
	systemLoad(collisionRender);

	initCore();



	// Safe to load assets and make dudes.
	core(Asset).loadShader("Flat","./shaders/simpleShader.vert", "./shaders/simpleShader.frag");
	
	/////Tank 1
	Vertex Tank1[3] = { { {   0,  30, 0, 1 }, { 0, 1, 1, 0 } },
						{ { -30, -30, 0, 1 }, { 0, 1, 1, 0 } }, 
						{ {  30, -30, 0, 1 }, { 0, 1, 1, 0 } } };
	Triangle tank1[1] = { 0, 1, 2 };

	core(Asset).loadMesh("Tank1", Tank1, 3, tank1, 1);

	/////Tank 2
	Vertex Tank2[3] = { { { 0, 30, 0, 1 }, { 1, 0, 0, 1 } },
					    { { -30, -30, 0, 1 }, { 1, 0, 0, 1 } },
						{ {  30, -30, 0, 1 }, { 1, 0, 0, 1 } } };
	Triangle tank2[1] = { 0, 1, 2 };

	core(Asset).loadMesh("Tank2", Tank2, 3, tank2, 1);

	////////Turret
	Vertex Turret[3] = { { {   0,  40, 0, 1 }, { 1, 0, 1, 0 } },
						{ { -15, -10, 0, 1 }, { 0, 1, 0, 1 } },
						{ {  15, -10, 0, 1 }, { 1, 0, 1, 0 } } };
	Triangle turret[1] = { 0, 1, 2 };

	core(Asset).loadMesh("Turret", Turret, 3, turret, 1);


	//////Bullet
	Vertex Bullet[3] = { { {   0,  15, 0, 1 }, { 1, 1, 1, 0 } },
						 { { -5, -5, 0, 1 }, { 0, 1, 0, 1 } },
					     { {  5, -5, 0, 1 }, { 1, 0, 1, 0 } } };
	Triangle bullet[1] = { 0, 1, 2 };

	core(Asset).loadMesh("Bullet", Bullet, 3, bullet, 1);

	/////Asteroid
	Vertex Asteroid[3] = { { {   0,  40, 0, 1 }, { 1, 1, 1, 0 } },
						   { { -15, -10, 0, 1 }, { 0, 1, 0, 1 } },
						   { {  15, -10, 0, 1 }, { 1, 0, 1, 0 } } };
	Triangle asteroid[1] = { 0, 1, 2 };

	core(Asset).loadMesh("Asteroid", Asteroid, 3, asteroid, 1);

	core(Factory).CreatePlane(0, core(Window).height() / 2, vec3Make(1,0,0), 0);
	core(Factory).CreatePlane(core(Window).width(), core(Window).height() / 2, vec3Make(-1, 0, 0), 0);
	core(Factory).CreatePlane(core(Window).width() / 2, 0, vec3Make(0, 1, 0), 0);
	core(Factory).CreatePlane(core(Window).width() / 2, core(Window).height(), vec3Make(0, -1, 0), 0);

	//core(Factory).CreateCircle(core(Window).width() / 2, core(Window).height() / 2, 55, 0);
	core(Factory).CreateRect(core(Window).width() / 2, core(Window).height() / 2, 0);

	core(Factory).MakeTank(core(Window).width() / 2 - 320, core(Window).height() / 2, 1);
	core(Factory).MakeTank(core(Window).width() / 2 + 320, core(Window).height() / 2, 2, 'I', 'K', 'J', 'L', 'U', 'O', 'N');
	//core(Factory).MakeAsteroid(core(Window).width() / 2, core(Window).width() / 2, 3);

	runGame();


}