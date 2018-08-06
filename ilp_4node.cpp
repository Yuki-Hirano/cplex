#include<ilcplex/ilocplex.h>
#define N 4
#define K 3

using namespace std;


int main() {

  int p_link[N][N];
  int Omega[N][N][K];
  int c_list[3]={1,5,10};
  int f_sd_k[N][N][K];
  int n_max[K]={0,0,0};
  int s,d,i,j,k;
  

  //primary network
  p_link[0][0]=0; p_link[0][1]=10; p_link[0][2]=10; p_link[0][3]=10;
  p_link[1][0]=1; p_link[1][1]=0; p_link[1][2]=5; p_link[1][3]=1;
  p_link[2][0]=1; p_link[2][1]=1; p_link[2][2]=0; p_link[2][3]=1;
  p_link[3][0]=1; p_link[3][1]=1; p_link[3][2]=5; p_link[3][3]=0;


  //set f_sd_k
  for(s=0;s<N;s++){
    for(d=0;d<N;d++){
      for(k=0;k<K;k++){
	if(p_link[s][d]==c_list[k]){
	  f_sd_k[s][d][k]=1;
	  n_max[k]++;
	    }else{
	  f_sd_k[s][d][k]=0;
	}
      }
    }
  }

  
  //Omega(p=0.1,eps=0.05)
  Omega[0][0][0]=0;Omega[0][0][1]=10;Omega[0][0][2]=10;
  Omega[0][1][0]=5;Omega[0][1][1]=10;Omega[0][1][2]=10;
  Omega[1][0][0]=1;Omega[1][0][1]=10;Omega[1][0][2]=10;
  Omega[1][1][0]=5;Omega[1][1][1]=10;Omega[1][1][2]=10;
  Omega[2][0][0]=1;Omega[2][0][1]=10;Omega[2][0][2]=10;
  Omega[2][1][0]=5;Omega[2][1][1]=10;Omega[2][1][2]=11;
  Omega[3][0][0]=1;Omega[3][0][1]=10;Omega[3][0][2]=11;
  Omega[3][1][0]=5;Omega[3][1][1]=10;Omega[3][1][2]=11;
  Omega[4][0][0]=2;Omega[4][0][1]=10;Omega[4][0][2]=11;
  Omega[4][1][0]=5;Omega[4][1][1]=10;Omega[4][1][2]=11;
  Omega[5][0][0]=2;Omega[5][0][1]=10;Omega[5][0][2]=11;
  Omega[5][1][0]=5;Omega[5][1][1]=10;Omega[5][1][2]=11;
  Omega[6][0][0]=2;Omega[6][0][1]=10;Omega[6][0][2]=11;
  Omega[6][1][0]=5;Omega[6][1][1]=11;Omega[6][1][2]=11;

  

  IloEnv env;
  IloModel model(env);
  //IloNumVarArray vars(env);
  IloNumVarArray cb_ij(env);
  IloNumVarArray b_sd_ij(env);
  IloNumVarArray x0_n_ij(env);
  IloNumVarArray x1_n_ij(env);
  IloNumVarArray x2_n_ij(env);

  //set cb_ij
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(i==j){
	cb_ij.add(IloIntVar(env,0,0));
      }else{
	cb_ij.add(IloIntVar(env,0,1));
      }
    }
  }

  //set b_sd_ij
  for(s=0;i<N;i++){
    for(d=0;i<N;i++){
      for(i=0;i<N;i++){
	for(j=0;i<N;i++){
	  if(s==d || i==j){
	    b_sd_ij.add(IloIntVar(env,0,0));
	  }else{
	    b_sd_ij.add(IloIntVar(env,0,1));
	  }
	}
      }
    }
  }

  //set x0_n_ij
  for(k=0;k<n_max[0];k++){
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
	if(i==j){
	  x0_n_ij.add(IloIntVar(env,0,0));
	}else{
	  x0_n_ij.add(IloIntVar(env,0,1));
	}
      }
    }
  }

  //set x1_n_ij
  for(k=0;k<n_max[1];k++){
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
	if(i==j){
	  x1_n_ij.add(IloIntVar(env,0,0));
	}else{
	  x1_n_ij.add(IloIntVar(env,0,1));
	}
      }
    }
  }

  //set x2_n_ij
  for(k=0;k<n_max[2];k++){
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
	if(i==j){
	  x2_n_ij.add(IloIntVar(env,0,0));
	}else{
	  x2_n_ij.add(IloIntVar(env,0,1));
	}
      }
    }
  }

  
  //objective function
  model.add(IloMinimize(env, IloSum(cb_ij)));

  //constraint 13-a
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(i!=j){
	model.add(IloSum(x1_n_ij[][i][j]))
      }
    }
  }
  //constraint 13-b


  

  //model.add( 2*vars[0] + 3*vars[1] + 1*vars[2] + 2*vars[3] + 3*vars[4] <= 6);

  IloCplex cplex(model);
  IloNumArray vals(env);

  cplex.solve();
  cplex.getValues(vals, cb_ij);

  env.out() << "Solution Value = " <<  cplex.getObjValue() << endl;
  env.out() << "Values = " << vals << endl;
  env.end();
  return 0;
}
