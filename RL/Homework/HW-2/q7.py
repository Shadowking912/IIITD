import numpy as np
import sys



#solve non linear using policy iteration algorithm
rows=5
columns=5
A=(0,1)
A_prime=(4,1)
B=(0,3)
B_prime=(2,3)

#calculate next state
def next_state(state, action):
    global rows, columns
    if state == A:
        return A_prime, 10
    if state == B:
        return B_prime, 5
    
    r=state[0]+action[0]
    c=state[1]+action[1]
    rew=0
    if r<0 or r>=rows or c<0 or c>=columns:
        rew=-1
        return state,rew
    return (r,c),rew

#policy evaluation
def policy_evaluation(policy, discount_factor=0.9, theta=1e-10):
    V={}
    for i in range(rows):
        for j in range(columns):
            V[(i,j)]=0
    while True:
        delta = 0
        #for all states calculate the value function for current policy
        for state in V:
            v = V[state]
            r=0
            for action in policy[state]:
                next_s,rew=next_state(state,action)
                r+=policy[state][action]*(rew+discount_factor*V[next_s])
            V[state] = r
            delta = max(delta, abs(v - V[state]))
        #break if value function converged
        if delta < theta:
            break
    return V

#policy improvement
def policy_improvement(V,policy,discount_factor=0.9):

    #for all states calculate the best action
    for state in V:
        q_values = np.zeros(4)  # 4 actions
        for i in range(len(actions)):
            action=actions[i]
            next_s,rew=next_state(state,action)
            action_value=rew + discount_factor * V[next_s]
            q_values[i]=(action_value)
        #take the first occurence of the max value
        best_action = np.argmax(q_values)
        policy[state] = {actions[best_action]:1}  # deterministic policy
    return policy

actions=[(0,-1),(-1,0),(0,1),(1,0)]


policy={}
for i in range(rows):
    for j in range(columns):
        policy[(i,j)]={(0,-1):0.25,(-1,0):0.25,(0,1):0.25,(1,0):0.25}

#loop for policy iteration
def policy_iteration():
    global policy
    iter=0
    while True:
        iter+=1
        old_policy = policy.copy()
        V = policy_evaluation(policy)
        new_policy = policy_improvement(V,policy)
        #break if policy converged
        if old_policy==new_policy:
            break
        policy = new_policy
    return policy, V


print("Value function:")
policy, V_star = policy_iteration()
for i in range(rows):
    for j in range(columns):
        print(round(V_star[(i,j)],1),end=" ")
    print()
print()
print("Policy:")
for i in range(rows):
    for j in range(columns):
        print(policy[(i,j)],end=" ")
    print()    
# print(policy)