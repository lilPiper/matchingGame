#pragma once
#include<iostream>
#include<vector>
#define MXH 6
#define MXL 6
typedef int Pos;
typedef int WTNum;
typedef int ScoreN;
class AIn {
	friend class Fun;
private:
	WTNum water;
	Pos p_l, p_h;
	//vector< vector<int > > arr;
	ScoreN Plus;
	static AIn* m_pInstance;
	AIn() = delete;
	//AIn(int x) :arr(MXH) {};
	void static createAIn(AIn* p);
public:
	static AIn* GetInstance();

	bool setPos();
	Pos getPosX();
	Pos getPosY();
	void getArrSizeAndScr();
			//输出二维数组 
	void dispArr();

		
	bool AddArrN(Pos x, Pos y);
	bool setPlusZ();
	ScoreN getPlus();
	WTNum getWater();
	
	bool setWater(int m);
	
	bool setPos(Pos l, Pos h);
	~AIn() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
};


class Fun {

public:
	Fun() = default;

	void firstSetMap();
	void Tvs(Pos x, Pos y);
public:
	//判断全局是否需要重新生成
	bool isGameOver(AIn* p);
	
};
