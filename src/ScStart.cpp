//
//  ScStart.cpp
//  SDL_OpenGL_Sandbox
//
//  Created by 中川 慎哉 on 2015/07/12.
//  Copyright (c) 2015年 中川 慎哉. All rights reserved.
//

#include "ScStart.h"
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>

ScStart::~ScStart() {}

Scene* ScStart::Update() {
	return this;
}

void ScStart::Draw() {
	// clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// setup view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( 0.0f,  0.0f,-30.0f,
			  0.0f,  0.0f, 0.0f,
			  0.0f, -1.0f, 0.0f);
	
	// setup material
	GLfloat ambient  [] = { 0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat diffuse  [] = { 1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat specular [] = { 1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shininess[] = { 0.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	
	// draw sphere
	GLUquadric* quadric = gluNewQuadric();
	gluSphere(quadric, 10.0, 30, 30);
	gluDeleteQuadric(quadric);
}