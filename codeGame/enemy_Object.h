#pragma once
#include "Function.h"

class enemy_Object :public base_Object //Đối tượng Kẻ địch kế thừa từ đối tượng cơ bản
{
private:
	vector <bullet_Object> bullets; //Thuộc tính vector đạn đại diện cho các viên đạn mà kẻ địch sẽ bắn
public:
 	enemy_Object(); //Khởi tạo đối tượng kẻ địch
	void Move(); //Di chuyển kẻ địch trên màn hình
	void Destroy(vector <bullet_Object>&); //Loại bỏ đối tượng địch khi bị trúng đạn
	vector<bullet_Object> GetBullet(); //Lấy vector đạn của địch
	void SetBullet(vector <bullet_Object>); //Cập nhật vector đạn của địch
	void Shoot(); //phương thức bắn đạn của địch
};

