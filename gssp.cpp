//加 SCORE/LEVEL
//#include "gssp.h"
#include <iostream>
#include <vector>
#define MXH 6
#define MXL 6
#include <ctime>

//using namespace std;
typedef int Pos;
typedef int WTNum;
typedef int ScoreN;
typedef long int ScoreLN;
typedef int RNum;
class AIn {
	friend class Fun;
private:
	WTNum water; //滴管毫升数
	Pos p_l, p_h;
	std::vector< std::vector<int > > arr; //对象成员，用二维向量实现水滴的存储
	ScoreN Plus;
	ScoreLN sumSc;
	RNum round;
	static AIn* m_pInstance;
	AIn() = delete;
	AIn(int x):arr(MXH) {
		for (int i = 0; i < MXH; i++) {
			arr[i].resize(MXH);
		}
	}
	void static createAIn(AIn *p) {
		p->water = 10;
		p->p_l = 0;
		p->p_h = 0;
		p->Plus = 0;
		p->sumSc = 0;
		
	}
public:
	//static AIn* m_pInstance = nullptr;
	static AIn* GetInstance() {
		if (!m_pInstance) {
			std::weak_ptr<AIn* > t;
			t.lock();
			if (!m_pInstance) {
				m_pInstance = new AIn(1);
				createAIn(m_pInstance);
			}
		}
			return m_pInstance;
	}

	bool setPos() {
		std::cout << "Please enter positions:x,y"<<std::endl;
		std::cout << "中间以一个任意符号分隔"<<std::endl;
		std::cin.clear();
		std::cin.sync();
		Pos tpx = 0, tpy = 0;
		char c = '\0';
		std::cin >> tpx>> c >> tpy;
		
		while (tpx <= 0 || tpy <= 0 || tpx > MXL || tpy > MXH ) {
			std::cout << "Position error,please try again!\n"<<std::endl;
			std::cin.clear();
			std::cin.sync();
			tpx = 0, c = '\0' , tpy = 0;
			std::cin.ignore(1024, '\n');
			std::cin >> tpx>> c >> tpy;
			
			
		}
			
		p_l = tpx;
		p_h = tpy;
		return true;
	}
	Pos getPosX() {
		return p_l;
	}
	Pos getPosY() {
		return p_h;
	}
	void getArrSizeAndScr() {
		//输出二维数组的行和列 
		std::cout << "YOUR Level:" << round;
		std::cout <<"Total Score:"<<sumSc<< " Row:" << arr.size() << "  Column:" << arr[0].size() << std::endl;

	}
	void dispArr() {
		//输出二维数组 
		std::cout << "[" << std::endl;
		for (int j = 0; j < arr.size(); j++) {
			std::cout << "[" << " ";
			for (int k = 0; k < arr[0].size(); k++) {
				std::cout << arr[j][k] << " ";
			}
			std::cout << "]" << std::endl;
		}
		std::cout << "]" << std::endl;

		std::cout <<"(("<< Plus <<"))"<< std::endl;
	}
	bool AddArrN(Pos x,Pos y) {
		arr[y - 1][x - 1] ++;
		return true;
	}
	bool setPlusZ() {
		Plus = 0;
		return true;
	};
	bool SumPlus() {
		sumSc += Plus;
		return true;
	};
	ScoreN getPlus() {
		return Plus;
	}
	WTNum getWater()
	{
		return water;
	}
	bool setWater(int m)
	{
		if(water>=0 && m>0)
			water ++;
		if (water >= 0 && m < 0)
			water --;

		return true;
	}
	bool setPos(Pos l,Pos h){
		return true;
	}
	void setRoundZ()
	{
		round = 0;
	}
	bool roundAdd() {
		round += 1;
		return true;
	}
	~AIn() {
		if (m_pInstance)
			delete m_pInstance;
		m_pInstance = nullptr;
	}
};


class Fun {

public:
	Fun()=default;

	void firstSetMap() {
		AIn* p = AIn::GetInstance();
		for(int z = 0;z< MXH; z++)
			for (int c = 0; c < MXL; c++)
			{
			
				//p->arr[z][c] = 
				p->arr[z][c] = rand() % 4;//随机产生布局
				//若固定一盘，则便于测试
			}
	}
	void Tvs(Pos x , Pos y ) {
		AIn* p = AIn::GetInstance();
		//int i;
		p->p_l;
		p->p_h;
		p->Plus++;
		//std::cout << "\n读入了" << "pos[" << x << "][" << y << "]" << "\n" << std::endl;
		if (p->arr[y - 1][x - 1] > 3) {
			p->arr[y - 1][x - 1] = 0;
			//向上
			for (int i = y - 2; i >= 0; i--) {
				if (p->arr[i][x - 1] != 0) {
					p->arr[i][x - 1] += 1;
					Tvs(x, i + 1);
					i = -1;
				}
			}
			//向下
			for (int i = y; i < MXH; i ++) {
				if (p->arr[i][x - 1] != 0) {
					p->arr[i][x - 1] += 1;
					Tvs(x, i + 1);
					i = MXH;
				}
			}
			//向左
			for (int i = x - 2; i >= 0; i--) {
				if (p->arr[y - 1][i] != 0) {
					p->arr[y - 1][i] += 1;
					Tvs(i + 1, y);
					i -= 1;
				}
			}
			//向右
			for (int i = x; i < MXL; i ++) {
				if (p->arr[y - 1][i] != 0) {
					p->arr[y - 1][i] += 1;
					Tvs(i + 1, y);
					i = MXL;
				}
			}
		}
		
	};

