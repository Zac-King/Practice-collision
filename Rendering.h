#pragma once
#include "SystemDef.h"
#include "crenderutils.h"

sysDef(Rendering)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->render && e->transform;
}

void update(Entity *e)
{
	auto &r = *e->render;
	auto &t = *e->transform;
	auto &assets = core(Asset);
	auto &camera = core(Camera).getCamera();
	auto mesh   = assets.getMesh(r.mesh);
	auto shader = assets.getShader(r.shader);
	

	glUseProgram(shader);

	GLuint ul_proj = glGetUniformLocation(shader, "Projection");
	GLuint ul_view = glGetUniformLocation(shader, "View");
	GLuint ul_model = glGetUniformLocation(shader, "Model");

	glUniformMatrix4fv(ul_proj, 1, GL_FALSE, camera.projection.m);
	glUniformMatrix4fv(ul_view, 1, GL_FALSE, camera.view.m);
	glUniformMatrix4fv(ul_model, 1, GL_FALSE, t.m_global.m);

	glBindVertexArray(mesh.VAO);
	glDrawElements(GL_TRIANGLES, mesh.size, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
	glUseProgram(0);	
}


sysEndDef