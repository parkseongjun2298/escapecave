#include "pch.h"
#include "Boss_head.h"

CBoss_head::CBoss_head() : Obj()
{
	info.Translate = { 0.f,8.f,0.f };
	info.Rotate = glm::vec3(0.f, 0.f, 0.f);
}

int CBoss_head::Update()
{
	info.Rotate.y += 5.f;
	return 0;
}