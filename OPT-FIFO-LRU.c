#include<iostream>
const int DataMax = 64;
const int BlockNum = 32;
int DataShow[BlockNum][DataMax]; // 用于存储要显示的数组
bool DataShowEnable[BlockNum][DataMax]; // 用于存储数组中的数据是否需要显示
int Data[DataMax]; // 保存数据
int Block[BlockNum]; // 物理块
int count[BlockNum]; // 计数器
int N ; // 页面个数
int M;//最小物理块数
int ChangeTimes;
void DataCreate();
void DataOutput();
void FIFO(); // FIFO 函数
void Optimal(); // Optimal函数
void LRU(); // LRU函数
void Clock();
#define Q 999
using namespace std;

///*
int main(int argc, char* argv[])
{
   DataCreate();//  DataInput();
  // FIFO();
  // Optimal();
 //  LRU();
 //  return 0;
      int menu;
	 while(true)
	 {
	   cout<<endl;
	   cout<<"*                     菜单选择                        *"<<endl;
	   cout<<"*******************************************************"<<endl;
	   cout<<"*                      1-FIFO                         *"<<endl;
	   cout<<"*                      2-Optimal                      *"<<endl;
	   cout<<"*                      3-LRU                          *"<<endl;
	   cout<<"*                      0-EXIT                         *"<<endl;
	   cout<<"*******************************************************"<<endl;
	   cin>>menu;
	   
	   switch(menu)
	   {
	   case 1: FIFO();break;
	   case 2: Optimal();break;
	   case 3: LRU();break;
	   if(menu!=1&&menu!=2&&menu!=3) break;
	 }
}
}








//*/
void DataOutput()
{
 int i,j;
 for(i=0;i<N;i++) // 对所有数据操作
 {
  cout<<Data[i]<<" ";
 }
 cout<<endl;
 for(j=0;j<M;j++)
 {
  cout<<" ";
  for(i=0;i<N;i++) // 对所有数据操作
  {
   if( DataShowEnable[j][i] )
    cout<<DataShow[j][i]<<" ";
   else
    cout<<"  ";
  }
  cout<<endl;
 }
 cout<<"缺页次数: "<<ChangeTimes<<endl;
 cout<<"缺页率: "<<ChangeTimes*100/N<<"%"<<endl;
}

