#include<bits/stdc++.h>
using namespace std;
//数独每个数坐标表示为（0～8,0～8），当然对于玩家来说和外部程序，仍可以（1～9,1～9）
struct M{
	int v[11][11],ans[11][11];//当前的填到的情况，以及解。
	int num,fws[3001];//玩家进行了有效填数操作以及第一个。
	int list[3001][3];//记录玩家填数的顺序（横纵坐标和这一位填之前的数字）;意味着数独最多进行3000次操作
	bool row[11][11],h[11][11],table[11][11];// 填数关于行、列、小方格的hash
	bool origin[11][11];//表示数字是否原来一开始给出的数字。
	bool okay;//	表示数读是否已经给出解，外部不许调用
	bool wrong;//当前玩家解的数独是否填错。
	M(){
		okay=0;num=0;wrong=0;fws[0]=81;
		memset(row,1,sizeof(row));
		memset(h,1,sizeof(h));
		memset(table,1,sizeof(table));
		memset(origin,0,sizeof(origin));
	}//初始化
	int getnext(int _x,int _y){
		for(int i=_x;i<9;++i)
			for(int j=(i==_x)?_y:0;j<9;++j)
				if(!v[i][j]) 
					return i*9+j;
		return 81;
	}//找下一个未填数的位置。
	void dfs(int dep){
		if(dep>80){
			okay=1;
			//printf("yes\n");
			for(int i=0;i<9;++i)
				for(int j=0;j<9;++j)
					ans[i][j]=v[i][j];
			return;
		}
		int _x=dep/9,_y=dep%9,bh=_x/3*3+_y/3;
		//printf("%d %d\n",_x,_y);
		for(int i=1;i<=9;++i)
			if(row[_x][i]&&h[_y][i]&&table[bh][i]){
				v[_x][_y]=i;
				row[_x][i]=h[_y][i]=table[bh][i]=0;
				//printf("%d %d %d\n",_x,_y,next);
				dfs(getnext(_x,_y));
				v[_x][_y]=0;
				row[_x][i]=h[_y][i]=table[bh][i]=1;
				if(okay) return;
			}
	}//利用递归求解
	M solve(){
		dfs(getnext(0,0));
		if(!okay)
			wrong=1;
		else 
			wrong=0;
		okay=0;
		return *this; 
	}//调用递归求解的函数
	M read(){
		for(int i=0;i<9;++i)
			for(int j=0;j<9;++j){
				int bh=i/3*3+j/3;
				scanf("%d",&v[i][j]);
				if(v[i][j]){
					row[i][v[i][j]]=h[j][v[i][j]]=table[bh][v[i][j]]=0;
					origin[i][j]=1;
				}	
			}
		(*this).solve();
		return *this;
	}//读入后解出数独
	void print(){
		//printf("\n");
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j)
				printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	void modify(int _x,int _y,int _w){
		--_x,--_y;//将外部正常坐标转为内部坐标
		if(_x<0||_y<0||_y>9||_x>9){
			printf("invalid input!");
			return;
		}
		if(origin[_x][_y]){
			printf("invalid input!");
			return;
		}//以上判断非法修改，如越界和改动一开始题目给出的块
		if(v[_x][_y]){
			row[_x][v[_x][_y]]=h[_y][v[_x][_y]]=table[_x/3*3+_y/3][v[_x][_y]]=1;
		}//如果修改的位置之前已经填数，则要把相应的hash先去掉。
		list[++num][0]=_x;list[num][1]=_y;list[num][2]=v[_x][_y];
		v[_x][_y]=_w;
		if(!_w) row[_x][_w]=h[_y][_w]=table[_x/3*3+_y/3][_w]=0;
		(*this).solve();
		if(wrong)
			fws[num]=min(fws[num],num);
		else 
			fws[num]=81;//之所以这里要分类还要开数组记录，原因是可能他会把某个空挖空。
	}
	void osb(){
		int _x=list[num][0],_y=list[num][1],_w=list[num][2];
		row[_x][v[_x][_y]]=h[_y][v[_x][_y]]=table[_x/3*3+_y/3][v[_x][_y]]=1;
		v[_x][_y]=_w;
		if(!_w) row[_x][_w]=h[_y][_w]=table[_x/3*3+_y/3][_w]=0;
		--num;
	}//one-step-back 指往前退一步
	void cbt(){
		for(;num&&fws[num]!=81;--num) (*this).osb();
	}//come-back-true 指回到仍有解的最大一步
};
int main(){
	freopen("sudoku1.in","r",stdin);
	M a;
	a=a.read();
	a.print();
	return 0;
}
