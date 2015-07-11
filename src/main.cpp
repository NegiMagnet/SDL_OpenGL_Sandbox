//
//  main.cpp
//  GoldFish
//
//  Created by 中川 慎哉 on 2015/06/20.
//  Copyright (c) 2015年 中川 慎哉. All rights reserved.
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/glu.h>

#include <iostream>
#include <string>

#include <cmath>

#include "ScStart.h"

static const std::string WINDOW_CAPTION = "SDL with OpenGL";
static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;

static const Uint32 FPS = 60;

static SDL_Window* window;
static SDL_GLContext context;

bool init();
bool finalize();

bool pollingEvent();

Scene* scene;

int main() {
	// initialize
	if (!init()) {
		std::cerr << "ERROR: failed to initialize SDL" << std::endl;
		exit(1);
	}
	
	// mainloop
	static const Uint32 interval = 1000 / FPS;
	static Uint32 nextTime = SDL_GetTicks() + interval;
	bool skipDraw = false;
	while (true) {
		// check event
		if (!pollingEvent()) break;
		
		// update and draw
		Scene* next = scene->Update();
		if(scene != next) {
			delete scene;
			scene = next;
		}
		if (!skipDraw) {
			scene->Draw();
			SDL_GL_SwapWindow(window);
		}
		
		int delayTime = (int)(nextTime - SDL_GetTicks());
		if (delayTime > 0) {
			SDL_Delay((Uint32)delayTime);
			skipDraw = false;
		} else {
			// skip next draw step because of no time
			skipDraw = true;
		}
		
		nextTime += interval;
	}
	
	// finalize
	finalize();
	return 0;
}

bool init() {
	// initialize SDL
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) return false;
	
	// enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	// create indow
	// set SDL_WINDOW_OPENGL to use opengl for drawing
	window = SDL_CreateWindow(WINDOW_CAPTION.c_str(),
							  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  WINDOW_WIDTH, WINDOW_HEIGHT,
							  SDL_WINDOW_OPENGL);
	if (!window) return false;
	
	// create OpenGL context
	context = SDL_GL_CreateContext(window);
	if (!context) return false;
	
	// setup viewport
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	
	// setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble) WINDOW_WIDTH / (GLdouble) WINDOW_HEIGHT, 2.0, 500.0);
	
	// setup light
	static GLfloat position[] = {-10.0f, 10.0f, 10.0f, 1.0f};
	static GLfloat ambient [] = { 1.0f, 1.0f, 1.0f, 1.0f};
	static GLfloat diffuse [] = { 1.0f, 1.0f, 1.0f, 1.0f};
	static GLfloat specular[] = { 0.0f, 0.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	scene = new ScStart();
	
	return true;
}

bool finalize() {
	// finalize SDL
	SDL_Quit();
	
	return true;
}
/*
void draw() {
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
*/
// polling event and execute actions
bool pollingEvent()
{
	SDL_Event ev;
	SDL_Keycode key;
	while ( SDL_PollEvent(&ev) )
	{
		switch(ev.type){
			case SDL_QUIT:
				// raise when exit event is occur
				return false;
				break;
			case SDL_KEYDOWN:
				// raise when key down
			{
				key = ev.key.keysym.sym;
				// ESC
				if(key == SDLK_ESCAPE){
					return false;
				}
			}
				break;
		}
	}
	return true;
}