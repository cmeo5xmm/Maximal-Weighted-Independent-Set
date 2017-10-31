#include <iostream>
#include <stdlib.h>
#include <fstream> 

using namespace std;
int main(int argc, char** argv) {
	
	int n,i,j,d,last=-1;	//n=node nums
	int total=0;
	
	fstream file;
	char buffer[1000];
	
	file.open("test1.txt",ios::in);		//change file name 
	file.getline(buffer,sizeof(buffer),'\n');
	n=atoi(buffer);
	
	int gp[n];		//previous graph
	int gc[n];		//current graph
	int w[n];		//weight
	int a[n][n];	//adjacency
	int deg[n];		//degree	
	float gw[n];	//W(v) / (deg(v) + 1)
	
	for(i=0;i<n;i++){		//read file
		if(i==n-1)	file.getline(buffer,sizeof(buffer),'\n');
		else file.getline(buffer,sizeof(buffer),' ');
		w[i]=atoi(buffer);
	}

	for(i=0;i<n;i++){
		d=0;
		for(j=0;j<n;j++){
			if(j==n-1)	file.getline(buffer,sizeof(buffer),'\n');
			else file.getline(buffer,sizeof(buffer),' ');
			
			a[i][j]=atoi(buffer);
			if(a[i][j]==1) d++;
			if(j==n-1) deg[i]=d;
		}
	}
	
	for(i=0;i<n;i++){
		gp[i]=0;		
		gc[i]=0;		
		gw[i]=(float)w[i]/(float)(deg[i]+1.0);		//compute GW
	}
	
	int t,flag=1;
	int x=0;
	while(flag==1){			//every round
		for(i=0;i<n;i++){	//every node
			t=0;	
			for(j=0;j<n;j++){
				if(a[i][j]==1){		//j=neighbor
					if(gw[j]>gw[i] && gp[j]==1){
						t=1;
						gc[i]=0;
					}
					if(gw[j]==gw[i] && gp[j]==1 && i>j){
						t=1;
						gc[i]=0;
					}
				}
			}
			if(t==0){
				gc[i]=1;
			}
		
		}
		
		if(x!=0){		//not first round
			for(i=0;i<n;i++){		
				if(gp[i]!=gc[i])	break;
				if(gp[i]==1)	last=i;
				if(i==n-1)	flag=0;		//done
			}
		}
		
		for(i=0;i<n;i++){		//updating round info
			gp[i]=gc[i];
		}
		x++;
	}

	//print
	cout<<"MWIS: {";
	for(i=0;i<n;i++){
		if(i==last){
			total+=w[i];
			cout<<i;
			break;
		}
		if(gc[i]==1){
			cout<<i<<",";
			total+=w[i];
		}
	}
	cout<<"}"<<endl;
	cout<<"total weight is:"<<total;
	
	file.close();
	return 0;
}

