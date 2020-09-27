#include <bangtal.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <time.h>

using namespace bangtal;
using namespace std;

int main()
{
	srand(time(NULL));//초기화
	auto scene = Scene::create("키키1", "images/background1.jpg");

	clock_t start, end;
	auto clickonbutton = false;
	auto startButton1 = Object::create("images/start.png", scene, 100, 0);
	startButton1->setScale(0.2f);
	startButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool
		{
			clickonbutton = true;
			startButton1->hide();
			start = clock();
			return true;
		});

	ObjectPtr pieces[9];
	ObjectPtr init_pieces[9];

	int blank = 8;
	for (int i = 0; i < 9; i++)
	{
		string pic_name = "images/p" + to_string(i + 1) + ".png";
		pieces[i] = Object::create(pic_name, scene, 265 + (i % 3) * 250, 500 - (i / 3) * 250);
		init_pieces[i] = pieces[i];
		pieces[i]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool
			{
				int j = 0;
				for (j = 0; j < 9; j++)
				{
					if (pieces[j] == object)
						break;
				}
				if ((j % 3 > 0 && j - 1 == blank) || (j % 3 < 2 && j + 1 == blank) || (j > 2 && j - 3 == blank) || (j < 6 && j + 3 == blank))
				{
					if (clickonbutton) {
						pieces[j]->locate(scene, 265 + (blank % 3) * 250, 500 - (blank / 3) * 250);
						pieces[blank]->locate(scene, 265 + (j % 3) * 250, 500 - (j / 3) * 250);

						pieces[j] = pieces[blank];
						pieces[blank] = object;
						blank = j;

						int k = 0;
						for (k = 0; k < 9; k++)
						{
							if (pieces[k] != init_pieces[k])
								break;
						}
						if (k == 9)
						{
							end = clock();
							cout << "How much time did you use: " << (float)(end - start) / CLOCKS_PER_SEC << std::endl;
							showMessage("다 맞췄다!");
						}
					}
				}

				return true;
			});
	}
	pieces[blank]->hide();

	auto timer = Timer::create(0.1f);
	auto count = 0;
	timer->setOnTimerCallback([&](TimerPtr timer)->bool
		{
			int j = 0;
			do {
				switch (rand() % 4) {
				case 0:
					j = blank - 1;
					break;//좌
				case 1:
					j = blank + 1;
					break;//우
				case 2:
					j = blank - 3;
					break;//상
				case 3:
					j = blank + 3;
					break;//하
				}
			} while (j < 0 || j >8 || !((j % 3 > 0 && j - 1 == blank) || (j % 3 < 2 && j + 1 == blank) || (j > 2 && j - 3 == blank) || (j < 6 && j + 3 == blank)));

			cout << blank << "," << j << endl;

			pieces[j]->locate(scene, 265 + (blank % 3) * 250, 500 - (blank / 3) * 250);
			pieces[blank]->locate(scene, 265 + (j % 3) * 250, 500 - (j / 3) * 250);

			auto object = pieces[j];
			pieces[j] = pieces[blank];
			pieces[blank] = object;
			blank = j;

			count++;
			if (count < 5)
			{
				timer->set(0.1f);
				timer->start();
			}
			return true;
		});

	timer->start();
	startGame(scene);
	return 0;
}
