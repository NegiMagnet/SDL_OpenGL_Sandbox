//
//  ScStart.h
//  SDL_OpenGL_Sandbox
//
//  Created by 中川 慎哉 on 2015/07/12.
//  Copyright (c) 2015年 中川 慎哉. All rights reserved.
//

#ifndef __SDL_OpenGL_Sandbox__ScStart__
#define __SDL_OpenGL_Sandbox__ScStart__

#include "Scene.h"

class ScStart : public Scene {
public:
	virtual ~ScStart();
	virtual Scene* Update();
	virtual void Draw();
};

#endif /* defined(__SDL_OpenGL_Sandbox__ScStart__) */
