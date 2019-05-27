#include<iostream>
#include<stdlib.h>

using namespace std;
#define M 2
#define Q 999
void DataCreate();
int const A = 4;//内存中存放的页面数
int count = 0;
int Inside[A];
int const PageCount =10;//总的页面数
int Page[PageCount];
int insert = 0;//先到先出置换算法fcfo中表示 当内存满的时候，新进入的页号放的位置
int suiji = 0; //随机置换算法randchange  当内存满的时候，新进入的页号放的位置
int state[A];//clock置换算法中，内存中的每个页面号对应的状态
int state2[A][M];// 二维数组，第一行第一列为访问位，第一行的第二列为修改位
double lost = 0.0;

void DataCreate()
{

    int p = 1;
    int e = 4;
    int m = 5;//处理4个页面后起始位置P+1
    float t = 0.637;
    float r; 
    int j = 0;

  srand((int)time(NULL));//用time(0)的返回值当种子
    for(int o=0;o<(PageCount/m);o++)
    {
        for(int i=0;i<m;i++)
        {
        
            Page[j] = rand() % (e+1) + p;//生成p和p+e之间的5个随机数
            j++;
            if(j == PageCount) break;//退出循环
            else if(i == 4) 
         {
        
             //生成随机数r
            r = rand() % (Q+1) /(float)(Q+1);
            cout<<r<<endl;

            if(r<t)
            {
                p = rand() % PageCount +1;
                cout<<"p的新值为"<<p<<endl;
            }

            else
            {
                p = (p+1) % A;
            }
        }
      
    }
    }

}

//检测页号是否在内存中
bool isInside(int num){
	for(int i = 0; i < A; i++){
		if(Inside[i] == Page[num]){
			state[i] = 1;
			return true;
		}
	}
	return false;
}

//判断页面是否已经被修改
bool change(){
	if((rand()%2+1) == 1 ){
		cout<<"该页面被修改"<<endl;
		return true;
	}
	else
		return false;
}

//用于改进型clock置换算法，检测页号是否在内存中并把访问位和修改位置1
bool isInside2(int num){
	for(int i = 0; i < A; i++){
		if(Inside[i] == Page[num]){
			if(change()){
				state2[i][0] = 1;
				state2[i][1] = 1;
			}
			else{
				state2[i][0] = 1;
			}
			return true;
		}
	}
	return false;
}

//用于改进型clock置换算法，判断内存中第几个需要被置换
int whichpage(){
	int j;

	for(j=0; j < A;j++){
        if(state2[j][0] == 0&&state2[j][1] == 0){
			return j;
		}
	}
	for(j=0; j < A;j++ ){
        if(state2[j][0] == 0&&state2[j][1] == 1){
			return j;
		}
		state2[j][0] = 0 ;
	}
	for(j=0; j < A;j++ ){
		state2[j][0] = 0 ;
	}
	return whichpage();
}


//简单Clock置换算法
void CLOCK(int num){
	int j;

	if(isInside(num)){
		cout<<"命中"<<endl;
		for(int i=0 ; i <A; i++)
        cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
	}
	else
		if(count == A){
			lost++;
			for(j=0; j < A; ){
				if(state[j] == 0){
					break;
				}
				else{
					state[j] = 0;
				}
				j++;
				j = j %3;
			}
			Inside[j] = Page[num];
			state[j] = 1;
			for(int i=0 ; i <A; i++)
            cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
		}
		else{
			Inside[count] = Page[num];
			count++;
			for(int i=0 ; i <A; i++)
            cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
		}
}

//改进型clock置换算法
void LCLOCK(int num){
	int j;

	if(isInside2(num)){
		cout<<"命中"<<endl;
		for(int i=0 ; i <A; i++)
			
        cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
	}
	else
		if(count == A){
			lost++;
			j =whichpage();
			Inside[j] = Page[num];
			state2[j][0] = 1;
			for(int i=0 ; i <A; i++)
			
           cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
			
		}

		else{
			Inside[count] = Page[num];
			count++;
			for(int i=0 ; i <A; i++)
			cout<<"物理块"<<i<<"#中内容:"<<Inside [i]<<endl;
		}
}

int main(){
  char ch ;
  DataCreate();
  for(int i = 0; i < PageCount; i++){
		cout<<Page[i]<<" ";
	}
  cout<<endl;
  while(1){
	cout<<"------------1.Clock置换算法（CLOCK）-----"<<endl;
	cout<<"------------2.改进型Clock置换算法--------"<<endl;
	cout<<"------------0.退出-----------------------"<<endl;
	cout<<"-------------输入进行选择----------------"<<endl;
	cin>>ch;
	switch(ch){
    case '1':{
            lost = 0;
			count = 0;
			for(int m = 0; m < A; m++){
				state[m] = 0;
				}
				for(int j = 0; j < A; j++){
					Inside[j] = 0;
				}
				for(int i = 0; i < PageCount; i++){
                    cout<<"读入Page["<<i<<"]="<<Page[i]<<endl;
                    CLOCK(i);
	            }
                cout<<"\n页面访问次数"<<PageCount<<"\n缺页中断次数"<<lost<<"\n缺页率"<<lost/(PageCount)<<"\n"<<endl;
    }break;
    case '2':{
            lost = 0;
			count = 0;
			for(int m = 0; m < A; m++){
                for(int n = 0; n < 2;n++)
				state2[m][n] = 0;
			}
			for(int j = 0; j < A; j++){
                Inside[j] = 0;
			}
			for(int i = 0; i < PageCount; i++){
                cout<<"读入Page["<<i<<"]="<<Page[i]<<endl;
                LCLOCK(i);
            }
            cout<<"\n页面访问次数"<<PageCount<<"\n缺页中断次数"<<lost<<"\n缺页率"<<lost/(PageCount)<<"\n"<<endl;
    }break;
	case '0':{
		exit(0);
			 }break;
	}
  }
  return 0;
}




