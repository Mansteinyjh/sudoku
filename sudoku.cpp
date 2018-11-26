#include<bits/stdc++.h>
using namespace std;
//����ÿ���������ʾΪ��0��8,0��8������Ȼ���������˵���ⲿ�����Կ��ԣ�1��9,1��9��
struct M{
	int v[11][11],ans[11][11];//��ǰ�����������Լ��⡣
	int num,fws[3001];//��ҽ�������Ч���������Լ���һ����
	int list[3001][3];//��¼���������˳�򣨺����������һλ��֮ǰ�����֣�;��ζ������������3000�β���
	bool row[11][11],h[11][11],table[11][11];// ���������С��С�С�����hash
	bool origin[11][11];//��ʾ�����Ƿ�ԭ��һ��ʼ���������֡�
	bool okay;//	��ʾ�����Ƿ��Ѿ������⣬�ⲿ�������
	bool wrong;//��ǰ��ҽ�������Ƿ����
	M(){
		okay=0;num=0;wrong=0;fws[0]=81;
		memset(row,1,sizeof(row));
		memset(h,1,sizeof(h));
		memset(table,1,sizeof(table));
		memset(origin,0,sizeof(origin));
	}//��ʼ��
	int getnext(int _x,int _y){
		for(int i=_x;i<9;++i)
			for(int j=(i==_x)?_y:0;j<9;++j)
				if(!v[i][j]) 
					return i*9+j;
		return 81;
	}//����һ��δ������λ�á�
	void dfs(int dep){
		//if(ans[0][0])printf("%d\n",dep);
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
	}//���õݹ����
	M solve(){
		dfs(getnext(0,0));
		if(!okay)
			wrong=1;
		else 
			wrong=0;
		okay=0;
		return *this; 
	}//���õݹ����ĺ���
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
	}//�����������
	void print(){
		//printf("\n");
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j)
				printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	void modify(int _x,int _y,int _w){
		--_x,--_y;//���ⲿ��������תΪ�ڲ�����
		if(_x<0||_y<0||_y>9||_x>9){
			printf("invalid input!");
			return;
		}
		if(origin[_x][_y]){
			printf("invalid input!");
			return;
		}//�����жϷǷ��޸ģ���Խ��͸Ķ�һ��ʼ��Ŀ�����Ŀ�
		if(row[_x][_w]==0||h[_y][_w]==0||table[_x/3*3+_y/3][_w]==0){
			printf("invalid input!");
			return;
		}//����һ����һ�л�С�ľŹ������Լ��ظ�
		if(v[_x][_y]){
			row[_x][v[_x][_y]]=h[_y][v[_x][_y]]=table[_x/3*3+_y/3][v[_x][_y]]=1;
		}//����޸ĵ�λ��֮ǰ�Ѿ���������Ҫ����Ӧ��hash��ȥ����
		list[++num][0]=_x;list[num][1]=_y;list[num][2]=v[_x][_y];
		v[_x][_y]=_w;
		if(_w)
			row[_x][_w]=h[_y][_w]=table[_x/3*3+_y/3][_w]=0;
		(*this).solve();
		if(wrong)
			fws[num]=min(fws[num],num);
		else 
			fws[num]=81;//֮��������Ҫ���໹Ҫ�������¼��ԭ���ǿ��������ĳ�����ڿա�
	}
	void osb(){
		int _x=list[num][0],_y=list[num][1],_w=list[num][2];
		row[_x][v[_x][_y]]=h[_y][v[_x][_y]]=table[_x/3*3+_y/3][v[_x][_y]]=1;
		v[_x][_y]=_w;
		if(!_w) row[_x][_w]=h[_y][_w]=table[_x/3*3+_y/3][_w]=0;
		--num;
	}//one-step-back ָ��ǰ��һ��
	void cbt(){
		for(;num&&fws[num]!=81;--num) (*this).osb();
	}//come-back-true ָ�ص����н�����һ��
};
int main(){
	freopen("sudoku2.in","r",stdin);
	M a;
	a=a.read();
	a.print();
	return 0;
}
