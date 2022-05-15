#include<bits\stdc++.h>
#include <windows.h>
using namespace std;


void setcolor(short x)//自定义字符颜色 
{
    if (x >= 0 && x <= 15)//参数在0-15的范围颜色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色
    else//默认的颜色白色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


struct Sink{
	int xd;
	int yd;
	char type;
	int G;
	double E;
	int ENERGY;
	double min_dis;
	double min_dis_cluster;
};
struct C_r{
	int xd=0;
	int yd=0;
	int distance=0;
	int id=0;
};

double min(double x,double y){
	if(x>y)return y;
	else x;
}

int main(){
	int map[101][101]; 
	int color[101][101];
	int xm=20;
	int ym=20;
	long int Bit=4000*100;
	//printf("%d",Bit);
	double sink[2]={0.5*xm,0.5*ym};
	int n=100;
	double m=0.1;
	double p=0.1;
	double Eo=2;
	double ETX=50*0.0000000001;
	double ERX=50*0.0000000001;
	double Efs=10*0.0000000001;
	double EDA=5*0.0000000001;
	double Emp=5*0.0000000001;
	int a=1;
	int dead=0;
	int countCHs=0;
	int CLUSTER=0;
	int d=30;
	int times=1;
	int sum_r=300;
	int dead_a=0;
	int dead_n=0;
	int cluster=0;
	int PACKETS_TO_BS[sum_r]={0};
	//int PACKETS_TO_CH[sum_r]={0};
	
	//int C=repmat(struct('xd',0,'yd',0,'distance',0,'id',0),n*p,1);簇
	C_r C[(int)(n*p)];
//	int die_first_x[times]={0};
//	int die_first_r[times]={0};
//	int die_r[sum_r]={0};//zuozhe zyk 
//	int die_y[sum_r]={0};
	int min_dis_cluster;
	int min_dis;
	int temp;
	Sink S[101];
//	for(int i=0;i<sum_r;i++){
//		die_r[i]=i+1;
//	}
	for(int tests=0;tests<times;tests++){
		for (int i=0;i<n;i++){
			S[i].xd=((double)(rand()%20))/20.0*xm;
		//	printf("%d ",S[i].xd);
			S[i].yd=((double)(rand()%20))/20.0*ym;
			S[i].type='N';
			S[i].G=0;
			int temp_rnd0=i;
			if(temp_rnd0<m*n+1){
				S[i].E=Eo*(1+a);
				S[i].ENERGY=1;
				map[S[i].xd][S[i].yd]=1;
			}
			if(temp_rnd0>=m*n+1){
				S[i].E=Eo;
				S[i].ENERGY=0;
				map[S[i].xd][S[i].yd]=2;
			}
           
		}
		S[n].xd=sink[0]; //基站 
		S[n].yd=sink[1];
		printf("以下为节点初始状态,中枢为+,普通节点为o，+节点为+\n");	 
		for(int i=0;i<20;i++){
			for(int j=0;j<20;j++){
				if(i==(20/2)&&j==(20/2)){
					printf("x");//中枢为x 
				}
				else if(map[i][j]==2){
					printf("o");
				}
				else if(map[i][j]==1){
					printf("+");
				}
				else{
					printf(" "); //空 
		 		}
			}
			printf("\n");
		}
		//开始仿真
		int is_first_die= 1;
		for(int r=0;r<sum_r;r++){
			cluster = 0;
        	countCHs = 0;
	    	dead_a = 0;
        	dead_n = 0;
        	dead = 0;
        	
			
			
			//die_y[r]=dead;
			double distance;
			//选举簇头节点
			for(int i=0;i<n;i++){
				if(S[i].E>0){
					double temp_rand=((double)(rand()%100))/100.0;	
					if((S[i].G)<=0){
						if(temp_rand<=(p/(1-p* ((r-1)%int(1/p)+0.5)))){
							color[S[i].xd][S[i].yd]=1;//簇头节点 
							countCHs=countCHs+1;
                        	S[i].type='C';
                        	S[i].G=round(1/p)-1; 
                        	cluster=cluster+1;
                        	C[cluster].xd=S[i].xd;
                        	C[cluster].yd=S[i].yd;
							distance=sqrt((S[i].xd-(S[n].xd))*(S[i].xd-(S[n].xd))+(S[i].yd-(S[n].yd))*(S[i].yd-(S[n].yd)));	
							C[cluster].distance=distance;
                        	C[cluster].id=i+1;
                        	if(distance>d){
                        		S[i].E=S[i].E-((ETX+EDA)*(Bit)+Emp*Bit*(distance*distance*distance*distance));
							}
							else{
								S[i].E=S[i].E-((ETX+EDA)*(Bit)+Efs*Bit*(distance*distance));
							}
						}
					}
				}
			}
			printf("实验次数=%d\t\t轮数=%d 选举簇头数：%d\n",tests+1,r+1,countCHs);
			PACKETS_TO_BS[r]=countCHs;
			//普通节点加入簇中
			for(int i=0;i<n;i++){
				if(S[i].type=='N'&& S[i].E>0){
					if(cluster>=1){
						min_dis=sqrt((S[i].xd-C[i].xd)*(S[i].xd-C[i].xd)+(S[i].yd-C[0].yd)*(S[i].yd-C[0].yd));
						min_dis_cluster=1;
						for(int c=0;c<cluster;c++){
							temp=min(min_dis,sqrt((S[i].xd-C[c].xd)*(S[i].xd-C[c].xd)+(S[i].yd-C[c].yd)*(S[i].yd-C[c].yd)));
							if(temp<min_dis){
            					min_dis=temp;
                            	min_dis_cluster=c;
							}
							else if(temp==min_dis){
								if( S[C[min_dis_cluster].id].E<S[C[c].id].E)
								min_dis=temp;
                                min_dis_cluster=c;
							}
						}
					}
					if(min_dis>d)S[i].E=S[i].E-((ETX*Bit)+Emp*Bit*(min_dis*min_dis*min_dis*min_dis));	
					if(min_dis<=d)S[i].E=S[i].E-((Efs*Bit)+Emp*Bit*(min_dis*min_dis*min_dis*min_dis));
					if(min_dis>0)S[C[min_dis_cluster].id].E=S[C[min_dis_cluster].id].E-((ERX+EDA)*Bit);
					S[i].min_dis=min_dis;
					S[i].min_dis_cluster=min_dis_cluster;
			///		PACKETS_TO_CH[r]=n-dead-cluster;
				//	printf("%d %d\n",r, countCHs);
				

				}
			} 

			//判断死亡 
			for(int i=0;i<n;i++){
				if(S[i].E<=0) {
					dead=dead+1;
					color[S[i].xd][S[i].yd]=2;//死亡节点 
					if(dead == 1 && is_first_die == 1){
						
                    	is_first_die = 0; //第一次死亡
                    	printf("实验次数=%d\t\t轮数=%d 出现死亡节点\n",tests+1,r+1);
                    //	die_first_x[tests]=tests+1;
                    //	die_first_r[tests]=r+1;
					}
					if(S[i].ENERGY==1){
						dead_a=dead_a+1;
					}
					if(S[i].ENERGY==0){
						dead_n=dead_n+1;
					}
				}
				
			}
			
			printf("以下第%d轮节点状态,中枢为+,普通节点为o，+节点为+\n,普通节点为白色，簇头节点为绿色，死亡节点为红色\n",r+1);	 
			for(int i=0;i<20;i++){
				for(int j=0;j<20;j++){
					if(i==(20/2)&&j==(20/2)){
						
						printf("x");
					}
					else if(map[i][j]==2){
						if(color[i][j]==2)setcolor(12);
						else if(color[i][j]==1)setcolor(10);
						printf("o");
						setcolor(7);
					}
					else if(map[i][j]==1){
						if(color[i][j]==2)setcolor(12);
						else if(color[i][j]==1)setcolor(10);
						printf("+");
						setcolor(7);
					}
					else{
						printf(" "); //空 
		 			}
				}
				printf("\n");
			}
			for(int i=0;i<20;i++){
				for(int j=0;j<20;j++){
					color[i][j]=0;
				}
			}
			if((r%(int)(n*p+0.5)) == 0){
				for(int i=0;i<n;i++){
					S[i].G=0;
					S[i].type='N';					
				}
			}
			if(dead==n){
				printf("第%d轮。节点全部死亡",r+1);
				break;
			}
		}
		
		


	}
}
