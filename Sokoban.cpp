/*
	Last edit:2020.2.8
	Author:赖朴然
	E-mail:1696095803@qq.com
	GitHub:Laipuran
*/
#pragma once

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <conio.h>
#include <Windows.h>

#define KEY_UP 0x48
#define KEY_DOWN 0x50
#define KEY_LEFT 0x4B
#define KEY_RIGHT 0x4D
#define W 0x77
#define A 0x61
#define S 0x73
#define D 0x64
#define ESC 0x1B
#define F4 0x3E

using namespace std;

int x = 0, y = 0;									//储存I坐标
int xl[5], yl[5];										//储存终点坐标
int bn = 0;											//储存箱子个数
int a = 0, b = 0;									//地图大小
int ct = 0;												//计数器
int ch = 0;											//输入
int t = 0;												//关数
int step = 0;											//步数
time_t start_t, end_t;								//计时器
string filename = "map1.map";				//文件名
bool flag = true, bo = true;					//判断器
char map[15][15] = {};							//地图

void add() {
	step++;
	end_t = time(NULL);
}

int main() {
	system("color F0");
	cout << setw(60) << "推箱子 Version 1.1 Copyright by 赖朴然\n" << endl;
	cout << "游戏规则：" << endl;
	cout << "把所有的目的地都用箱子压住即为成功" << endl;
	cout << "I是你自己\no是箱子\n#是障碍物\n";
	system("pause");
	system("cls");
	ifstream fin;
	for (t = 0; t < 3; t++) {
		bn = 0;
		switch (t) {
		case 0:
			filename[3] = '1';
			break;
		case 1:
			filename[3] = '2';
			break;
		case 2:
			filename[3] = '3';
			break;
		default:
			break;
		}
		cout << filename << endl;
		fin.open(filename);
		if (fin.fail()) {
			cout << "打开失败！" << endl;
			system("pause");
			return 0;
		}
		fin >> a;
		fin >> b;
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				fin >> map[i][j];
			}
		}
		fin.close();
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				switch (map[i][j]) {
				case '0':
					map[i][j] = '#';
					break;
				case '1':
					map[i][j] = ' ';
					break;
				case '2':
					map[i][j] = 'I';
					x = i;
					y = j;
					break;
				case '3':
					map[i][j] = 'o';
					bn++;
					break;
				case '4':
					map[i][j] = 'X';
					xl[ct] = i;
					yl[ct] = j;
					ct++;
					break;
				default:
					break;
				}
			}
		}
		ct = 0;
		step = 0;
		flag = true;
		while (flag) {
			cout << setw(60) << "第" << filename[3] << "关" << endl;
			for (int i = 0; i < a; ++i) {
				for (int j = 0; j < b; ++j) {
					cout << map[i][j] << " ";
				}
				if (i == 0)
					cout << "     " << "步数：" << step << "步";
				if (i == 1 && !bo)
					cout << "     " << "用时：" << difftime(end_t, start_t) << "秒";
				cout << endl;
			}
			cout << "使用上下左右键来控制移动" << endl;
			cout << "使用Esc键重试,F4退出" << endl;
			ch = _getch();
			if (bo) {
				start_t = time(NULL);
				bo = false;
			}
			if (ch == 224 || ch == 0) {
				ch = _getch();
			}
			switch (ch) {					//判断移动方向
			case KEY_UP:
			case W:
				if (map[x - 1][y] != '#' && map[x - 1][y] != 'o') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x - 1][y] = 'I';
					x -= 1;
				}
				if (map[x - 1][y] == 'o' && map[x - 2][y] != '#') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x - 1][y] = 'I';
					map[x - 2][y] = 'o';
					x -= 1;
				}
				add();
				break;
			case KEY_LEFT:
			case A:
				if (map[x][y - 1] != '#' && map[x][y - 1] != 'o') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x][y - 1] = 'I';
					y -= 1;
				}
				if (map[x][y - 1] == 'o' && map[x][y - 2] != '#') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x][y - 1] = 'I';
					map[x][y - 2] = 'o';
					y -= 1;
				}
				add();
				break;
			case KEY_DOWN:
			case S:
				if (map[x + 1][y] != '#' && map[x + 1][y] != 'o') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x + 1][y] = 'I';
					x += 1;
				}
				if (map[x + 1][y] == 'o' && map[x + 2][y] != '#') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x + 1][y] = 'I';
					map[x + 2][y] = 'o';
					x += 1;
				}
				add();
				break;
			case KEY_RIGHT:
			case D:
				if (map[x][y + 1] != '#' && map[x][y + 1] != 'o') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x][y + 1] = 'I';
					y += 1;
				}
				if (map[x][y + 1] == 'o' && map[x][y + 2] != '#') {
					while (ct < bn) {
						if (x == xl[ct] && y == yl[ct]) {
							map[x][y] = 'X';
							ct++;
						}
						else {
							map[x][y] = ' ';
							break;
						}
					}
					map[x][y + 1] = 'I';
					map[x][y + 2] = 'o';
					y += 1;
				}
				add();
				break;
			case ESC:
				system("cls");
				bo = true;
				main();
				break;
			case F4:
				system("pause");
				return 0;
				break;
			default:
				break;
			}
			while (ct < bn) {
				if (map[xl[ct]][yl[ct]] == 'o') {
					flag = false;
					ct++;
				}
				else {
					flag = true;
					break;
				}
			}
			ct = 0;
			system("cls");
		}
	}
	end_t = time(NULL);
	cout << "成功！你一共使用了" << difftime(end_t, start_t) << "秒" << endl;
	cout << "是否重来？（Y/N）";
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
		main();
	cout << "游戏结束" << endl;
	cout << "将要在3秒内关闭" << endl;
	Sleep(3000);
	return 0;
}
