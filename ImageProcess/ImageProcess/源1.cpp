//////#include<stdio.h>
//////#include<stdlib.h>
//////
//////void sort(int a[],int n)
//////{
//////	int temp;
//////
//////	for (int i = 0; i < n; i++)
//////	{
//////		for (int j = i; j < n; j++)
//////		{
//////			if (a[i] > a[j])
//////			{
//////				temp = a[i];
//////				a[i] = a[j];
//////				a[j] = temp;
//////			}
//////		}
//////	}
//////}
//////
//////int main()
//////
//////{
//////
//////	int a[5] = {2,7,4,9,0};
//////	int n = sizeof(a) / sizeof(int);
//////	sort(a,n);
//////	return 0;
//////}
////
//////#include <iostream>
//////using namespace std;
//////template <typename T>
//////T add(T a, T b)  //注意形参和返回类型
//////{
//////	return a + b;
//////}
//////void main()
//////{
//////	int num1, num2, sum;
//////	cin >> num1 >> num2;
//////	sum = add(num1, num2); //用int匹配模版参数T，若sum,num1,num2类型不一致则无法匹配。
//////	cout << sum;
//////}
////
//#include "dip.h"
//
//int main()
//{
//
//	double theta = 0.7853982;
//	int h = 500;
//	int w = 420;
//
//	int h1 = sswr(h*cos(theta) + w*sin(theta));
//	int w1 =sswr( h*sin(theta) + w*cos(theta));
//
//	int a = 420;
//	int b = 500;
//
//	int x = sswr((a - h / 2.0)*cos(theta) + (b - w / 2.0)*sin(theta) + h1 / 2.0);
//	int y =sswr( -sin(theta)*(a - h / 2.0) + (b - w / 2.0)*cos(theta) + w1 / 2.0);
//	
//
//	return 0;
//}