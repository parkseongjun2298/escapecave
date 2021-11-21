#pragma once
namespace PLAYER
{
	enum BODY { UNDER, CENTER, LEFT_ARM, RIGHT_ARM, BODY_END };
	enum DIR {FRONT, BACK, LEFT, RIGHT};
}
struct Tree {
	OBJECT branch;
	OBJECT Grass;
};
struct Running_Machine {
	OBJECT bottom;
	OBJECT left_Side;
	OBJECT right_Side;
	OBJECT top;
	//OBJECT 
};
enum RUNNING { RUNNING_BODY, RUNNING_LEFTLEG, RUNNING_RIGHTLEG, RUNNING_END };

class CShader_Func
{
public:
	CShader_Func();
	~CShader_Func();

public:
	
	// 1. drawScene함수에서 그리기 for문으로
	// 2. make_vertexShader()
	// 3. make_fragmentShader()
	// 4. InitBuffer()
	// 5. InitShader()

	// 초기화
	void Initialize_Shader();
	void make_vertexShader();
	void make_fragmentShader();
	void Init_Objects();
	void Init_Machines();

	// 업데이트
	void Update();
	void Update_Buffer(int _vindex, glm::vec3 Shape_pos[], glm::vec3 shape_color[], size_t _size);
	void Update_Buffer(int _vindex, vector<glm::vec3> _vertices, vector<glm::vec3> _color);
	void Update_Shader();
	void Call_Vao();

	// 카메라 이동 함수
	void Move_Camera(glm::vec3 _moveSize);
	void Rotate_Camera(GLfloat _dir);
	// 모델변환 적용
	void Set_ModelTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_ModelTransform_Parent(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_ArmModelTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_ModelTransform_pullbarMan(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_LegTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_RailTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_PlayerTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);
	void Set_PlayerArmTransform(MODEL_TRANSFORM _modelTransform, unsigned int _modelLocation);



	// 18번 함수
	GLboolean Open_Stage();
	void Walk_Player(glm::vec3 _moveSize, PLAYER::DIR _dir);
	// 로봇 함수
	void Rotate_Arms();
	GLboolean Jump();
	// 모든 변환 리셋
	void Reset_All();
	void Collision_Check();

	// 19번 함수
	void Upate_Machines();
	void Set_nowDir(PLAYER::DIR _eDir) { _nowDir = _eDir; }
private:
	GLchar* vertexsource, * fragmentsource; // 소스코드 저장 변수
	GLuint vertexshader, fragmentshader; // 세이더 객체
	GLuint s_program;
	//TRIANGLE triShape[TRINUM];
	//CUBE cubeShape[CUBENUM];
	//LINE lineShape[LINENUM];
	GLuint vao[100], vbo[100][2];
	GLenum ePolygonMode = GL_FILL;
	CAMERA_DESC m_Camera_Desc;
	GLfloat m_Camera_Rotate_Angle = 0.f;
	glm::vec3 Camera_Pos{ 0.f, 3.f, 25.f };

	GLboolean bGenerate = false;
	// obj 불러오기
	// 여기에 넣는다.
	// 각 객체는 좌표가 있다.
	OBJECT stage;
	OBJECT stage_front;
	GLfloat m_YMove_Cnt = 0.f;
	
	// 로봇 만들기

	//Test 팔회전 시키는 거 중심을 끝으로 두고 해보기
	OBJECT leftArm, rightArm;
	OBJECT leftLeg, rightLeg;
	OBJECT Body, Head, Nose;

	// arm
	GLboolean bRotate_Dir = true;

	// jump
	GLboolean bJumpUp = true;

	// 러닝머신
	OBJECT running_machine;
	OBJECT running_machine_rail;

	// 나무
	Tree tree;
	GLboolean tree_Size = true;

	// 철봉
	OBJECT pullbar;
	OBJECT pullbarMan;

	// 러닝에서 달리는 애
	OBJECT runningMan[RUNNING_END];
	GLboolean running_Size = true;

	// 벤치프레스
	OBJECT bench;
	OBJECT weights;
	OBJECT benchMan;
	OBJECT benchArm[2];
	OBJECT benchHand[2];

	GLboolean press_size = true;

	// 중간 충돌체
	OBJECT mid_cube;

	PLAYER::DIR _nowDir;

	GLuint object_number = 0;
};

