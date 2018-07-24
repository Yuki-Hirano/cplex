# -*- coding: utf-8 -*-

import numpy as np

def given_info(char):

    cap_list=[1,5,10]
    f_0=np.zeros(4,4)
    f_1=np.zeros(4,4)
    f_2=np.zeros(4,4)

    cp=[[0,10,10,10],
        [1, 0, 5, 1],
        [1, 1, 0, 1],
        [1, 1, 5, 0]]

    for s in range(N):
        for d in range(N):
            if cp[s][d]==cp_list[0]:
                f_0[s][d]=1
            elif cp[s][d]==cp_list[1]:
                f_1[s][d]=1
            elif cp[s][d]==cp_list[2]:
                f_2[s][d]=1
    print(f_0)
    print(f_1)
    print(f_2)



    
    #if char=="p":   #primary network
     #   return cp
    




def create_LP():
    given_info()
    N=4 # number of nodes 
    
    path= "./ilp_4node.lp"
    with open(path, mode="w") as f:
        f.write("minimize\n") #objective function
        for i in range(N):
            for j in range(N):
                if i==N-1 and j==N-1:
                    f.write("cb_{0}_{1}".format(i,j))
                else:
                    f.write("cb_{0}_{1}+".format(i,j)) #backup capacity cb_i_j
        f.write("\n")
        f.write("subject to") #constraint
        
if __name__=="__main__":
     create_LP()
