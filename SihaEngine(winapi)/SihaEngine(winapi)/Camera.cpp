#include "common.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::setTarget(GameObject* target)
{
	this->target = target;
}

void Camera::init()
{
	this->target = nullptr;
	cameraPos = { 0, 0 };
}

void Camera::update()
{
	if(this->target != nullptr)
		cameraPos = target->pos;
}

void Camera::setPos(POINT pos)
{
	this->cameraPos = pos;
}

POINT Camera::getPos()
{
	return cameraPos;
}