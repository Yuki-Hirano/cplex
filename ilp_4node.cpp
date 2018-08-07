#include<ilcplex/ilocplex.h>

using namespace std;
typedef IloArray<IloArray<IloIntArray> > Int3DArray; // 3D matrix of int coefficients
typedef IloArray<IloIntArray>    IntMatrix;  // 2D matrix of int coefficients
typedef IloArray<IloArray<IloArray<IloNumVarArray> > > NumVar4DArray; // 4D matrix of variables
typedef IloArray<IloArray<IloNumVarArray> > NumVar3DArray; // 3D matrix of variables
typedef IloArray<IloNumVarArray> NumVarMatrix; // 2D matrix of variables

int main() {
  IloEnv env;
  IloModel model(env);
  IloInt N=4;
  IloInt K=3;
  
  NumVarMatrix cb_ij(env,N);
  NumVar4DArray b_sd_ij(env,N);
  NumVar3DArray x0(env,N);
  NumVar3DArray x1(env,N);
  NumVar3DArray x2(env,N);
 
  
  IntMatrix p_link(env,N);
  IloIntArray c_list(env,K);
  Int3DArray f_k_sd(env,K);
  IloIntArray n_max(env,K);
  IloInt s,d,i,j,k;

  //set c_list
  c_list[0]=1; c_list[1]=5; c_list[2]=10;

  //initialize n_max
  n_max[0]=0; n_max[1]=0; n_max[2]=0;

  //primary network
  for(s=0;s<N;s++){
    p_link[s]=IloIntArray(env,N);
  }
      p_link[0][0]=0; p_link[0][1]=10; p_link[0][2]=10; p_link[0][3]=10;
      p_link[1][0]=1; p_link[1][1]=0; p_link[1][2]=5; p_link[1][3]=1;
      p_link[2][0]=1; p_link[2][1]=1; p_link[2][2]=0; p_link[2][3]=1;
      p_link[3][0]=1; p_link[3][1]=1; p_link[3][2]=5; p_link[3][3]=0;   
  
  //set f_sd_k
  for(k=0;k<K;k++){
    f_k_sd[k]=IntMatrix(env,N);
    for(s=0;s<N;s++){
      f_k_sd[k][s]=IloIntArray(env,N);
      for(d=0;d<N;d++){
	if(p_link[s][d]==c_list[k]){
	  f_k_sd[k][s][d]=1;
	  n_max[k]++;
	    }else{
	  f_k_sd[k][s][d]=0;
	}
      }
    }
  }


  //Omega(p=0.1,eps=0.05)
  Int3DArray Omega(env,n_max[0]);

  for(i=0;i<n_max[0];i++){
    Omega[i]=IntMatrix(env,n_max[1]);
    for(j=0;j<n_max[1];j++){
      Omega[i][j]=IloIntArray(env,n_max[2]);
    }
  }
  Omega[0][0][0]=0; Omega[0][0][1]=10; Omega[0][0][2]=10;
  Omega[0][1][0]=5; Omega[0][1][1]=10; Omega[0][1][2]=10;
  Omega[1][0][0]=1; Omega[1][0][1]=10; Omega[1][0][2]=10;
  Omega[1][1][0]=5; Omega[1][1][1]=10; Omega[1][1][2]=10;
  Omega[2][0][0]=1; Omega[2][0][1]=10; Omega[2][0][2]=10;
  Omega[2][1][0]=5; Omega[2][1][1]=10; Omega[2][1][2]=11;
  Omega[3][0][0]=1; Omega[3][0][1]=10; Omega[3][0][2]=11;
  Omega[3][1][0]=5; Omega[3][1][1]=10; Omega[3][1][2]=11;
  Omega[4][0][0]=2; Omega[4][0][1]=10; Omega[4][0][2]=11;
  Omega[4][1][0]=5; Omega[4][1][1]=10; Omega[4][1][2]=11;
  Omega[5][0][0]=2; Omega[5][0][1]=10; Omega[5][0][2]=11;
  Omega[5][1][0]=5; Omega[5][1][1]=10; Omega[5][1][2]=11;
  Omega[6][0][0]=2; Omega[6][0][1]=10; Omega[6][0][2]=11;
  Omega[6][1][0]=5; Omega[6][1][1]=11; Omega[6][1][2]=11;
  
  
  //set cb_ij
  for(i=0;i<N;i++){
    cb_ij[i]=IloNumVarArray(env,N);
    for(j=0;j<N;j++){
      if(i==j){
	cb_ij[i][j]=IloIntVar(env,0,0);
      }else{
	cb_ij[i][j]=IloIntVar(env,0,1);
      }
    }
  }


    
  //set b_sd_ij
  for(s=0;i<N;i++){
    b_sd_ij[s]=NumVar3DArray(env,N);
    for(d=0;i<N;i++){
      b_sd_ij[s][d]=NumVarMatrix(env,N);
      for(i=0;i<N;i++){
	b_sd_ij[s][d][i]=IloNumVarArray(env,N);
	for(j=0;i<N;i++){
	  if(s==d || i==j){
	    b_sd_ij[s][d][i][j]=IloIntVar(env,0,0);
	  }else{
	    b_sd_ij[s][d][i][j]=IloIntVar(env,0,1);
	  }
	}
      }
    }
  }
  

  
  //set x0
  for(i=0;i<N;i++){
    x0[i]=NumVarMatrix(env,N);
    for(j=0;j<N;j++){
      x0[i][j]=IloNumVarArray(env,n_max[0]);
      for(k=0;k<n_max[0];k++){
	if(i==j){
	  x0[i][j][k]=IloIntVar(env,0,0);
	}else{
	  x0[i][j][k]=IloIntVar(env,0,1);
	}
      }
      
    }
  }
  
  
  //set x1
  for(i=0;i<N;i++){
    x1[i]=NumVarMatrix(env,N);
    for(j=0;j<N;j++){
      x1[i][j]=IloNumVarArray(env,n_max[1]);
      for(k=0;k<n_max[1];k++){
	if(i==j){
	  x1[i][j][k]=IloIntVar(env,0,0);
	}else{
	  x1[i][j][k]=IloIntVar(env,0,1);
	}
      }

    }
  }
 
  
  //set x2
  for(i=0;i<N;i++){
    x2[i]=NumVarMatrix(env,N);
    for(j=0;j<N;j++){
      x2[i][j]=IloNumVarArray(env,n_max[2]);
      for(k=0;k<n_max[2];k++){
	if(i==j){
	  x2[i][j][k]=IloIntVar(env,0,0);
	}else{
	  x2[i][j][k]=IloIntVar(env,0,1);
	}
      }

    }
  }
  
  //objective function
  IloExpr cb_sum(env);
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      cb_sum+=cb_ij[i][j];
    }
  }
  model.add(IloMinimize(env, cb_sum));

  
  //constraint 13-a
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(i!=j){
	model.add(IloSum(x0[i][j])==1);
	model.add(IloSum(x1[i][j])==1);
	model.add(IloSum(x2[i][j])==1);
      }
    }
  }
  
  //constraint 13-b
  IloIntArray n_k(env,3);



  for(k=0;k<K;k++){
    for(i=0;i<N;i++){
      for(j=0;j<N;j++){
	
	IloExpr left(env);
	IloExpr right0(env);
	IloExpr right1(env);
	IloExpr right2(env);
	if(i!=j){
	  
	  for(s=0;d<N;s++){
	    for(d=0;d<N;d++){
	      if(s!=d){
	      left+=b_sd_ij[s][d][i][j]*f_k_sd[k][s][d];
	      }
	    }
	  }
	  
	  for(n_k[0]=0; n_k[0]<n_max[0]; n_k[0]++){
	    right0+= n_k[0]*x0[i][j][k];
	  }
	  model.add(left==right0);
	  
	  for(n_k[1]=0; n_k[1]<n_max[1]; n_k[1]++){
	    right1+= n_k[1]*x0[i][j][k];
	  }
	  model.add(left==right1);
	  
	  for(n_k[2]=0; n_k[2]<n_max[2]; n_k[2]++){
	  right2+= n_k[2]*x0[i][j][k];
	  }
	  model.add(left==right2);
	  
	}
      }
    }
  }
  

  
  //Constraint 13-j
  for(s=0;s<N;s++){
    for(d=0;d<N;d++){
	for(i=0;i<N;i++){
	  
	  IloExpr flow(env);
	  IloExpr flow_inv(env);
	  
	  for(j=0;j<N;j++){
	    flow+=b_sd_ij[s][d][i][j];
	    flow_inv+=b_sd_ij[s][d][j][i];
	  }
	  
	  
	  
	    if(s==i){
	      model.add(flow-flow_inv==1);
	    }else if(d==i){
	      model.add(flow-flow_inv==-1);
	    }else{
	      model.add(flow-flow_inv==0);
	    }
	    
	    
       }
    }
  }

  
  



  //solve ILP
  IloCplex cplex(model);
  IloIntArray vals(env);


  cplex.solve();
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      vals.add(cplex.getValue(cb_ij[i][j]));
    }
  }
  
  env.out() << "Solution Value = " <<  cplex.getObjValue() << endl;
  env.out() << "Backup Capacity = " << vals << endl;
  env.end();
  return 0;
}
