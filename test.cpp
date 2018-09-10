#include<ilcplex/ilocplex.h>
#define N 2

using namespace std;
typedef IloArray<IloArray<IloIntArray> > Int3DArray; // 3D matrix of int coefficients
typedef IloArray<IloIntArray>    IntMatrix;  // 2D matrix of int coefficients
typedef IloArray<IloArray<IloArray<IloNumVarArray> > > NumVar4DArray; // 4D matrix of variables
typedef IloArray<IloArray<IloNumVarArray> > NumVar3DArray; // 3D matrix of variables
typedef IloArray<IloNumVarArray> NumVarMatrix; // 2D matrix of variables

int main() {
  IloEnv env;
  IloModel model(env);

  NumVarMatrix x(env,N);


  IloInt i,j;

  for(i=0; i<N; i++){
    x[i]=IloNumVarArray(env,N);
  }

  x[0][0]= IloIntVar(env,0,0);
  x[0][1]= IloIntVar(env,0,1);
  x[1][0]= IloIntVar(env,0,0);
  x[1][1]= IloIntVar(env,0,1);

  model.add(x[0][0]+x[0][1]==1);
  model.add(x[1][0]+x[1][1]==1);

  IloExpr sum(env);

  sum+=x[0][0];
  sum+=x[1][0];
  model.add(IloMinimize(env,sum));

  //solve ILP
  IloCplex cplex(model);
  IloIntArray vals(env);


  cplex.solve();
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      vals.add(cplex.getValue(x[i][j]));
    }
  }

  env.out() << "Solution Value = " <<  cplex.getObjValue() << endl;
  env.out() << "Backup Capacity = " << vals << endl;
  env.end();
  return 0;
}
