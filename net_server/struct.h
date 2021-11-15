#pragma once
#include "pch.h"

typedef struct DataInfo {
	char infoindex;	// 패킷 타입
	char datasize;	// 패킷 크기
};

typedef struct ObjectInfo {
	glm::vec3 Translate;	//오브젝트의 좌표 이동 위한 벡터값 저장
	char hp;		//오브젝트의 남은 체력. 0일 시 오브젝트 제거
};