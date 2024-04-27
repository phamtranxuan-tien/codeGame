#pragma once
#include "Function.h"

class Heart_Object :public base_Object //Đối tượng Máu kế thừa từ đối tượng cơ bản
{
private:
	int HP; //Thuộc tính HP đại diện cho máy bay chính còn máu hay hết máu
public:
	Heart_Object(); //Khởi tạo lớp đối tượng máu
	void CreateHeart(int, int, string); //Tạo đối tượng máu
	int GetHP(); //Lấy thuộc tính của HP
	void SetHP(int); //Cập nhật thuộc tính HP
};

