﻿#include <bangtal.h>
using namespace bangtal;

int main()
{
	auto scene1 = Scene::create("룸1", "images/배경-1.png");
	auto scene2 = Scene::create("룸2", "images/배경-2.png");

	auto key = Object::create("images/열쇠.png", scene1, 600, 150);
	key->setScale(0.2f);

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});

	auto flowerpot_moved = false;
	auto flowerpot = Object::create("images/화분.png", scene1, 550, 150);
	flowerpot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (flowerpot_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				flowerpot->locate(scene1, 450, 150);
				flowerpot_moved == true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				flowerpot->locate(scene1, 650, 150);
				flowerpot_moved == true;
			}
		}

		return true;
		});
	auto open1 = false;
	auto door1 = Object::create("images/문-오른쪽-닫힘.png", scene1, 800, 270);

	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open1 == true) {
			scene2->enter();
		}
		else if (key->isHanded()) {
			door1->setImage("images/문-오른쪽-열림.png");
			open1 = true;
		}
		else {
			showMessage("열쇠가 없잖아!!");
		}

		return true;
		});

	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto open3 = false, locked3 = true;
	auto door3 = Object::create("images/문-오른쪽-닫힘.png", scene2, 910, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (locked3) {
			showMessage("문이 잠겨있어!");
		}

		else if (open3) {
			endGame();
		}
		else  {
			door3->setImage("images/문-오른쪽-열림.png");
			open3 = true;
		}
		return true;
		});

	door3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked3 = false;
		showMessage("짜잔~");

		return true;
		});

	auto keypad = Object::create("images/키패드.png", scene2, 885, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("BANGTAL", door3);
		return true;
		});

	auto password = Object::create("images/암호.png", scene2, 400, 100, false);

	auto lighted = true;
	auto button = Object::create("images/스위치.png", scene2, 880, 440);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {
			scene2->setLight(0.2f);
			password->show();
			lighted = false;
		}
		else {
			scene2->setLight(1.0f);
			password->hide();
			lighted = true;
		}
		return true;
		});

		startGame(scene1);
		return 0;
}