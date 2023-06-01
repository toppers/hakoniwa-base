#!/usr/bin/python
# -*- coding: utf-8 -*-
import json
import sys
from hako_binary import offset_map
from hako_binary import binary_writer
from hako_binary import binary_reader
import qtable_model2
import hako_env
import hako
import time
import signal
import numpy as np
import hako_robomodel_ev3 as ev3
import csv


def handler(signum, frame):
  print(f'SIGNAL(signum={signum})')
  sys.exit(0)

# signal.SIGALRMのシグナルハンドラを登録
signal.signal(signal.SIGINT, handler)

#create hakoniwa env
env = hako_env.make("Ev3TransportModel", "ev3")
env.hako.wait_event(hako.HakoEvent['START'])
env.hako.wait_state(hako.HakoState['RUNNING'])


#do simulation

max_episode_num = 500 #1試行あたりのエピソード数
average_num = 5 #直近何回の報酬の平均を取るか
trial_num = 300 #試行の数

for i in range(trial_num):
  reward_list = [0.0]*average_num #直近報酬データの保持用リスト
  sum = 0.0 #直近報酬の和
  model = qtable_model2.get_model(env.robo().num_states(), env.robo().num_actions())
  robo = env.robo()
  max_reward_average = 0.0  #最大平均合計報酬
  number_of_episode = max_episode_num
  episode_num_list = np.loadtxt('./dev/ai/episode.csv', delimiter=',').astype(int)  #csvファイルを読み込み、末尾にデータを追加して戻すため
  for episode in range(max_episode_num):
    total_time = 0
    done = False
    state = 0
    total_reward = 0
    reward_average = sum/average_num  #直近の平均合計報酬
    max_reward_average = max(max_reward_average, reward_average)
    if(max_reward_average > 420000):
      number_of_episode = episode - 4 #収束判定
      break
    #100secs
    while not done and total_time < 4000:
        
        action = model.get_action(state, max_reward_average, reward_average)
        next_state, reward, done, _ = env.step(action)
        total_reward = total_reward + reward
        model.learn(state, action, reward, next_state)
        
        state = next_state    
        total_time = total_time + 1

    env.reset()
    model.save('./dev/ai/qtable_model.csv')
    old_reward = reward_list.pop(0)
    reward_list.append(total_reward)
    sum += total_reward - old_reward
    print("trial="+str(i)+" episode=" + str(episode) + " total_time=" + str(total_time) + " total_reward=" + str(total_reward))
  episode_num_list = np.append(episode_num_list, number_of_episode)
  np.savetxt("dev/ai/episode.csv", episode_num_list, delimiter=',', fmt='%d')
  


print("END")
env.reset()
sys.exit(0)

