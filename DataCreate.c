#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
const int DataMax = 64;
const int BlockNum = 32;
int Data[DataMax]; // 保存数据
int Block[BlockNum]; // 物理块
int count[BlockNum]; // 计数器
int N ; // 页面个数
int M;//最小物理块数
#define Q 999
using namespace std;

int main()
{
    int p = 1;
    int e = 4;
    int m = 5;//处理4个页面后起始位置P+1
    float t = 0.637;
    float r; 
    int j = 0;
    int a;

    cout<<"请输入最小物理块数：";
    cin>>M;
    while(M > BlockNum) // 大于数据个数
 {
  cout<<"物理块数超过预定值，请重新输入：";
  cin>>M;
 }
 cout<<"请输入页面的个数：";
 cin>>N;
 while(N > DataMax) // 大于数据个数
 {
  cout<<"页面个数超过预定值，请重新输入：";
  cin>>N;
 }
      
    srand((int)time(NULL));//用time(0)的返回值当种子
    for(int o=0;o<(N/m);o++)
    {
        for(int i=0;i<m;i++)
        {
        
            Data[j] = rand() % (e+1) + p;//生成p和p+e之间的5个随机数
            j++;

            if(j == N) break;//退出循环
            else if(i == 4) 
         {
        
             //生成随机数r
            r = rand() % (Q+1) /(float)(Q+1);
            cout<<r<<endl;

            if(r<t)
            {
                p = rand() % N +1;
                cout<<"p的新值为"<<p<<endl;
            }

            else
            {
                p = (p+1) % M;
            }
        }
      
    }
    }
   for(int c=0;c<N;c++)
   {
       cout<<Data[c]<<endl;
   }
   return 0;
}