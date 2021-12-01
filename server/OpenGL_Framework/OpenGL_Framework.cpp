#include "pch.h"
#include "CShader_Func.h"
#include "MainGame.h"
#include "server.h"
#include "tmp.h"
// 전역함수
GLvoid drawScene(GLvoid);
GLvoid ReShape(int w, int h);
// Func함수
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);

GLvoid Timer(int value);

// 셰이더 클래스 변수
CMainGame maingame;

glm::vec3 background = {0.0,0.0,0.0};

//좌표 보내는 쪽
Client client;
int main(int argc, char** argv)
{
	
	client.InitClient();	// 클라이언트로써 서버와 연결하는 함수
	client.Send_GameStart();	// 서버에게 게임 시작 요청
	


	srand(unsigned int(time(NULL)));

	glutInit(&argc, argv);		// GLUT openGL 환경 초기화
	// 더블 모드로 해야함
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 컬러모델, 윈도우 버퍼 등 초기의 출력 모드 결정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정 100, 100 떨어진 위치에 생성
	glutInitWindowSize(WINCX, WINCY); // 윈도우의 크기 지정
	int winID = glutCreateWindow("OpenGL기초"); // 윈도우 생성 윈도우의 아이디 리턴



	//////////////////////////////////////////////////////////////////////////////////////////////


	glewExperimental = GL_TRUE;		// GLEW 초기화

	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	////////////셰이더 관련////////////////////////
	maingame.Initialize_MainGame();

	//////////////////////////////////////////////

	glutDisplayFunc(drawScene);
	glutReshapeFunc(ReShape);

	// 여기서 이벤트 처리함수 추가
	glutMouseFunc(Mouse);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(10, Timer, TIMER_MAIN);
	glutTimerFunc(ADD_TIME, Timer, TIMER_ADD);

	glutMainLoop(); // 이벤트 처리 시작 중요!!!!!!! 종료하라는 명령어 들어올때까지 실행한다
	//glutLeaveMainLoop(); // 이벤트 프로세싱을 종료(프로그램 종료)


}
GLvoid Brighter()
{
	if (background.x < 1.f) {
		background.x += 0.01f;
		background.y += 0.01f;
		background.z += 0.01f;

	}
	
}
GLvoid drawScene(GLvoid)
{
	glClearColor(background.x, background.y, background.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/////// 셰이더
	ResetEvent(hSynchro);	//클라이언트로부터 키 입력이 와도 오브젝트 업데이트까지 적용 대기시킨다.
	maingame.Update_MainGame();

	SetEvent(hSynchro);	//클라이언트의 키 입력에 대한 적용을 허용한다.
	maingame.Draw_MainGame();
	maingame.Late_Update();

	client.Send_Object_Info();

	glutPostRedisplay();

	glutSwapBuffers();
}

GLvoid ReShape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Mouse(int button, int state, int x, int y)
{
	return GLvoid();
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		
		break;
	default:
		break;
	}
}

GLvoid SpecialKeyboard(int key, int x, int y)
{


	
	glutPostRedisplay();
}

GLvoid Timer(int value)
{
	// 메인루프
	if (TIMER_MAIN == value) {
		glutTimerFunc(10, Timer, TIMER_MAIN);
		glutPostRedisplay();
		if (maingame.Get_NowStage() == maingame.STAGE_END) {
			// 배경 점점 밝게
			Brighter();
		}

	}
	if (TIMER_ADD == value) {
		//maingame.Add_Object(OBJID::PLAYER);
		//maingame.Add_Object(OBJID::MONSTER);
		//maingame.Add_Object(OBJID::MAP);
		//glutTimerFunc(ADD_TIME, Timer, TIMER_ADD);

	}

}
