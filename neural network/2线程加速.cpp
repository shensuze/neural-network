#include <stdio.h>
#include <limits.h>
#include<float.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include<time.h>
#include<pthread.h>
using namespace std;
//初始化
float dc_dwhide1[64][12], dc_dwhide2[64][12], dc_dwhide3[64][12], dc_dbhide1[64], dc_dbhide2[64], dc_dbhide3[64], dc_dwout1[64][3], dc_dwout2[64][3], dc_dbout1[64], dc_dbout2[64];
clock_t start_time, end_time;
double total_time;

float n = 0.2f;
float x_1[64][12] = { 1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
	0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,
					0.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,
					0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,
	1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,
	1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
	1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
					1.0f,1.0f,1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
					0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
					0.0f,1.0f,1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
	1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,
					1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,1.0f,1.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
	1.0f,1.0f,0.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,
					1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,
					1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
	1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
	1.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
					1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,
					0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,1.0f,0.0f,
					0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f

};
//理想值t
float t[64][2] = {
				1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
				1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
				1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
				1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
														1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
														1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
														1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
														1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,
				0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
														0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
														0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
														0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
														0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,
};
//隐藏层的权重和偏置的初值按照标准正态分布
float whide_1[12] = {
						0.49f,0.348f,0.073f,
						0.837f,-0.071f,-3.617f,
						-0.536f,-0.023f,-1.717f,
						-1.456f,-0.556f,0.852f
};
float bhide_1 = -0.185f;
float whide_2[12] = {
					0.442f,-0.537f,1.008f,
					1.072f,-0.733f,0.823f,
					-0.453f,-0.014f,-0.027f,
					-0.427f,1.876f,-2.305f

};
float bhide_2 = 0.526f;
float whide_3[12] = {
					0.654f,-1.389f,1.246f,
					0.057f,-0.183f,-0.743f,
					-0.461f,0.331f,0.449f,
					-1.296f,1.569f,-0.471f

};
float bhide_3 = -1.169f;
//输出层的权重和偏置
float wout_1[3] = { 0.388f,0.803f,0.029f }; float bout_1 = -1.438f;
float wout_2[3] = { 0.025f,-0.790f,1.553f }; float bout_2 = -1.379f;
int loop = 1;
pthread_mutex_t lock;
float csum_old = 0.0f;
float csum = 0.0f;
//定义结构体
struct MY_ARGS {
	int first;
	int last;
	float result;
};

//隐藏层的输入值z
float zhide[64][3];
//隐藏层的输出值a
float ahide[64][3];
//隐藏层输出的导数
float ahide_d[64][3];
//输出层的输入值
float zout[64][2];
//输出层的输出值
float aout[64][2];



//输出层输出的导数
float aout_d[64][2];
//误差值c
float c[64];
//误差对输出层输出值的偏导数
float dc_da[64][2];
//输出层的神经单元误差
float delta_out[64][2];
//隐藏层的神经单元误差
float delta_hide[64][3];


//定义向量点乘函数
double multiple(float *a, float *b, int j)
{
	double multiple = 0;

	int i;
	for (i = 0; i < j; i++)
	{

		multiple = multiple + a[i] * b[i];
	}

	return multiple;
}
//定义激活函数
double sig(float a)
{
	double sig;
	sig = 1 / (1 + exp(-a));

	return sig;
}



