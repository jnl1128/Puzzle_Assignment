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
	auto background1 = Scene::create("1단계", "images/back.jpg");
	auto backobject1 = Object::create("images/back.jpg", background1,265,-300);
	auto background2 = Scene::create("2단계", "images/.jpg");
	auto backobject2 = Object::create("images/background2.jpg", background2, 265, -300);
	//좌표 생성
	int blank_x = 765;
	int blank_y = 0;
	int grid[8][3] = { { 265, 500, },  { 515, 500, } , { 765, 500, }, { 265,250, }, { 515,250, }, { 765, 250, }, { 265, 0, }, { 515, 0, } };
	int position[8][2] = { 0, };
	//좌표 랜덤 설정
	int bFound;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 8; ++i){
		while (1){
			grid[i][2] = rand() % 8 + 1;
			bFound = 0;
			for (int j =0; j < i; ++j){
				if (grid[j][2] == grid[i][2]){
					bFound = 1;
					break;
		
				}
			}
			if (!bFound) break;
		}
	}
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (grid[j][2] == i+1){
				position[i][0] = grid[j][0];
				position[i][1] = grid[j][1];
			}	
		}
	}
	//퍼즐 조각 생성//p:background1조각, pp:background2조각
	auto p1 = Object::create("images/p1.png", background1,position[0][0], position[0][1]);
	auto p2 = Object::create("images/p2.png", background1, position[1][0], position[1][1]);
	auto p3 = Object::create("images/p3.png", background1, position[2][0], position[2][1]);
	auto p4 = Object::create("images/p4.png", background1, position[3][0], position[3][1]);
	auto p5 = Object::create("images/p5.png", background1,position[4][0], position[4][1]);
	auto p6 = Object::create("images/p6.png", background1, position[5][0],position[5][1]);
	auto p7 = Object::create("images/p7.png", background1,position[6][0], position[6][1]);
	auto p8 = Object::create("images/p8.png", background1, position[7][0], position[7][1]);
	auto pp1 = Object::create("images/pp1.png", background2, position[0][0], position[0][1]);
	auto pp2 = Object::create("images/pp2.png", background2, position[1][0], position[1][1]);
	auto pp3 = Object::create("images/pp3.png", background2, position[2][0], position[2][1]);
	auto pp4 = Object::create("images/pp4.png", background2, position[3][0], position[3][1]);
	auto pp5 = Object::create("images/pp5.png", background2, position[4][0], position[4][1]);
	auto pp6 = Object::create("images/pp6.png", background2, position[5][0], position[5][1]);
	auto pp7 = Object::create("images/pp7.png", background2, position[6][0], position[6][1]);
	auto pp8 = Object::create("images/pp8.png", background2, position[7][0], position[7][1]);
	//조각 이벤트 설정
	p1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[0][0], position[0][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[0][0], &position[0][1], &blank_x, &blank_y);
				p1->locate(background1, position[0][0], position[0][1]);
			}
 			return true;
		});
	pp1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
				if (closeToblank(position[0][0], position[0][1], blank_x, blank_y, 250)){
					switch_puzzle(&position[0][0], &position[0][1], &blank_x, &blank_y);
					pp1->locate(background2, position[0][0], position[0][1]);
				}
				return true;
			});
	
	p2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[1][0], position[1][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[1][0], &position[1][1], &blank_x, &blank_y);
				p2->locate(background1, position[1][0], position[1][1]);
			}
			return true;
		});
	pp2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[1][0], position[1][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[1][0], &position[1][1], &blank_x, &blank_y);
			pp2->locate(background2, position[1][0], position[1][1]);
		}
		return true;
		});
	p3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
		if (closeToblank(position[2][0], position[2][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[2][0], &position[2][1], &blank_x, &blank_y);
				p3->locate(background1, position[2][0], position[2][1]);
			}
			return true;
		});
	pp3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[2][0], position[2][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[2][0], &position[2][1], &blank_x, &blank_y);
			pp3->locate(background2, position[2][0], position[2][1]);
		}
		return true;
		});
	p4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[3][0], position[3][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[3][0], &position[3][1], &blank_x, &blank_y);
				p4->locate(background1, position[3][0], position[3][1]);
			}
 			return true;
		});
	pp4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[3][0], position[3][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[3][0], &position[3][1], &blank_x, &blank_y);
			pp4->locate(background2, position[3][0], position[3][1]);
		}
		return true;
		});
	p5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[4][0], position[4][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[4][0], &position[4][1], &blank_x, &blank_y);
				p5->locate(background1, position[4][0], position[4][1]);
			}
			return true;
		});
	pp5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[4][0], position[4][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[4][0], &position[4][1], &blank_x, &blank_y);
			pp5->locate(background2, position[4][0], position[4][1]);
		}
		return true;
		});
	p6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[5][0], position[5][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[5][0], &position[5][1], &blank_x, &blank_y);
				p6->locate(background1, position[5][0], position[5][1]);
			}
			return true;
		});
	pp6->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[5][0], position[5][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[5][0], &position[5][1], &blank_x, &blank_y);
			pp6->locate(background2, position[5][0], position[5][1]);
		}
		return true;
		});
	p7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[6][0], position[6][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[6][0], &position[6][1], &blank_x, &blank_y);
				p7->locate(background1, position[6][0], position[6][1]);
			}
			return true;
		});
	pp7->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[6][0], position[6][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[6][0], &position[6][1], &blank_x, &blank_y);
			pp7->locate(background2, position[6][0], position[6][1]);
		}
		return true;
		});
	p8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool{
			if (closeToblank(position[7][0], position[7][1], blank_x, blank_y, 250)){
				switch_puzzle(&position[7][0], &position[7][1], &blank_x, &blank_y);
				p8->locate(background1, position[7][0], position[7][1]);
			}
			return true;
		});
	pp8->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		if (closeToblank(position[7][0], position[7][1], blank_x, blank_y, 250)) {
			switch_puzzle(&position[7][0], &position[7][1], &blank_x, &blank_y);
			pp8->locate(background2, position[7][0], position[7][1]);
		}
		return true;
		});
	//시작버튼, 버저버튼, 다음 단계버튼
	auto startButton = Object::create("images/start.png", background1, 100, 0);
	startButton->setScale(0.2f);
	auto startButton2 = Object::create("images/start.png", background2, 100, 0);
	startButton2->setScale(0.2f);
	auto nextButton = Object::create("images/next.png", background1, 100, 0);
	nextButton->setScale(0.2f);
	auto buzzerButton = Object::create("images/buzzer.png", background1, 90, 200,false);
	buzzerButton->setScale(0.22f);
	auto buzzerButton2 = Object::create("images/buzzer.png", background2, 90, 200, false);
	buzzerButton2->setScale(0.22f);
	//초시계 생성
	clock_t start1,start2, end1, end2;
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			startButton->hide();
			buzzerButton->show();
			start1 = clock();
			return true;
		});
	startButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			startButton2->hide();
			buzzerButton2->show();
			start2 = clock();
			return true;
		});
	nextButton -> setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			background1->enter();
			startButton2->show();
			return true;
		});
	//성공 조건
	buzzerButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			int count = 0;//제 위치 찾은 조각 개수
			for (int i = 0; i < 8; i++)
			{
				if (position[i][0] == grid[i][0] && position[i][1] == grid[i][1]) count++;
			}
			if (count == 8)
			{
				end1 = clock();
				nextButton->show();
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
				if (position[i][0] == grid[i][0] && position[i][1] == grid[i][1]) count++;
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
	// 종료 조건
	backobject1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			endGame();
			return true;
		});

	//게임 시작
	startGame(background1);
	return 0;
}