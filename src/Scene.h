//
//  Scene.h
//  GoldFish
//
//  Created by 中川 慎哉 on 2015/06/20.
//  Copyright (c) 2015年 中川 慎哉. All rights reserved.
//

#ifndef __GoldFish__Scene__
#define __GoldFish__Scene__

class Scene {
public:
	virtual ~Scene(){}
	virtual Scene* Update() = 0;
	virtual void Draw() = 0;
protected:
	Scene* _scene;
};

#endif /* defined(__GoldFish__Scene__) */
