#include <bangtal.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace bangtal;

bool closeToblank(int x, int y, int blankX, int blankY, int dis)//빈칸 옆에 있는 퍼즐 조각인지 판단하기 위한 함수
{
	return (((x - blankX == dis || blankX - x == dis) && (y == blankY))|| (x == blankX) && (y-blankY == dis || blankY - y == dis));
}
void switch_puzzle(int *x, int *y, int *blankX, int *blankY)
{
	int temp[2] = { *x,*y };
	*x = *blankX;
	*y = *blankY;
	*blankX = temp[0];
	*blankY = temp[1];

}

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	//배경 생성
	auto firstbackground = Scene::create("퍼즐월드", "images/firstbackground.png");
	showMessage("Welcome to puzzleWorld~!\n 어느 퍼즐을 맞출건지 골라줘!");
	auto background1 = Scene::create("No.1", "images/.jpg");
	auto backobject1 = Object::create("images/background1.jpg", background1,265,-300);
	auto background2 = Scene::create("No.2", "images/.jpg");
	auto backobject2 = Object::create("images/background2.jpg", background2, 265, -300);
	//좌표 생성
	int blank_x1 = 765;
	int blank_y1 = 0;
	int blank_x2 = 765;
	int blank_y2 = 0;
	int grid1[8][3] = { { 265, 500, },  { 515, 500, } , { 765, 500, }, { 265,250, }, { 515,250, }, { 765, 250, }, { 265, 0, }, { 515, 0, } };
	int grid2[8][3] = { { 265, 500, },  { 515, 500, } , { 765, 500, }, { 265,250, }, { 515,250, }, { 765, 250, }, { 265, 0, }, { 515, 0, } };
	int position1[8][2] = { 0, };
	int position2[8][2] = { 0, };
	//퍼즐1 좌표 랜덤생성
	int bFound1, bFound2;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 8; ++i) {
		while (1) {
			grid1[i][2] = rand() % 8 + 1;
			bFound1 =0;
			for (int j = 0; j < i; ++j) {
				if (grid1[j][2] == grid1[i][2]) {
					bFound1 = 1;
					break;
				}
			}
			if (!bFound1) break;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid1[j][2] == i + 1) {
				position1[i][0] = grid1[j][0];
				position1[i][1] = grid1[j][1];
			}
		}
	}
	//퍼즐2 좌표 랜덤생성
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 8; ++i) {
		while (1) {
			grid2[i][2] = rand() % 8 + 1;
			bFound2 = 0;
			for (int j = 0; j < i; ++j) {
				if (grid2[j][2] == grid2[i][2]) {
					bFound2 = 1;
					break;
				}
			}
			if (!bFound2) break;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (grid2[j][2] == i + 1) {
				position2[i][0] = grid2[j][0];
				position2[i][1] = grid2[j][1];
			}
		}
	}
	//조각
	auto p1 = Object::create("images/p1.png", background1, position1[0][0], position1[0][1]);
	auto p2 = Object::create("images/p2.png", background1, position1[1][0], position1[1][1]);
	auto p3 = Object::create("images/p3.png", background1, position1[2][0], position1[2][1]);
	auto p4 = Object::create("images/p4.png", background1, position1[3][0], position1[3][1]);
	auto p5 = Object::create("images/p5.png", background1, position1[4][0], position1[4][1]);
	auto p6 = Object::create("images/p6.png", background1, position1[5][0], position1[5][1]);
	auto p7 = Object::create("images/p7.png", background1, position1[6][0], position1[6][1]);
	auto p8 = Object::create("images/p8.png", background1, position1[7][0], position1[7][1]);
	auto pp1 = Object::create("images/pp1.png", background2, position2[0][0], position2[0][1]);
	auto pp2 = Object::create("images/pp2.png", background2, position2[1][0], position2[1][1]);
	auto pp3 = Object::create("images/pp3.png", background2, position2[2][0], position2[2][1]);
	auto pp4 = Object::create("images/pp4.png", background2, position2[3][0], position2[3][1]);
	auto pp5 = Object::create("images/pp5.png", background2, position2[4][0], position2[4][1]);
	auto pp6 = Object::create("images/pp6.png", background2, position2[5][0], position2[5][1]);
	auto pp7 = Object::create("images/pp7.png", background2, position2[6][0], position2[6][1]);
	auto pp8 = Object::create("images/pp8.png", background2, position2[7][0], position2[7][1]);
	//시작버튼, 버저버튼, 전 단계로 가는 버튼
	auto clickonbutton = false;
	auto step1 = Object::create("images/one.jpg", firstbackground, 300, 300);
	auto step2 = Object::create("images/two.jpg", firstbackground, 800, 300);
	auto startButton1 = Object::create("images/start.png", background1, 100, 0);
	startButton1->setScale(0.2f);
	auto startButton2 = Object::create("images/start.png", background2, 100, 0);
	startButton2->setScale(0.2f);
	auto returnButton1 = Object::create("images/return.png", background1, 100, 0, false);
	returnButton1->setScale(0.2f);
	auto returnButton2 = Object::create("images/return.png", background2, 100, 0, false);
	returnButton2->setScale(0.2f);
	auto buzzerButton1 = Object::create("images/buzzer.png", background1, 90, 200, false);
	buzzerButton1->setScale(0.22f);
	auto buzzerButton2 = Object::create("images/buzzer.png", background2, 90, 200, false);
	buzzerButton2->setScale(0.22f);

	//퍼즐 고르기
	step1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			background1->enter();
			startButton1->show();
			returnButton1->hide();
			return true;
		});
	step2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			background2->enter();
			startButton2->show();
			returnButton2->hide();
			return true;
		});

	//전 단계로 돌아가기
	returnButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			clickonbutton = false;
			buzzerButton1->hide();
			firstbackground->enter();
			return true;
		});
	returnButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			clickonbutton = false;
			buzzerButton2->hide();
			firstbackground->enter();
			return true;
		});

	//버튼 이동 가능한 조건 생서 및 초시계 작동
	clock_t start1, start2, end1, end2;
	startButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			clickonbutton = true;
			startButton1->hide();
			returnButton1->show();
			buzzerButton1->show();
			start1 = clock();
			return true;
		});
	startButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			clickonbutton = true;
			startButton2->hide();
			returnButton2->show();
			buzzerButton2->show();
			start2 = clock();
			return true;
		});
	
	//성공 조건
	buzzerButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			int count = 0;//제 위치 찾은 조각 개수
			for (int i = 0; i < 8; i++)
			{
				if (position1[i][0] == grid1[i][0] && position1[i][1] == grid1[i][1]) count++;
			}
			if (count == 8)
			{
				end1 = clock();
				showMessage("퍼즐 다 맞췄다!");
				std::cout << "How much time did you use: " << (float)(end1 - start1) / CLOCKS_PER_SEC << std::endl;

			}
			else showMessage("아직 다 맞추지 못했어!");
			return true;
		});
	buzzerButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			int count = 0;//제 위치 찾은 조각 개수
			for (int i = 0; i < 8; i++)
			{
				if (position2[i][0] == grid2[i][0] && position2[i][1] == grid2[i][1]) count++;
			}
			if (count == 8)
			{
				end2 = clock();
				showMessage("퍼즐 다 맞췄다!\nMisson Complete");
				std::cout << "How much time did you use: " << (float)(end2 - start2) / CLOCKS_PER_SEC << std::endl;
				if ((end2 - start2) < (end1 - start1)) {
					std::cout << "You did faster than before!" << std::endl; //저번 단계보다 빨라졌을 경우
				}
			}
			else showMessage("아직 다 맞추지 못했어!");

			return true;
		});

	//조각 이벤트 설정
		p1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[0][0], position1[0][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[0][0], &position1[0][1], &blank_x1, &blank_y1);
				if (clickonbutton) p1->locate(background1, position1[0][0], position1[0][1]);
			}
			return true;
			});
		pp1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[0][0], position2[0][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[0][0], &position2[0][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp1->locate(background2, position2[0][0], position2[0][1]);
			}
			return true;
			});
		p2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[1][0], position1[1][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[1][0], &position1[1][1], &blank_x1, &blank_y1);
				if (clickonbutton) p2->locate(background1, position1[1][0], position1[1][1]);
			}
			return true;
			});
		pp2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[1][0], position2[1][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[1][0], &position2[1][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp2->locate(background2, position2[1][0], position2[1][1]);
			}
			return true;
			});
		p3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[2][0], position1[2][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[2][0], &position1[2][1], &blank_x1, &blank_y1);
				if (clickonbutton) p3->locate(background1, position1[2][0], position1[2][1]);
			}
			return true;
			});
		pp3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[2][0], position2[2][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[2][0], &position2[2][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp3->locate(background2, position2[2][0], position2[2][1]);
			}
			return true;
			});
		p4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[3][0], position1[3][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[3][0], &position1[3][1], &blank_x1, &blank_y1);
				if (clickonbutton) p4->locate(background1, position1[3][0], position1[3][1]);
			}
			return true;
			});
		pp4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[3][0], position2[3][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[3][0], &position2[3][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp4->locate(background2, position2[3][0], position2[3][1]);
			}
			return true;
			});
		p5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[4][0], position1[4][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[4][0], &position1[4][1], &blank_x1, &blank_y1);
				if (clickonbutton) p5->locate(background1, position1[4][0], position1[4][1]);
			}
			return true;
			});
		pp5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[4][0], position2[4][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[4][0], &position2[4][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp5->locate(background2, position2[4][0], position2[4][1]);
			}
			return true;
			});
		p6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[5][0], position1[5][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[5][0], &position1[5][1], &blank_x1, &blank_y1);
				if (clickonbutton) p6->locate(background1, position1[5][0], position1[5][1]);
			}
			return true;
			});
		pp6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[5][0], position2[5][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[5][0], &position2[5][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp6->locate(background2, position2[5][0], position2[5][1]);
			}
			return true;
			});
		p7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[6][0], position1[6][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[6][0], &position1[6][1], &blank_x1, &blank_y1);
				if (clickonbutton) p7->locate(background1, position1[6][0], position1[6][1]);
			}
			return true;
			});
		pp7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[6][0], position2[6][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[6][0], &position2[6][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp7->locate(background2, position2[6][0], position2[6][1]);
			}
			return true;
			});
		p8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position1[7][0], position1[7][1], blank_x1, blank_y1, 250)) {
				switch_puzzle(&position1[7][0], &position1[7][1], &blank_x1, &blank_y1);
				if (clickonbutton) p8->locate(background1, position1[7][0], position1[7][1]);
			}
			return true;
			});
		pp8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
			if (closeToblank(position2[7][0], position2[7][1], blank_x2, blank_y2, 250)) {
				switch_puzzle(&position2[7][0], &position2[7][1], &blank_x2, &blank_y2);
				if (clickonbutton) pp8->locate(background2, position2[7][0], position2[7][1]);
			}
			return true;
			});

	// 종료 조건
	backobject1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (clickonbutton) endGame();
			return true;
		});
	backobject2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			if (clickonbutton) endGame();
			return true;
		});

	//게임 시작
	startGame(firstbackground);
	return 0;
}