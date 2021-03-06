#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include "opencv2/opencv.hpp"
#define pi 3.1415926
//GA_base
class GA
{
protected:
	int chrom_num;
	int gene_num;
	float p_recombin;
	float p_mut;
	float search_min;
	float search_max;
	int para_num;
	cv::Mat ost;//fun ,x,y,z..
private:
	float (*fun)(std::vector<float> argv);
public:
	GA(const int _chrom_num=40,const int _gene_num=20,
		const float _p_recombin=0.3,const float _p_mut=0.2,
		const float min=0,const float max=1,const int _para_num=1);
	void solve(float (*_fun)(std::vector<float> argv),const int &_para_num=0);
	~GA(){};
	cv::Mat crtbp(const int &Nind=0,const int &Lind=0,const int&encodemin=0,const int &encodemax=2);
	std::pair<std::vector<float> , float> ranking(void);
	GA& select(cv::Mat &Popula,int _method=0);
	GA& recombin(cv::Mat &Popula,const float &opt=0);
	GA& mut(cv::Mat &Popula,float opt=0);
	void bs2rv(cv::Mat &Popula,float min=0,float max=0);
};
//BP
class GA_BP:public GA
{
private:
	cv::Mat input;
	cv::Mat output;
	int implication_num;
public:
	GA_BP(const int _chrom_num=40,const int _gene_num=20,
		const float _p_recombin=0.3,const float _p_mut=0.2,
		const float min=0,const float max=1,const int _para_num=1):
	GA(_chrom_num,_gene_num,_p_recombin,_p_mut,min,max,_para_num){}

	~GA_BP(){};
	void BPsolve(cv::Mat &_input,cv::Mat &_output);
	std::pair<std::vector<float>, float> ranking(void);
};
//GA_TSP
class GA_TSP:public GA
{
private:
	cv::Mat address;
	double distance(int indexi,int indexj);
public:
	GA_TSP(const int _chrom_num=40,const int _gene_num=20,
		const float _p_recombin=0.3,const float _p_mut=0.2,
		const float min=0,const float max=1,const int _para_num=1):
	GA(_chrom_num,_gene_num,_p_recombin,_p_mut,min,max,_para_num){}
	
	~GA_TSP(){};
	void TSPsolve(cv::Mat &_address);
	std::pair<std::vector<float>, float> ranking(cv::Mat &_Poulate);
	cv::Mat crtbp(int encodemax=0);
	GA_TSP& recombin(cv::Mat &Popula,const float &opt=0);
	GA_TSP& mut(cv::Mat &Popula,float opt=0);
	GA_TSP& select(cv::Mat &Popula,int _method=0){GA::select(Popula,_method);return *this;}
};
//QGA
class QGA:public GA
{
public:
	QGA(const int _chrom_num=80,const int _gene_num=20,
		const float _p_recombin=0.3,const float _p_mut=0.2,
		const float min=-pi,const float max=pi,const int _para_num=1):
	GA(_chrom_num,_gene_num,_p_recombin,_p_mut,min,max,_para_num){}
	~QGA(){}
	cv::Mat crtbp(const int &Nind=0,const int &Lind=0);
	void bs2rv(cv::Mat &Popula,float min=-pi,float max=pi);//修改编码方式
	QGA& select(cv::Mat &Popula);
	QGA& recombin(cv::Mat &Popula,const float &opt=0)=delete;
	QGA& mut(cv::Mat &Popula,float opt=0)=delete;
};
//PSO
class PSO
{
private:
	int chrom_num;//不需要 基因 离子群都为浮点数
	int para_num;
	float c1;
	float c2;
	float wmax;
	float wmin;
	float bmin;
	float bmax;
	cv::Mat Population;
	cv::Mat v;//speed 速度
	cv::Mat Pbest;//popula history best 个体历史最有
	std::vector<float> Gbest;//globel best 全局最优
	std::vector<float> post;
	std::vector<float> ost;
	float (*fun)(std::vector<float> argv);
public:
	PSO(const int _chrom_num=50,const int _para_num=1,
		const float min=0,const float max=1,
		const float c1=0.8,const float c2=0.8,const float wmax=1.2,
		const float wmin=0.1);
	~PSO(){}
	void crtbp(const int &_chrom_num=0,const int &_para_num=0);
	void solve(float(*_fun)(std::vector<float> argv));
	std::pair<std::vector<float>, float>  ranking();
	void update(bool para=0);
};