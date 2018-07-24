#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 14
#define K 2
#define INF 10000


/*
void swap(char *pa,char *pb){
        char temp = *pa;
        *pa = *pb;
        *pb = temp;
}
*/
/*
void swap(int *pa,int *pb){
  int temp = *pa;
  *pa = *pb;
  *pb = temp;
}
*/

int min_key(int A[]){
        int key=0;
        int i,j=A[key];

        if(j==-1) {
                j=INF;
        }

        for(i=0; i<N; i++) {
                if((A[i]!=-1)&&(A[i]<j)) {
                        key=i;
                        j=A[key];
                }
        }
        return key;
}

int check_V(int A[]){
        int e=0;
        int i;
        for(i=0; i<N; i++) {
                if(A[i]!=-1) {
                        e=1;
                }
        }
        return e;
}

void reverse(int A[]){
        int i;
        int temp;
        for(i=0; i<N/2; i++) {
                temp=A[i];
                A[i]=A[N-i-1];
                A[N-i-1]=temp;
        }
}





void RandomSerch(int s,int d,int A[]){
        int line[N][N];
        int dis[N][N];
        int neighbour_nodes[N];
        int number_neighbour;
        int selected_node;
        int point=0;
        int modify_graph[N][N];
        int U[N][N];
        int V[N];
        int i,j,c,w;
        int check;
        int minimum;
        int val;
        int path[N];
        int pos;

        for(i=0; i<N; i++) {
                for(j=0; j<N; j++) {
                        line[i][j]=0;
                        if(i==j) {
                                dis[i][j]=10000;
                        }else{
                                dis[i][j]=1;
                        }
                }
        }

        /*
           dis[0][0]=10000;
           dis[0][1]=1;
           dis[0][2]=1;
           dis[0][3]=1;
           dis[0][4]=1;

           dis[1][0]=1;
           dis[1][1]=10000;
           dis[1][2]=1;
           dis[1][3]=1;
           dis[1][4]=1;

           dis[2][0]=1;
           dis[2][1]=1;
           dis[2][2]=10000;
           dis[2][3]=1;
           dis[2][4]=1;

           dis[3][0]=1;
           dis[3][1]=1;
           dis[3][2]=1;
           dis[3][3]=10000;
           dis[3][4]=1;

           dis[4][0]=1;
           dis[4][1]=1;
           dis[4][2]=1;
           dis[4][3]=1;
           dis[4][4]=10000;
         */

        c=s;
        w=s;

        while(c!=d) {
                for(i=0; i<N; i++) {
                        neighbour_nodes[i]=INF;
                }
                neighbour_nodes[N]=-10;

                point=0;
                for(j=0; j<N; j++) {
                        if((dis[c][j]==1) && (w!=j)) {
                                neighbour_nodes[point]=j;
                                point++;
                        }
                }


                //for(i=0;i<N;i++){
                //printf("%d,",neighbour_nodes[i]);
                //}

                number_neighbour=0;
                for(i=0; i<N; i++) {
                        if(neighbour_nodes[i]!=INF) {
                                number_neighbour++;
                        }
                }

                //printf("\nnumber=%d\n",number_neighbour);


                selected_node=rand()%number_neighbour;

                //printf("%d\n",selected_node);


                line[c][neighbour_nodes[selected_node]]++;
                w=c;
                c=neighbour_nodes[selected_node];
        }

        for(i=0; i<N; i++) {
	  for(j=0; j<N; j++) {
                        modify_graph[i][j]=INF;
                }
        }

        for(c=0; c<N; c++) {
                for(j=0; j<N; j++) {
                        if((line[c][j]<=1) && (line[j][c]<=1)) {
                                if(line[c][j]==line[j][c]) {
                                        modify_graph[c][j]=100000;
                                        modify_graph[j][c]=100000;
                                }else{
                                        if(line[c][j]>line[j][c]) {
                                                modify_graph[c][j]=line[c][j];
                                                modify_graph[j][c]=100000;
                                        }else{
                                                modify_graph[j][c]=line[j][c];
                                                modify_graph[c][j]=10000;
                                        }
                                }
                        }else{
                                if(line[c][j]>line[j][c]) {
                                        modify_graph[c][j]=1;
                                        modify_graph[j][c]=100000;
                                }else if(line[c][j]<line[j][c]) {
                                        modify_graph[c][j]=100000;
                                        modify_graph[j][c]=1;
                                }else{
                                        modify_graph[c][j]=100000;
                                        modify_graph[j][c]=100000;
                                }
                        }
                }
        }

        /*for(i=0;i<N;i++){
           for(j=0;j<N;j++){
            printf("%d",modify_graph[i][j]);
           }
           printf("\n");
           }*/

        for(i=0; i<N; i++) {
                V[i]=INF;
                for(j=0; j<2; j++) {
                        U[i][j]=INF;
                }
        }



        V[s]=0;
        check=1;


        //for(i=0;i<N;i++){
        //printf("%d",V[i]);
        //}
        //printf("\n");

        while(check==1) {
                minimum=min_key(V);
                //printf("%d\n",minimum);
                if(minimum==d) {
                        break;
                }
                for(i=0; i<N; i++) {
                        val=modify_graph[minimum][i];
                        if((V[i]!=-1) && (V[minimum]+val<V[i])) {
                                V[i]=V[minimum]+val;
                                U[i][0]=minimum;
                                U[i][1]=V[i];
                        }
                }
                V[minimum]=-1;
                //for(point=0;point<N;point++){
                //printf("%d,",V[point]);
                //}
                //printf("\n");

                check=check_V(V);
        }

        pos=d;
        point=0;
        for(i=0; i<N; i++) {
                path[i]=INF;
        }

        /*
           for(i=0;i<N;i++){
           for(j=0;j<2;j++){
            printf("%d",U[i][j]);
           }
           printf("\n");
           }
         */

        while(pos!=s) {
                path[point]=pos;
                pos=U[pos][0];
                point++;
        }

        path[point]=s;
        reverse(path);
        /*
           for(i=0;i<N;i++){
           printf("%d,",path[i]);
           }
           printf("\n");
         */
        for(i=0; i<N; i++) {
                A[i]=path[i];
        }
}


