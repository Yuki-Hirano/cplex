# -*- coding: utf-8 -*-
import numpy as np

N=4 # number of nodes


def given_info():

    cap_list=[1,5,10]
    f_0=np.zeros((4,4))
    f_1=np.zeros((4,4))
    f_2=np.zeros((4,4))

#primary network capacity
    cp=[[0,10,10,10],
        [1, 0, 5, 1],
        [1, 1, 0, 1],
        [1, 1, 5, 0]]

#set f_k^sd 
    n_max_0=0
    n_max_1=0
    n_max_2=0
    for s in range(N):
        for d in range(N):
            if cp[s][d]==cap_list[0]:
                f_0[s][d]=1
                n_max_0+=1
            elif cp[s][d]==cap_list[1]:
                f_1[s][d]=1
                n_max_1+=1
            elif cp[s][d]==cap_list[2]:
                f_2[s][d]=1
                n_max_2+=1
#print(f_0)
    #print(f_1)
    #print(f_2)

#set Omega
                #Omega=[]
                #for i in range(n_max_0):
                    for j in rnage(n_max_1):
                        for k in range(n_max_2):
                            Omega.append([])
                            #probability=0.075 epsilon=0.05
                            Omega=[
                                [[0,10,10],[5,10,10]],
                                [[1,10,10],[5,10,10]],
                                [[1,10,10],[5,10,10]],
                                [[1,10,10],[5,10,10]],
                                [[1,10,10],[5,10,11]],
                                [[1,10,11],[5,10,11]],
                                [[2,10,11],[5,10,11]],
                                   ]

    #if char=="p":   #primary network
     #   return cp
    




def create_LP():
    given_info()
    
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
