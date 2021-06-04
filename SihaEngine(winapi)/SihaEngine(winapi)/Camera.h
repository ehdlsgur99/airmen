#pragma once

#include "common.h"

class Camera : public CSingleton<Camera>
{
private:
	POINT cameraPos;
	
	GameObject* target;
public:
	Camera();
	~Camera();

	void setTarget(GameObject* target);

	void init();
	void update();

	void setPos(POINT pos);
	POINT getPos();
};

