import numpy as np
import sys
#policy iteration algorithm
rows=4
columns=4
terminals=[(0,0),(3,3)]

#calculate next state
def next_state(state, action):
    global rows, columns
    if state in terminals:
        return state, 0
    r=state[0]+action[0]
    c=state[1]+action[1]
    rew=-1
    #if next state is out of grid
    if r<0 or r>=rows or c<0 or c>=columns:
        rew=-1
        return state,rew
    return (r,c),rew

def show_values(V):
    for i in range(rows):
        for j in range(columns):
            print(round(V[(i,j)],1),end=" ")
        print()
    print()

def show_policy(policy):
    for i in range(rows):
        for j in range(columns):
            print(policy[(i,j)],end=" ")
        print()
    print()

#policy evaluation
def policy_evaluation(policy, discount_factor=1, theta=1e-10):
    print("LOG: policy_evaluation")
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
        # best_actions=list[list == np.max(list)]
        best_action = np.argmax(q_values)#takes the first occurence of the max value
        policy[state] = {actions[best_action]:1}  # deterministic policy
    return policy

actions=[(0,-1),(-1,0),(0,1),(1,0)]

#initial policy
policy={}
for i in range(rows):
    for j in range(columns):
        policy[(i,j)]={(0,-1):0.25,(-1,0):0.25,(0,1):0.25,(1,0):0.25}

def policy_iteration():
    global policy
    iter=0
    
    while True:
        iter+=1
        print("LOG: iteration ",iter)
        old_policy = policy.copy()
        V = policy_evaluation(policy)
        print("LOG: Value function")
        show_values(V)
        new_policy = policy_improvement(V,policy)
        print("LOG: Updated Policy")
        show_policy(new_policy)

        #break if policy converged
        if old_policy==new_policy:
            break
        policy = new_policy
    return policy, V

#run policy iteration
print("LOG: Policy Iteration")
print("LOG: Initial Policy")
show_policy(policy)
policy, V_star = policy_iteration()
print("LOG: policy iteration completed")
print("LOG: Final Value function")
show_values(V_star)
print("LOG: Final Policy")
show_policy(policy)    



#value iteration algorithm
def value_iteration(discount_factor=1, theta=1e-10):
    iter=0
    V={}
    #initialize value function
    for i in range(rows):
        for j in range(columns):
            V[(i,j)]=0
    print("LOG: intial value function")
    show_values(V)

    while True:
        iter+=1
        print("LOG: iteration ",iter)
        delta = 0
        for state in V:
            v = V[state]
            #calculate q values for all actions
            q_values = np.zeros(4)  # 4 actions
            for a in range(len(actions)):
                action = actions[a]
                next_s, rew = next_state(state, action)
                q_values[a] = rew + discount_factor * V[next_s]
            #update value function
            V[state] = np.max(q_values)
            delta = max(delta, abs(v - V[state]))
        print("LOG: updated value function")
        show_values(V)
        if delta < theta:
            break
    return V

print("LOG: Value Iteration")
V_star = value_iteration()
print("LOG: value iteration completed")
print("LOG: Final Value function")
show_values(V_star)