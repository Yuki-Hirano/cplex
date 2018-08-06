#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "SA_head2.h"
#define N 4
#define INF 10000
#define LIMIT1 10000
#define LIMIT2 1000
#define T_initial 70
#define rho 0.99
#define SEED 2
//#define PROBABILITY 0.1
//#define EPSILON 0.05
#define SIGMA 0.25
#define MU 0.5
#define K 3
#define ERROR 1e-15


typedef struct {
  int cap;
  double prob;
} topology;


void swap_topology(topology *x, topology *y);
void sort_by_cap(topology a[],int length);
void combine(topology a[]);
int define_cap(topology a[],double EPSILON);

int main(int argc, char *argv[]){
  double PROBABILITY=atof(argv[1]);
  double EPSILON=atof(argv[2]);
  int cap_list[3]={1,5,10};
  int N_max[3]={7,2,3};
  int N_list[K];
  int omega;
  int i,j,k,a,b;
  int cnt2;
  int num[K];
  int input[K];
  topology *p_density;
  
  

  for(i=0; i<N_max[0]; i++) {
    for(j=0; j<N_max[1]; j++) {
      for(k=0; k<N_max[2]; k++){
	N_list[0]=i;
	N_list[1]=j;
	N_list[2]=k;
	//probability
       	cnt2=(1+i)*(1+j)*(1+k);
	

	p_density = (topology*)malloc(sizeof(topology)*(cnt2+1));
	if(p_density==NULL) {
	  printf("memory error\n");
	  exit(0);
	}

	for(a=0; a<cnt2+1; a++) {
	  p_density[a].cap=0;
	  p_density[a].prob=0;
	}
	
	for(b=0;b<cnt2+1;b++){
	  for(num[0]=0; num[0]<i+1; num[0]++) {
	    for(num[1]=0; num[1]<j+1; num[1]++) {
	      for(num[2]=0; num[2]<k+1; num[2]++){
		for(a=0; a<K; a++) {
		  input[a]=num[a];
		}
    
		p_density[b].cap=calc_cap(cap_list,input);
		p_density[b].prob=calc_prob(cap_list,N_list,input,PROBABILITY);
		b++;
	      }
	    }
	  }
	}
	
	combine(p_density);
	sort_by_cap(p_density,cnt2);


	omega=define_cap(p_density,EPSILON);
	printf("Omega[%d][%d][%d]=%d;",i,j,k,omega);

	free(p_density);
      }
      printf("\n");
    }
  }

 


  
  return 0;
}



void swap_topology(topology *x, topology *y){
  topology temp=*x;
  *x=*y;
  *y=temp;
}

void sort_by_cap(topology a[],int length){
  int i,j;

  for(i=0; i<length-1; i++) {
    for(j=length-1; j>i; j--) {
      if(a[j-1].cap < a[j].cap) {
	swap_topology(&a[j-1],&a[j]);
      }
    }
  }
}


void combine(topology a[]){
  int i,len=0,temp,cnt;


  while(a[len].cap!=0) {
    len++;
  }

  for(i=0; i<len+1; i++) {
    temp=a[i].cap;
    cnt=i+1;
    while(a[cnt].cap!=0) {
      if(a[cnt].cap==temp) {
	a[i].prob=a[i].prob+a[cnt].prob;
	a[cnt].prob=0;
      }
      cnt++;
    }
  }
}

int define_cap(topology a[],double EPSILON){
  double sum_prob=0;
  int i,c=0,cnt=0;
  while(1) {
    if(a[cnt].cap==0&&fabs(a[cnt].prob)<ERROR) {
      break;
    }
    cnt++;
  }

  for(i=0; i<cnt; i++) {
    if(((a[i].cap!=0)&&(fabs(a[i].prob)>ERROR)) ||((a[i].cap==0)&&(fabs(a[i].prob-1)<ERROR))) {
      if((fabs(EPSILON-(sum_prob+a[i].prob))>ERROR) && (EPSILON<sum_prob+a[i].prob)) {
	c=a[i].cap;
	break;
      }
      sum_prob+=a[i].prob;
    }
  }

  return c;
}
