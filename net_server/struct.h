#pragma once
#include "pch.h"

typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��
};

typedef struct ObjectInfo {
	glm::vec3 Translate;	//������Ʈ�� ��ǥ �̵� ���� ���Ͱ� ����
	char hp;		//������Ʈ�� ���� ü��. 0�� �� ������Ʈ ����
};