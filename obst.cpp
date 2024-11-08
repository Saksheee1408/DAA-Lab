/*Name : Prachi Mehetre
Roll no. : 47
Class : TY-B2
Assignment 6 : Develop a program to implement Optimal Binary Search Tree using Dynamic Programming. 
*/
#include<iostream>
#include <climits>
using namespace std;
class algo
{
    public : 
            int i,j;
    public : 
            int find(float c[][20],int r[][20],int i,int j)
            {
                int mincost=INT_MAX,minindex=i;
                for(int m=r[i][j-1];m<=r[i+1][j];m++)
                {
                    if((c[i][m-1]+c[m][j]) < mincost)
                    {
                        mincost=c[i][m-1]+c[m][j];
                        minindex=m;
                    }
                }
                return minindex;
            }
            void obst(float p[],float q[],int n)
            {
                float w[20][20]={0};
                float c[20][20]={0};;
                int r[20][20]={0};
                
                for(i=0;i<=n;i++)
                {
                    w[i][i]=q[i];
                    c[i][i]=0;
                    r[i][i]=0;
                }
                for(i=0;i<n;i++)
                {
                    w[i][i+1]=q[i]+q[i+1]+p[i+1];
                    c[i][i+1]=w[i][i+1];
                    r[i][i+1]=i+1;
                }
                w[n][n]=q[n];
                c[n][n]=0.0;
                r[n][n]=0;
                for(int m=2;m<=n;m++)
                {
                    for(i=0;i<=n-m;i++)
                    {
                        j=i+m;
                        w[i][j]=w[i][j-1]+p[j]+q[j];
                        int k=find(c,r,i,j);
                        c[i][j]=w[i][j]+c[i][k-1]+c[k][j];
                        r[i][j]=k;
                    }
                }
                cout<<"Weight Matrix :\n";
                for(i=0;i<=n;i++)
                {
                    for(j=0;j<=n;j++)
                    {
                        cout<<"w("<<i<<","<<j<<")="<<w[i][j]<<"\t";
                    }
                    cout<<endl;
                }
                cout<<"Cost Matrix :\n";
                for(i=0;i<=n;i++)
                {
                    for(j=0;j<=n;j++)
                    {
                        cout<<"c("<<i<<","<<j<<")="<<c[i][j]<<"\t";
                    }
                    cout<<endl;
                }
                cout<<"R Matrix :\n";
                for(i=0;i<=n;i++)
                {
                    for(j=0;j<=n;j++)
                    {
                        cout<<"r("<<i<<","<<j<<")="<<r[i][j]<<"\t";
                    }
                    cout<<endl;
                }
                cout<<"Optimal weight : "<<w[0][n]<<endl;
                cout<<"Optimal cost : "<<c[0][n]<<endl;
                cout<<"Optimal K value : "<<r[0][n]<<endl;
            }
};
int main()
{
    algo a;
    int n,i;
    float p[20],q[20];
    cout<<"Enter n : ";
    cin>>n;
    cout<<"Enter profit of successful search : \n";
    for(i=1;i<=n;i++)            ////
    {
        cout<<"P["<<i<<"] : ";
        cin>>p[i];
    }
    cout<<"Enter profit of Unsuccessful search : \n";
    for(i=0;i<=n;i++)
    {
        cout<<"Q["<<i<<"] : ";
        cin>>q[i];
    }
    a.obst(p,q,n);
    return 0;
}
/*
OUTPUT :
Enter n : 4
Enter profit of successful search : 
P[1] : 3
P[2] : 3
P[3] : 1
P[4] : 1
Enter profit of Unsuccessful search : 
Q[0] : 2
Q[1] : 3
Q[2] : 1
Q[3] : 1
Q[4] : 1
Weight Matrix :
w(0,0)=2	w(0,1)=8	w(0,2)=12	w(0,3)=14	w(0,4)=16	
w(1,0)=0	w(1,1)=3	w(1,2)=7	w(1,3)=9	w(1,4)=11	
w(2,0)=0	w(2,1)=0	w(2,2)=1	w(2,3)=3	w(2,4)=5	
w(3,0)=0	w(3,1)=0	w(3,2)=0	w(3,3)=1	w(3,4)=3	
w(4,0)=0	w(4,1)=0	w(4,2)=0	w(4,3)=0	w(4,4)=1	
Cost Matrix :
c(0,0)=0	c(0,1)=8	c(0,2)=19	c(0,3)=25	c(0,4)=32	
c(1,0)=0	c(1,1)=0	c(1,2)=7	c(1,3)=12	c(1,4)=19	
c(2,0)=0	c(2,1)=0	c(2,2)=0	c(2,3)=3	c(2,4)=8	
c(3,0)=0	c(3,1)=0	c(3,2)=0	c(3,3)=0	c(3,4)=3	
c(4,0)=0	c(4,1)=0	c(4,2)=0	c(4,3)=0	c(4,4)=0	
R Matrix :
r(0,0)=0	r(0,1)=1	r(0,2)=1	r(0,3)=2	r(0,4)=2	
r(1,0)=0	r(1,1)=0	r(1,2)=2	r(1,3)=2	r(1,4)=2	
r(2,0)=0	r(2,1)=0	r(2,2)=0	r(2,3)=3	r(2,4)=3	
r(3,0)=0	r(3,1)=0	r(3,2)=0	r(3,3)=0	r(3,4)=4	
r(4,0)=0	r(4,1)=0	r(4,2)=0	r(4,3)=0	r(4,4)=0	
Optimal weight : 16
Optimal cost : 32
Optimal K value : 2
*/