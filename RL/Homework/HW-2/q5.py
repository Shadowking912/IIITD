import numpy as np
import sys

#function to get new coordinates after taking an action
def new_coord(action,i,j):
    r=i+action[0]
    c=j+action[1]
    return r,c

#grid
rows=5
cols=5
discounting_factor = 0.9

#special states
term_A=(0,1)
A_prime=(4,1)
term_B=(0,3)
B_prime=(2,3)

#actions
actions = [(0,-1),(-1,0),(0,1),(1,0)]
action_prob = 0.25


#solve using linear equation of form Ax=b

#A
A=np.zeros((rows*cols,rows*cols))

#order of variables in the system
d={}
for i in range(rows):
    for j in range(cols):
        d[(i,j)]=len(d)

#b
b=np.zeros((rows*cols))

#for each equation in the system calculate the coefficients of the variables in A and the constants in b
for i in range(rows):
    for j in range(cols):

        #special states
        if (i,j)==term_A:
            A[d[(i,j)],d[(i,j)]]=-1
            A[d[(i,j)],d[A_prime]]=1*discounting_factor
            b[d[(i,j)]]=-10
        elif (i,j)==term_B:
            A[d[(i,j)],d[(i,j)]]=-1
            A[d[(i,j)],d[B_prime]]=1*discounting_factor
            b[d[(i,j)]]=-5

        #normal states
        else:
            for action in actions:
                new_i,new_j=new_coord(action,i,j)

                #out of grid actions
                if new_i<0 or new_i>=rows or new_j<0 or new_j>=cols:
                    new_i,new_j=i,j
                    rew=-1
                #normal actions
                else:
                    rew=0
                A[d[(i,j)],d[(new_i,new_j)]]+=action_prob*discounting_factor
                b[d[(i,j)]]-=rew*action_prob
            A[d[(i,j)],d[(i,j)]]+=-1

#solve the linear system
solution = np.linalg.solve(A, b)

#display the value for each variable in the system
print("Values of the states:")
for i in range(rows):
    for j in range(cols):
        print(round(solution[d[(i,j)]],1),end=" ")
    print()                 