#pragma once
#include "pch.h"

typedef struct DataInfo {
	char infoindex;	// ��Ŷ Ÿ��
	char datasize;	// ��Ŷ ũ��
};

typedef struct ObjectInfo {
	glm::vec3 Translate;	//������Ʈ�� ��ǥ �̵� ���� ���Ͱ� ����
	glm::vec3 Rotate;	// ������Ʈ�� ȸ�� �� -> ���Ϳ��� ���
	char hp;		//������Ʈ�� ���� ü��. 0�� �� ������Ʈ ����
};