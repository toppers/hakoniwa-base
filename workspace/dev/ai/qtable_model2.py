#!/usr/bin/python
# -*- coding: utf-8 -*-

import numpy as np
import os

class QtableModel:
    def __init__(self, num_states, num_actions):
        #q_tableを乱数で初期化
        self.num_states = num_states
        self.num_actions = num_actions
        self.q_table = np.random.uniform(0, 1, (num_states,num_actions))

    def save(self, filepath):
        np.savetxt(filepath, self.q_table, delimiter=',')

    def load(self, filepath):
        if os.path.isfile(filepath):
            print("qtable model is loaded:" + filepath)
            self.q_table = np.loadtxt(filepath, delimiter=',')

    def get_action(self, next_state):
        epsilon = 0.001
        if epsilon < np.random.uniform(0,1):
            next_action = np.argmax(self.q_table[next_state])
        else:
            next_action = np.random.randint(low = 0, high = self.num_actions -1)        
        return next_action

    def learn(self, state, action, reward, next_state):
        gamma=0.99
        alpha=0.5
        self.q_table[state, action] = \
            (1 - alpha) * self.q_table[state, action] + \
            alpha * (reward + gamma * max(self.q_table[next_state]))

def get_model(num_states, num_actions):
    return QtableModel(num_states, num_actions)