	//void Tvs(Pos tl = -1,Pos th = -1) {
	//	AIn* p = AIn::GetInstance();
	//	/*p->p_l;
	//	p->p_h;*/
	//	p->Plus++;
	//	if (p->arr[p->p_h - 1][p->p_l - 1] > 3) {
	//		p->arr[p->p_h - 1][p->p_l - 1] = 0;
	//		std::cout << "\n pos["<<p->p_l<<"]["<<p->p_h<<"] is added"<<"\n" << std::endl;
	//		//ArrFind(p->p_h,p->p_l,p);
	//		//Tvs(p->p_h, p->p_l);
	//		std::cout << "\narrived :149th line \n" << std::endl;
	//	
	//
	////void ArrFind(Pos h,Pos l,AIn *p) {
	//	
	//		for (int i = th - 2; i >= 0; i--){
	//		if (p->arr[i][tl - 1] != 0){
	//			p->arr[i][tl - 1] += 1;
	//			std::cout << "\narrived : "<< "pos["<<(i+1)<<"]["<<tl<<"]\n" << std::endl;
	//			Tvs( tl, i + 1);
	//			i = -1;
	//		}
	//	}
	//	for (int i = th; i<MXH; i += 1){
	//		if (p->arr[i][tl - 1] != 0){
	//			p->arr[i][tl - 1] += 1;
	//			std::cout << "\narrived : " << "pos[" << (i + 1) << "][" << tl << "]\n" << std::endl;
	//			Tvs( tl, i + 1);
	//			i = MXH;
	//		}
	//	}
	//	for (int i = tl - 2; i >= 0; i--){
	//		if (p->arr[th - 1][i] != 0){
	//			p->arr[th - 1][i] += 1;
	//			std::cout << "\narrived : " << "pos[" << th << "][" << (i+1) << "]\n" << std::endl;
	//			Tvs(i + 1, th);
	//			i --;
	//		}
	//	}
	//	for (int i = tl; i<MXH; i += 1){
	//		if (p->arr[th - 1][i] != 0){
	//			p->arr[th - 1][i] += 1;
	//			std::cout << "\narrived : " << "pos[" << th << "][" << (i + 1) << "]\n" << std::endl;
	//			Tvs(i + 1, th);
	//			i = MXH;
	//		}
	//	}
	//	}
	//};

public:
	//判断全局是否需要重新生成
	bool isGameOver(AIn* p) {
		int flg = 0;
		for (int m = 0; m < MXH; m++) {
			for (int n = 0; n < MXL; n++) {
				if (p->arr[m][n] != 0) {
					flg ++;
				}
			}
		}
		if (0 == flg) {
			AIn::createAIn(p);
			std::cout << "CONGRATULATIONS!" << std::endl;
			std::cout << "Level "<<p->round<<" completed!" << std::endl;
			srand((unsigned)time(NULL));
			firstSetMap();
			p->dispArr();
			p->roundAdd();
			return true;
		}
		else
			return false;
	};
};

	AIn * AIn::m_pInstance = nullptr;

int main() {

	//随机数种子
	srand((unsigned)time(NULL));
	
	//单例模式创建
	AIn * pSc = AIn::GetInstance();
	Fun opt;

	//pSc->dispArr();
	opt.firstSetMap();//布局

	std::cout << "按任意键开始游戏\n" << std::endl;
	system("pause");

	pSc->dispArr();
	pSc->setRoundZ();//级别初始化
	for (; pSc->getWater() > 0 && pSc->getWater() < 100;)
	{
		if (pSc->AIn::setPos())
		{
			//pSc->AIn::setPos();
			Pos pgx = pSc->getPosX(), pgy = pSc->getPosY();
			/*std::cout << "AAA";*/
			pSc->AddArrN(pgx, pgy); //水滴

			pSc->setWater(-1);
			pSc->SumPlus();
			pSc->setPlusZ();
			opt.Tvs(pgx, pgy);
			if (pSc->getPlus() >= 2){
				pSc->setWater(1);
			}
			pSc->dispArr();
			std::cout << "water=" << pSc->getWater() << std::endl;
			opt.isGameOver(pSc);
		}
	}
	 if(pSc->getWater() <= 0)
		std::cout << "You are failed. Try again, YOU CAN DO IT!" << std::endl;
	if (pSc->getWater() >= 100)
		std::cout << "You win!$:*.`★* ." << std::endl;
	

	pSc->getArrSizeAndScr();
	//pSc->dispArr();
	int i;
	std::cin >> i;
	return 0;
}





    /*vector<vector<int> > arr(MXH);
	for (int i = 0; i < MXH; i++) {
		arr[i].resize(MXL);
	}*/
	////输出二维数组的行和列 
	//cout << "Row:" << arr.size() << "  Column:" << arr[0].size() << endl;

	////输出二维数组 
	//cout << "[" << endl;
	//for (int j = 0; j < arr.size(); j++) {
	//	cout << "[" << " ";
	//	for (int k = 0; k < arr[0].size(); k++) {
	//		cout << arr[j][k] << " ";
	//	}
	//	cout << "]" << endl;
	//}
	//cout << "]" << endl;



//vector<vector<int> > array(m); 
//这个m一定不能少
////初始化一个m*n的二维数组
//for (int i = 0; i < m; i++) {
//	array[i].resize(n);
//}