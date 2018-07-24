#include<ilcplex/ilocplex.h>
#define N 4

using namespace std;


int main() {

  int p_link[N][N];
  

  //primary network




  

  IloEnv env;
  IloModel model(env);
  IloNumVarArray vars(env);

  vars.add(IloIntVar(env, 0, 1));
  vars.add(IloIntVar(env, 0, 1));
  vars.add(IloIntVar(env, 0, 1));
  vars.add(IloIntVar(env, 0, 1));
  vars.add(IloIntVar(env, 0, 1));

  model.add(IloMaximize(env, 3*vars[0] + 2*vars[1] + 2*vars[2] + 4*vars[3] + 3*vars[4]));
  model.add( 2*vars[0] + 3*vars[1] + 1*vars[2] + 2*vars[3] + 3*vars[4] <= 6);

  IloCplex cplex(model);
  IloNumArray vals(env);

  cplex.solve();
  cplex.getValues(vals, vars);

  env.out() << "Solution Value = " <<  cplex.getObjValue() << endl;
  env.out() << "Values = " << vals << endl;
  env.end();
  return 0;
}
