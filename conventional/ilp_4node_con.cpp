#include<ilcplex/ilocplex.h>
#define N 4
#define M_max 3
#define K 15

using namespace std;
typedef IloArray<IloArray<IloIntArray> > Int3DArray; // 3D matrix of int coefficients
typedef IloArray<IloIntArray>    IntMatrix;  // 2D matrix of int coefficients
// typedef IloArray<IloArray<IloArray<IloArray<IloNumVarArray> > > > NumVar5DArray; // 4D matrix of variables
typedef IloArray<IloArray<IloArray<IloNumVarArray> > > NumVar4DArray; // 4D matrix of variables
typedef IloArray<IloArray<IloNumVarArray> > NumVar3DArray; // 3D matrix of variables
typedef IloArray<IloNumVarArray> NumVarMatrix; // 2D matrix of variables

int main() {



  IloEnv env;
  IloModel model(env);

  NumVarMatrix cb_ij(env,N);
  NumVar4DArray b_sd_ij(env,N);
  NumVar4DArray theta_sd_ij(env,N);
  NumVar3DArray x_ij_m(env,N);
  NumVar3DArray y_ij_m(env,N);
  NumVarMatrix nu_ij(env,N);

  IntMatrix p_link(env,N);
  IloIntArray Lm_prime(env,M_max+1);
  IloInt s,d,i,j,m;

  //primary network
  for(s=0;s<N;s++){
    p_link[s]=IloIntArray(env,N);
  }
  p_link[0][0]=0; p_link[0][1]=10; p_link[0][2]=10; p_link[0][3]=10;
  p_link[1][0]=1; p_link[1][1]=0; p_link[1][2]=5; p_link[1][3]=1;
  p_link[2][0]=1; p_link[2][1]=1; p_link[2][2]=0; p_link[2][3]=1;
  p_link[3][0]=1; p_link[3][1]=1; p_link[3][2]=5; p_link[3][3]=0;

  //L(m')(p=0.1,eps=0.05)
  Lm_prime[0]=0;
  Lm_prime[1]=3;
  Lm_prime[2]=8;
  Lm_prime[3]=12;



  //set cb_ij
  for(i=0;i<N;i++){
    cb_ij[i]=IloNumVarArray(env,N);
    for(j=0;j<N;j++){
      if(i==j){
        cb_ij[i][j]=IloIntVar(env,0,0);
      }else{
        cb_ij[i][j]=IloIntVar(env);
      }
    }
  }


  //set b_sd_ij,theta_sd_ij
  for(s=0;s<N;s++){
    b_sd_ij[s]=NumVar3DArray(env,N);
    theta_sd_ij[s]=NumVar3DArray(env,N);
    for(d=0;d<N;d++){
      b_sd_ij[s][d]=NumVarMatrix(env,N);
      theta_sd_ij[s][d]=NumVarMatrix(env,N);
      for(i=0;i<N;i++){
        b_sd_ij[s][d][i]=IloNumVarArray(env,N);
        theta_sd_ij[s][d][i]=IloNumVarArray(env,N);
        for(j=0;j <N;j++){
          if(s==d || i==j){
            b_sd_ij[s][d][i][j]=IloIntVar(env,0,0);
            theta_sd_ij[s][d][i][j]=IloIntVar(env,0,0);
          }else{
            b_sd_ij[s][d][i][j]=IloIntVar(env,0,1);
            theta_sd_ij[s][d][i][j]=IloIntVar(env,0,1000);
          }
        }
      }
    }
  }

//set nu_ij
for(i=0;i<N;i++){
  nu_ij[i]=IloNumVarArray(env,N);
  for(j=0;j<N;j++){
    if(i==j){
      nu_ij[i][j]=IloIntVar(env,0,0);
    }else{
      nu_ij[i][j]=IloIntVar(env,0,1000);
    }
  }
}

  //set x_m_ij
  for(i=0;i<N;i++){
    x_ij_m[i]=NumVarMatrix(env,N);
    for(j=0;j<N;j++){
      x_ij_m[i][j]=IloNumVarArray(env,M_max+1);
      for(m=0;m<M_max+1;m++){
        if(i==j){
          x_ij_m[i][j][m]=IloIntVar(env,0,0);
        }else{
          x_ij_m[i][j][m]=IloIntVar(env,0,1);
        }
      }
    }
  }

  //set y_m_ij
  for(i=0;i<N;i++){
    y_ij_m[i]=NumVarMatrix(env,N);
    for(j=0;j<N;j++){
      y_ij_m[i][j]=IloNumVarArray(env,M_max+1);
      for(m=0;m<M_max+1;m++){
        if(i==j){
          y_ij_m[i][j][m]=IloIntVar(env,0,0);
        }else{
          y_ij_m[i][j][m]=IloIntVar(env,0,1000);
        }
      }
    }
  }


 //Constraint eq.(27)
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     if(i!=j){
       IloExpr right1(env);
       IloExpr right2(env);

       for(m=0;m<M_max+1;m++){
         right1+=m*y_ij_m[i][j][m];
       }

       for(s=0;s<N;s++){
         for(d=0;d<N;d++){
             right2+=theta_sd_ij[s][d][i][j];
         }
       }

       model.add(cb_ij[i][j]>=right1+right2);
     }
   }
 }


 //Constraint eq.(28)
 for(s=0;s<N;s++){
   for(d=0;d<N;d++){
     for(i=0;i<N;i++){
       for(j=0;j<N;j++){
         if(s!=d && i!=j){
           model.add(nu_ij[i][j]+theta_sd_ij[s][d][i][j]>=p_link[s][d]*b_sd_ij[s][d][i][j]);
         }
       }
     }
   }
 }


 //Constraiunt eq.(29)
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     if(i!=j){
       model.add(IloSum(x_ij_m[i][j])==1);
     }
   }
 }

 //Constraint eq.(30)
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     if(i!=j){
       IloExpr left(env);
       IloExpr right(env);

       for(s=0;s<N;s++){
         for(d=0;d<N;d++){
           if(s!=d){
             left+=b_sd_ij[s][d][i][j];
           }
         }
       }

       for(m=0;m<M_max+1;m++){
         right+=Lm_prime[m]*x_ij_m[i][j][m];
       }

       model.add(left<=right);
     }
   }
 }

 //Constraint eq.(31),(32)
 for(i=0;i<N;i++){
   for(j=0;j<N;j++){
     if(i!=j){
       for(m=0;m<M_max+1;m++){
         model.add(y_ij_m[i][j][m]>=nu_ij[i][j]+K*(x_ij_m[i][j][m]-1));
         model.add(y_ij_m[i][j][m]<=K*x_ij_m[i][j][m]);
       }
     }
   }
 }


  //Constraint eq.(33)
  for(s=0;s<N;s++){
    for(d=0;d<N;d++){
      for(i=0;i<N;i++){
        IloExpr flow(env);
        if(s!=d){
          for(j=0;j<N;j++){
            if(i!=j){
              flow += b_sd_ij[s][d][i][j];
              flow -= b_sd_ij[s][d][j][i];
            }
          }

          if(s==i){
            model.add(flow == 1);
          }else if(d==i){
            model.add(flow  == -1);
          }else{
            model.add(flow == 0);
          }
        }
        // flow.end();
      }
    }
  }




  //objective function
  IloExpr cb_total(env);
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(i!=j){
        cb_total+=cb_ij[i][j];
      }
    }
  }
  model.add(IloMinimize(env,cb_total));


  //solve ILP
  IloCplex cplex(model);
  //cplex.setParam(IloCplex::Param::MIP::Tolerances::MIPGap,0.0001);
  cplex.solve();
  //env.out() << "MIPGap = " << IloCplex::EpAGap << endl;
  //env.out() << "MIPGap = " << IloCplex::Param::MIP::Tolerances::MIPGap << endl;
  //env.out() << "Timelimit = " << IloCplex::Param::TimeLimit << endl;
  env.out() << "Solution Value = " <<  cplex.getObjValue() << endl;

//
//   //b_sd_ij
//   env.out() << "b_sd_ij" << endl;
//   for(s=0;s<N;s++){
//     for(d=0;d<N;d++){
//       if(s!=d){
//         env.out() << "(" << s << ", " << d << ") --- ";
//         for(i=0;i<N;i++){
//           for(j=0;j<N;j++){
//             if(i!=j){
//             if(cplex.getValue(b_sd_ij[s][d][i][j])==1){
//               env.out() << "(" << i << ", " << j << ") , ";
//             }
//           }
//         }
//       }
//     }
//     env.out() << endl;
//   }
// }



//cb_ij
env.out() << "Backup Capacity Array" << endl;
for(i=0;i<N;i++){
  for(j=0;j<N;j++){
    if(i==j){
      env.out() << "0 ";
    }else{
      env.out() << cplex.getValue(cb_ij[i][j]) << " ";
    }
  }
  env.out() << endl;
}

env.end();
return 0;
}
