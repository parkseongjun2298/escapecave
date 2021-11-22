#pragma once
#include "pch.h"

typedef struct DataInfo {
	char infoindex;	
	char datasize;	
};

typedef struct modelTransform
{
	glm::vec3 Scale{ 1.f, 1.f, 1.f };
	glm::vec3 Rotate{ 0.f, 0.f, 0.f };
	glm::vec3 Translate{ 0.f, 0.f, 0.f };
	glm::vec3 Revolution{ 0.f, 0.f, 0.f };
	glm::vec3 pivot{ 0.f,0.f,0.f };
	glm::vec3 origin_Translate{ 0.f, 0.f, 0.f };
	modelTransform* Parent = nullptr;

	glm::mat4 matWorld;
}MODEL_TRANSFORM;

typedef struct ObjectInfo {
	glm::vec3 Translate;	
	char hp;		

	MODEL_TRANSFORM model_transform;
};