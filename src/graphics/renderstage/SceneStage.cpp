//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "SceneStage.h"
#include "../../engine/Engine.h"

SceneStage::SceneStage() {
	basicShader = Shader::load("../res/shaders/reasonable.vs", "../res/shaders/reasonable.fs");
	portalShader = Shader::load("../res/shaders/portal.vs", "../res/shaders/portal.fs");
	portalSceneShader = Shader::load("../res/shaders/reasonablePortal.vs", "../res/shaders/reasonable.fs");
	pre = new FBO(Engine::getEngine().getWindowWidth(), Engine::getEngine().getWindowHeight());
	pre_texture = pre->colorTextureAttachment(0);
	pre->depthBufferAttachment();
}

void SceneStage::render() {
	glClearColor(0,.7,1,1);
	pre->bind();
	basicShader->bind();
	for(auto *light : pipeline->lights){
		light->updateShader(basicShader);
	}
	pipeline->dl->updateShader(basicShader);
	pipeline->dl->updateShader(portalSceneShader);
	pipeline->dl->getShadowMap().bind(1);
	basicShader->bind();
	basicShader->uniformi("dLShadowMap", 1);
	portalSceneShader->bind();
	portalSceneShader->uniformi("dLShadowMap", 1);

	glEnable(GL_STENCIL_TEST);
	for(auto * portal : *portals){
		//Draw portal
		glStencilFunc(GL_ALWAYS, 1, 0xFF); //Set stencils to one when drawing
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); //Only keep 1s
		glStencilMask(0xFF); // Write to stencil buffer when drawing
		glClear(GL_STENCIL_BUFFER_BIT);

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		{ //Render portal to stencil buffer
			portalShader->bind();
			mat4 viewprojection = camera->getViewProjection();
			portalShader->uniformMat4("vp", &viewprojection);
			vec3 campos = camera->transform.getPos().getCopy();
			portalShader->uniformVec3("viewpos", &campos);
			portal->render(*portalShader);
			basicShader->bind();
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

		glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass the test if stencil value is 1
		glStencilMask(0x00); // Don't write to stencil buffer when drawing
		mat4 tran;
		mat4 rot;
		rot.initRotation(portal->getTransform().getRot() * quat::fromEulerDeg(vec3(0, 180, 0)));
		tran.initTranslation(portal->getTransform().getPos());
		tran *= rot;
		vec3 saveScale = portal->bound->getTransform().getScale();
		portal->bound->getTransform().setScale(vec3(1, 1, 1), nullptr);
		mat4 view = tran * portal->bound->getTransform().getMatrix().inverse();
		portal->bound->getTransform().setScale(saveScale, nullptr);

		portalSceneShader->bind();
		portalSceneShader->uniformMat4("PortalV", &view);
		mat4 viewprojection = camera->getProjectionMatrix();
		viewprojection *= camera->getViewMatrix();
		portalSceneShader->uniformMat4("vp", &viewprojection);
		vec3 campos = camera->transform.getPos().getCopy();
		portalSceneShader->uniformVec3("viewpos", &campos);

		glEnable(GL_CLIP_PLANE0);
		vec3 z = vec3(0, 0, 1);
		z = portal->getTransform().getRot().rotatedVec3(z);
		vec4 plane = vec4(z.getX(), z.getY(), z.getZ(), z.dot(portal->getTransform().getPos()));
		printf("X: %f, Y: %f, Z: %f\n", plane.getX(), plane.getY(), plane.getZ());
		portalSceneShader->uniformVec4("clipPlane", &plane);
		for(auto* obj: *pipeline->objects){
			obj->render(*portalSceneShader);
		}
		glDisable(GL_CLIP_PLANE0);

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_TRUE);
		{ //Render portal to depth buffer
			portalShader->bind();
			mat4 viewprojection = camera->getViewProjection();
			portalShader->uniformMat4("vp", &viewprojection);
			vec3 campos = camera->transform.getPos().getCopy();
			portalShader->uniformVec3("viewpos", &campos);
			portal->render(*portalShader);
			basicShader->bind();
		}
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}
	glDisable(GL_STENCIL_TEST);
	basicShader->uniformMat4("depthvp", &pipeline->dl->getvp());

	mat4 viewprojection = camera->getViewProjection();
	basicShader->uniformMat4("vp", &viewprojection);
	vec3 campos = camera->transform.getPos().getCopy();
	basicShader->uniformVec3("viewpos", &campos);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF); // Pass the test if stencil value is 1
	glStencilMask(0x00); // Don't write to stencil buffer when drawing
	for(auto* obj: *pipeline->objects){
		obj->render(*basicShader);
	}
}

SceneStage::~SceneStage() {
	delete pre;
	delete basicShader;

}

void SceneStage::setCamera(Camera *camera) {
	this->camera = camera;
}

void SceneStage::reset() {
	pre->bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void SceneStage::bind() {
	RenderStage::bind();
	pre->bind();
}

void SceneStage::bindPortals(std::vector<PortalObj *> *portals) {
	this->portals = portals;

}