int same_ch(int A[],int B[]){
        int i;
        int check=1;

        for(i=0; i<N; i++) {
                if(A[i]==B[i]) {
                        check=0;
                }
        }

        return check;
}


void descend_sort(int A[],int length){/*bubble sort*/
        int i,j,temp;

        for(i=0; i<length-1; i++) {
                for(j=length-1; j>i; j--) {
                        if(A[j-1]<A[j]) {
                                temp=A[j-1];
                                A[j-1]=A[j];
                                A[j]=temp;
                        }
                }
        }
}

/*
   void swap_topology(topology *x, topology *y){
   topology temp=*x;
 * x=*y;
 * y=temp;
   }

   void sort_by_cap(topology a[],int length){
   int i,j;

   for(i=0;i<N;i++){
    for(j=i;j<length-1;j--){
      if(a[j-1].cap < a[j].cap){
   swap_topology(&a[j-1],&a[j]);
      }
    }
   }
   }

 */

//0からK-1までの整数値をランダムに返す関数
int rand_K(int k){
        int a;
        a=rand()%k;
        return a;
}

int combination(int n, int r){
        if(n==r)
                return(1);
        else if(r==0)
                return(1);
        else if(r==1)
                return(n);
        else
                return( combination(n-1, r-1) + combination(n-1, r) );
}

double calc_prob(int cap[K],int cnt_k[K],int input[K],double p){
        int i=K;
        double sum=1;

        while(i>0) {
                sum*=combination(cnt_k[i-1],input[i-1])*pow(p,input[i-1])*pow(1-p,cnt_k[i-1]-input[i-1]);
                i--;
        }
        return sum;
}

int calc_cap(int cap[K],int input[K]){
        int sum=0;
        int i=K;
        while(i>0) {
                sum+=cap[i-1]*input[i-1];
                i--;
        }
        return sum;
}