//定义线程函数
void* func(void* args) {
	MY_ARGS* my_args = (MY_ARGS*) args;
	int first = my_args->first;
	int last = my_args->last;
	pthread_mutex_lock(&lock);
	 csum = 0.0f;

	for (int i = first; i <= last; i++)
	{
		////隐藏层的输入值z
			//float zhide[64][3];
		zhide[i][0] = multiple(&whide_1[0], &x_1[i][0], 12) + bhide_1;
		zhide[i][1] = multiple(&whide_2[0], &x_1[i][0], 12) + bhide_2;
		zhide[i][2] = multiple(&whide_3[0], &x_1[i][0], 12) + bhide_3;
		
		
		////隐藏层的输出值a
		//float ahide[64][3];
		ahide[i][0] = sig(zhide[i][0]);
		ahide[i][1] = sig(zhide[i][1]);
		ahide[i][2] = sig(zhide[i][2]);
		
		////隐藏层输出的导数
		//float ahide_d[64][3];
		ahide_d[i][0] = ahide[i][0] * (1 - ahide[i][0]);
		ahide_d[i][1] = ahide[i][1] * (1 - ahide[i][1]);
		ahide_d[i][2] = ahide[i][2] * (1 - ahide[i][2]);
		

		////输出层的输入值
		//float zout[64][2];
		zout[i][0] = multiple(&wout_1[0], &ahide[i][0], 3) + bout_1;////////////////////////////为什么写*x_1_new不行
		zout[i][1] = multiple(&wout_2[0], &ahide[i][0], 3) + bout_2;///////////////////////////
		
		////输出层的输出值
		//float aout[64][2];
		aout[i][0] = sig(zout[i][0]);
		aout[i][1] = sig(zout[i][1]);
		
		//输出层输出的导数
		
		aout_d[i][0] = aout[i][0] * (1 - aout[i][0]);
		aout_d[i][1] = aout[i][1] * (1 - aout[i][1]);

		

		//误差值c

		
		c[i] = 0.5f * ((aout[i][0] - t[i][0]) * (aout[i][0] - t[i][0]) + (aout[i][1] - t[i][1]) * (aout[i][1] - t[i][1]));
		
		csum = csum + c[i];
		
		//误差对输出层输出值的偏导数

		dc_da[i][0] = aout[i][0] - t[i][0];
		dc_da[i][1] = aout[i][1] - t[i][1];

		//输出层的神经单元误差

		delta_out[i][0] = dc_da[i][0] * aout_d[i][0];
		delta_out[i][1] = dc_da[i][1] * aout_d[i][1];

		//隐藏层的神经单元误差

		delta_hide[i][0] = ahide_d[i][0] * (wout_1[0] * delta_out[i][0] + wout_2[0] * delta_out[i][1]);
		delta_hide[i][1] = ahide_d[i][1] * (wout_1[1] * delta_out[i][0] + wout_2[1] * delta_out[i][1]);
		delta_hide[i][2] = ahide_d[i][2] * (wout_1[2] * delta_out[i][0] + wout_2[2] * delta_out[i][1]);


		//每个的dc/dw

		for (int tk = 0; tk < 12; tk++)
		{
			dc_dwhide1[i][tk] = delta_hide[i][0] * x_1[i][tk];

			dc_dbhide1[i] = delta_hide[i][0];
			dc_dwhide2[i][tk] = delta_hide[i][1] * x_1[i][tk];

			dc_dbhide2[i] = delta_hide[i][1];
			dc_dwhide3[i][tk] = delta_hide[i][2] * x_1[i][tk];

			dc_dbhide3[i] = delta_hide[i][2];

		}

		for (int tt = 0; tt < 3; tt++)
		{
			dc_dwout1[i][tt] = delta_out[i][0] * ahide[i][tt];

			dc_dbout1[i] = delta_out[i][0];

			dc_dwout2[i][tt] = delta_out[i][1] * ahide[i][tt];

			dc_dbout2[i] = delta_out[i][1];





		}
		

		

	


	}
	my_args->result = csum;

	pthread_mutex_unlock(&lock);
	return NULL;

}
int main()
{
	
	
	
	pthread_mutex_init(&lock, NULL);
	start_time = clock();
	while (1) {
		
		pthread_t th1, th2;
		MY_ARGS args1 = { 0,31,0 };
		MY_ARGS args2 = { 32,63,0 };
	
		pthread_create(&th1,NULL,func,(void*)&args1);
		pthread_create(&th2,NULL,func,(void*)&args2);
		pthread_join(th1, NULL);
		pthread_join(th2, NULL);
		

		//计算总的梯度
		float dc_dwhide[3][12] = { 0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f,
									0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f,
									0.0f,0.0f,0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, 0.0f,0.0f, };
		float dc_dbhide[3] = { 0.0f,0.0f,0.0f };
		float dc_dwout[2][3] = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
		float dc_dbout[2] = { 0.0f,0.0f };
		//隐藏层w1_1-w1_12
		for (int t1 = 0; t1 < 12; t1++)
		{

			for (int t2 = 0; t2 < 64; t2++)
			{

				dc_dwhide[0][t1] = dc_dwhide[0][t1] + dc_dwhide1[t2][t1];
			}

		}
		//隐藏层b1
		for (int t1 = 0; t1 < 64; t1++)
		{
			dc_dbhide[0] = dc_dbhide[0] + dc_dbhide1[t1];
		}

		//隐藏层w2_1-w2_12
		for (int t1 = 0; t1 < 12; t1++)
		{

			for (int t2 = 0; t2 < 64; t2++)
			{

				dc_dwhide[1][t1] = dc_dwhide[1][t1] + dc_dwhide2[t2][t1];
			}

		}
		//隐藏层b2
		for (int t1 = 0; t1 < 64; t1++)
		{
			dc_dbhide[1] = dc_dbhide[1] + dc_dbhide2[t1];;
		}
		//隐藏层w3_1-w3_12
		for (int t1 = 0; t1 < 12; t1++)
		{

			for (int t2 = 0; t2 < 64; t2++)
			{

				dc_dwhide[2][t1] = dc_dwhide[2][t1] + dc_dwhide3[t2][t1];
			}

		}
		//隐藏层b3
		for (int t1 = 0; t1 < 64; t1++)
		{
			dc_dbhide[2] = dc_dbhide[2] + dc_dbhide3[t1];;
		}

		//输出层w11-w13
		for (int t1 = 0; t1 < 3; t1++)
		{

			for (int t2 = 0; t2 < 64; t2++)
			{

				dc_dwout[0][t1] = dc_dwout[0][t1] + dc_dwout1[t2][t1];////////////////////////
			}

		}
		//输出层b1
		for (int t1 = 0; t1 < 64; t1++)
		{
			dc_dbout[0] = dc_dbout[0] + dc_dbout1[t1];
		}
		//输出层w21-w23
		for (int t1 = 0; t1 < 3; t1++)
		{

			for (int t2 = 0; t2 < 64; t2++)
			{

				dc_dwout[1][t1] = dc_dwout[1][t1] + dc_dwout2[t2][t1];
			}

		}
		//输出层b2
		for (int t1 = 0; t1 < 64; t1++)
		{
			dc_dbout[1] = dc_dbout[1] + dc_dbout2[t1];
		}
		
		

		//c条件判断
		if (loop > 1 && args1.result+args2.result - csum_old > -0.01)
		{
			for (int i = 0; i < 12; i++)
			{
				printf("whide_1:%d:%lf\n", i, whide_1[i]);



			}
			printf("bhide_1:%lf\n", bhide_1);
			for (int i = 0; i < 12; i++)
			{


				printf("whide_2:%d:%lf\n", i, whide_2[i]);



			}
			printf("bhide_2:%lf\n", bhide_2);
			for (int i = 0; i < 12; i++)
			{


				printf("whide_3:%d:%lf\n", i, whide_3[i]);

			}
			printf("bhide_3:%lf\n", bhide_3);
			for (int i = 0; i < 3; i++)
			{
				printf("wout_1:%d:%lf\n", i, wout_1[i]);

			}
			printf("bout_1:%lf\n", bout_1);
			for (int i = 0; i < 3; i++)
			{

				printf("wout_2:%d:%lf\n", i, wout_2[i]);
			}
			printf("bout_2:%lf\n", bout_2);
			printf("迭代次数%d\n", loop);


			break;
		}

		csum_old = args1.result+args2.result;
	
		
		//更新隐藏层

		for (int i = 0; i < 12; i++)
		{
			whide_1[i] = whide_1[i] - n * dc_dwhide[0][i];
		}
		bhide_1 = bhide_1 - n * dc_dbhide[0];

		for (int i = 0; i < 12; i++)
		{
			whide_2[i] = whide_2[i] - n * dc_dwhide[1][i];
		}
		bhide_2 = bhide_2 - n * dc_dbhide[1];

		for (int i = 0; i < 12; i++)
		{
			whide_3[i] = whide_3[i] - n * dc_dwhide[2][i];
		}
		bhide_3 = bhide_3 - n * dc_dbhide[2];
		//更新输出层

		for (int i = 0; i < 3; i++)
		{
			wout_1[i] = wout_1[i] - n * dc_dwout[0][i];
		}
		bout_1 = bout_1 - n * dc_dbout[0];

		for (int i = 0; i < 3; i++)
		{
			wout_2[i] = wout_2[i] - n * dc_dwout[1][i];
		}
		bout_2 = bout_2 - n * dc_dbout[1];

		loop = loop + 1;
	}
	
	end_time = clock();
	printf("start_time=%ld\n", start_time);
	printf("end_time=%ld\n", end_time);
	total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("total_time=%f\n", total_time);
	
	
	
	
	
	
	
	
	
	
	
	//测试结果
	float test[2][12] = { 0.0f,1.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,1.0f,0.0f,1.0f,
						 0.0f,1.0f,1.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f,0.0f,1.0f,0.0f
	};
	for (int i = 0; i < 2; i++)
	{
		////隐藏层的输入值z
			//float zhide[64][3];
		zhide[i][0] = multiple(&whide_1[0], &test[i][0], 12) + bhide_1;
		zhide[i][1] = multiple(&whide_2[0], &test[i][0], 12) + bhide_2;
		zhide[i][2] = multiple(&whide_3[0], &test[i][0], 12) + bhide_3;

		////隐藏层的输出值a
		//float ahide[64][3];
		ahide[i][0] = sig(zhide[i][0]);
		ahide[i][1] = sig(zhide[i][1]);
		ahide[i][2] = sig(zhide[i][2]);

		////隐藏层输出的导数
		//float ahide_d[64][3];
		ahide_d[i][0] = ahide[i][0] * (1 - ahide[i][0]);
		ahide_d[i][1] = ahide[i][1] * (1 - ahide[i][1]);
		ahide_d[i][2] = ahide[i][2] * (1 - ahide[i][2]);


		////输出层的输入值
		//float zout[64][2];
		zout[i][0] = multiple(&wout_1[0], &ahide[i][0], 3) + bout_1;////////////////////////////为什么写*x_1_new不行
		zout[i][1] = multiple(&wout_2[0], &ahide[i][0], 3) + bout_2;///////////////////////////

		////输出层的输出值
		//float aout[64][2];
		aout[i][0] = sig(zout[i][0]);
		aout[i][1] = sig(zout[i][1]);

		for (int t = 0; t < 12; t++)
		{

			if (t % 3 == 0)
			{
				printf("\n");
			}
			printf("%f ", test[i][t]);
		}

		if (aout[i][0] > aout[i][1])
		{
			printf("是0");
		}
		else
		{
			printf("是1");
		}



	}

	



	pthread_exit(NULL);




	return 0;
}