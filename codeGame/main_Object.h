#pragma once
#include "base_Object.h"
#include "bullet_Object.h"
#include "enemy_Object.h"
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>
#include "Heart_Object.h"

using namespace std;

class main_Object:public base_Object //class main_Object duoc ke thua tu class base_Object
{
private:
	vector <Heart_Object> Mau; //Thuoc tinh dai dien cho mau cua main object
	vector <bullet_Object> bullets; //Thuoc tinh dai dien cho dan
public:
	main_Object(); //Ham khoi tao mac dinh;
	~main_Object(); //Phuong thuc pha huy
	void Move(); //Ham di chuyen
	void Action(SDL_Event); //Kiem tra huong di chuyen va cap nhat khoang cach doi tuong di bao xa
	vector<bullet_Object> GetBullet(); //Lay vector dan
	void SetBullet(vector <bullet_Object>); //Cap nhat vector dan
	void Shoot(); //Ham ban dan 
	void Crush(vector <enemy_Object>&); //Kiem tra va cham voi dich va cap nhat lai ke dich
	void Crush(vector <bullet_Object>&); //Kiem tra va cham voi dan
	void Damage(); //Gây thiệt hại lên máu của đối tượng chính khi va chạm
	void DamageEnemy(vector <enemy_Object>); //Gây thiệt hại lên máu của đối tượng chính khi máy bay địch đi quá phạm vi cần bảo vệ 

	vector <Heart_Object> GetMau(); //Lấy vector máu của đối tượng chính
	void SetMau(vector <Heart_Object>); //Cập nhật vector máu của đối tượng chính
	void CreateMau(); //Tạo vector máu của đối tượng chính
	void DestroyMau(); //Làm giảm máu của đối tượng chính bằng cách chỉnh thuộc tính HP và hình ảnh của các đối tượng máu trong vector máu
	void DrawMau(); //Vẽ vector máu lên màn hình
};