void DataCreate()
{
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
    int p = 1;
    int e = 4;
    int m = 5;//处理4个页面后起始位置P+1
    float t = 0.637;
    float r; 
    int j = 0;

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

}
void FIFO()
{
 int i,j;
 bool find;
 int point; 
 int temp; // 临时变量
 ChangeTimes = 0;
 for(j=0;j<M;j++)
  for(i=0;i<N;i++)
   DataShowEnable[j][i] = false;  // 初始化为false，表示没有要显示的数据
  
 for(i=0;i<M;i++)
 {
   count[i] = 0; //  大于等于BlockNum，表示块中没有数据，或需被替换掉
        // 所以经这样初始化（3 2 1），每次替换>=3的块，替换后计数值置1，
       // 同时其它的块计数值加1 ，成了（1 3 2 ），见下面先进先出程序段
 }
 for(i=0;i<N;i++) // 对有所数据操作
 {
  // 增加count
  for(j=0;j<M;j++)
   count[j]++;
  find = false; // 表示块中有没有该数据
  for(j=0;j<M;j++)
  {
   if( Block[j] == Data[i] )
   {
    find = true; 
   }
  }
  if( find ) continue; // 块中有该数据，判断下一个数据
  // 块中没有该数据
  ChangeTimes++; // 缺页次数++  
  
  if( (i+1) > M ) // 因为i是从0开始记，而M指的是个数，从1开始，所以i+1
  {
   //获得要替换的块指针
   temp = 0;
   for(j=0;j<M;j++)
   {
    if( temp < count[j] ) 
    {
     temp = count[j];
     point = j; // 获得离的最远的指针
    }
   }
  }
  else point = i;
  // 替换
  Block[point] = Data[i]; 
  
  count[point] = 0; // 更新计数值
  
  // 保存要显示的数据
  for(j=0;j<M;j++)
  {
   DataShow[j][i] = Block[j];
   DataShowEnable[i<M?(j<=i?j:i):j][i] = true; // 设置显示数据
  }
 }
 // 输出信息
 cout<< endl;
 cout<<"FIFO => "<< endl;
 DataOutput();
}
void Optimal()
{
 int i,j,k;
 bool find;
 int point; 
 int temp; // 临时变量，比较离的最远的时候用
 ChangeTimes = 0;
 for(j=0;j<M;j++)
  for(i=0;i<N;i++)
   DataShowEnable[j][i] = false;  // 初始化为false，表示没有要显示的数据
// for(i=0;i<M;i++)
// {
  // count[i] = 0 ; // 
// }
 for(i=0;i<N;i++) // 对有所数据操作
 {
  find = false; // 表示块中有没有该数据
  for(j=0;j<M;j++)
  {
   if( Block[j] == Data[i] )
    find = true; 
  }
  if( find ) continue; // 块中有该数据，判断下一个数据
  // 块中没有该数据，最优算法
  ChangeTimes++; // 缺页次数++  
  for(j=0;j<M;j++)
  {
   // 找到下一个值的位置
   find = false;
   for( k =i;k<N;k++)
   {
    if( Block[j] == Data[k] )
    {
     find = true;
     count[j] = k;
     break;
    }
   }
   if( !find ) count[j] = N;
  }
  if( (i+1) > M ) // 因为i是从0开始记，而BlockNum指的是个数，从1开始，所以i+1
  {
   //获得要替换的块指针
   temp = 0;
   for(j=0;j<M;j++)
   {
    if( temp < count[j] ) 
    {
     temp = count[j];
     point = j; // 获得离的最远的指针
    }
   }
  }
  else point = i;
  // 替换
  Block[point] = Data[i]; 
  
  // 保存要显示的数据
  for(j=0;j<M;j++)
  {
   DataShow[j][i] = Block[j];
   DataShowEnable[i<M?(j<=i?j:i):j][i] = true; // 设置显示数据
  }
 
 }
 // 输出信息
 cout<< endl;
 cout<<"Optimal => "<< endl;
 DataOutput();
}

void LRU()
{
 int i,j;
 bool find;
 int point; 
 int temp; // 临时变量
 ChangeTimes = 0;
 for(j=0;j<M;j++)
  for(i=0;i<N;i++)
   DataShowEnable[j][i] = false;  // 初始化为false，表示没有要显示的数据
 for(i=0;i<M;i++)
 {
   count[i] = 0 ; 
 }
 for(i=0;i<N;i++) // 对有所数据操作
 {
  // 增加count
  for(j=0;j<M;j++)
   count[j]++;
  find = false; // 表示块中有没有该数据
  for(j=0;j<M;j++)
  {
   if( Block[j] == Data[i] )
   {
    count[j] = 0;
    find = true; 
   }
  }
  if( find ) continue; // 块中有该数据，判断下一个数据
  // 块中没有该数据
  ChangeTimes++; // 缺页次数++  
  if( (i+1) > M ) // 因为i是从0开始记，而BlockNum指的是个数，从1开始，所以i+1
  {
   //获得要替换的块指针
   temp = 0;
   for(j=0;j<M;j++)
   {
    if( temp < count[j] ) 
    {
     temp = count[j];
     point = j; // 获得离的最远的指针
    }
   }
  }
  else point = i;
  // 替换
  Block[point] = Data[i]; 
  count[point] = 0;
  
  // 保存要显示的数据
  for(j=0;j<M;j++)
  {
   DataShow[j][i] = Block[j];
   DataShowEnable[i<M?(j<=i?j:i):j][i] = true; // 设置显示数据
  }
 
 }
 // 输出信息
 cout<< endl;
 cout<<"LRU => "<< endl;
 DataOutput();
}

