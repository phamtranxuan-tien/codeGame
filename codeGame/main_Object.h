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
	vector <Heart_Object> Mau; //Thuộc tính vector Máu đại diện cho số máu và trạng thái máu của đối tượng chính
	vector <bullet_Object> bullets; //Thuộc tính vector Đạn đại diện cho số đạn mà đối tượng chính có
public:
	main_Object(); //Khởi tạo đối tượng chính;
	~main_Object(); //Phá hủy đối tượng chính
	void Move(); //Di chuyển đối tượng chính
	void Action(SDL_Event); //Cập nhật các giá trị chuyển động, bắn cho đối tượng chính bằng các phím trên bàn phím
	vector<bullet_Object> GetBullet(); //Lấy vector đạn của đối tượng chính
	void SetBullet(vector <bullet_Object>); //Cập nhật vector đạn của đối tượng chính
	void Shoot(); //Đối tượng chính bắn đạn
	void Crush(vector <enemy_Object>&); //Kiểm tra va chạm đối tượng chính với đạn của địch
	void Crush(vector <bullet_Object>&); //Kiểm tra va chạm đối tượng chính với kẻ địch
	void Damage(); //Gây thiệt hại lên máu của đối tượng chính khi va chạm
	void DamageEnemy(vector <enemy_Object>); //Gây thiệt hại lên máu của đối tượng chính khi máy bay địch đi quá phạm vi cần bảo vệ 

	vector <Heart_Object> GetMau(); //Lấy vector máu của đối tượng chính
	void SetMau(vector <Heart_Object>); //Cập nhật vector máu của đối tượng chính
	void CreateMau(); //Tạo vector máu của đối tượng chính
	void DestroyMau(); //Làm giảm máu của đối tượng chính bằng cách chỉnh thuộc tính HP và hình ảnh của các đối tượng máu trong vector máu
	void DrawMau(); //Vẽ vector máu lên màn hình
};

