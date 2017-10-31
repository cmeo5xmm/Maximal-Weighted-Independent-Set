#include <iostream>
#include <stdlib.h>
#include <fstream> 

using namespace std;
int main(int argc, char** argv) {
	
	int n,i,j,d,last=-1;	//n=node nums
	int total=0;
	
	fstream file;
	char buffer[1000];
	
	file.open("test2.txt",ios::in);		//change file name 
	file.getline(buffer,sizeof(buffer),'\n');
	n=atoi(buffer);
	
	int g[n];		//graph
	int w[n];		//weight
	int a[n][n];	//adjacency
	int deg[n];		//degree
	int mwis[n];	
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
		g[i]=1;		//init graph
		mwis[i]=0;
		gw[i]=(float)w[i]/(float)(deg[i]+1.0);		//compute GW
	}
	
	while(true){
		int max=-1,arg=-1;
		for(i=0;i<n;i++){		//find max gw
			if(gw[i]>max && g[i]==1){
				max=gw[i];
				arg=i;
			}
		}
		
		if(max==-1) break;		//done 
		total+=w[arg];
		g[arg]=0;
		for(i=0;i<n;i++){		//delete max&neighbors in G
			if(a[arg][i]==1){
				g[i]=0;
			}
		}
		
		for(i=0;i<n;i++){		//updating new degree
			d=0;
			for(j=0;j<n;j++){
				if(g[j]==0)	a[i][j]=0;
				if(g[i]==1 && a[i][j]==1)	d++;
				if(j==n-1)	deg[i]=d;
			}
		}
		for(i=0;i<n;i++){		//new GW
			gw[i]=(float)w[i]/(float)(deg[i]+1.0);
		}
		
		mwis[arg]=1;
		if(arg>last) last=arg;
	}
	
	//print
	cout<<"MWIS: {";
	for(i=0;i<n;i++){
		if(i==last){
			cout<<i;
			break;
		}
		if(mwis[i]==1)	cout<<i<<",";
	}
	cout<<"}"<<endl;
	cout<<"total weight is:"<<total;

	file.close();
	return 0;
}
