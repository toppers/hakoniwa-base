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
import hako_robomodel_tb3 as tb3

def handler(signum, frame):
  print(f'SIGNAL(signum={signum})')
  sys.exit(0)
  
print("START TB3 TEST")

# signal.SIGALRMのシグナルハンドラを登録
signal.signal(signal.SIGINT, handler)

#create hakoniwa env
env = hako_env.make("base_practice_1", "tb3")
print("WAIT START:")
env.hako.wait_event(hako.HakoEvent['START'])
print("WAIT RUNNING:")
env.hako.wait_state(hako.HakoState['RUNNING'])

print("GO:")

#do simulation

robo = env.robo()

for episode in range(1):
  total_time = 0
  done = False
  state = 0
  total_reward = 0
  #100secs
  while not done and total_time < 4000:
    sensors = env.hako.execute()
      
    img = env.robo().camera_data(sensors)
    with open("camera.jpg" , 'bw') as f:
        f.write(img)
    
    scan_datas = env.robo().laser_scan(sensors)
    #print("d_f=%f" % env.robo().get_forward_distance(scan_datas))
    if env.robo().get_forward_distance(scan_datas) >= 0.2:
        env.robo().foward(0.5)
        env.robo().turn(0.0)
    else:
        env.robo().foward(0.0)
        env.robo().turn(-0.5)
    
    env.robo().step()  
    total_time = total_time + 1

  env.reset()


print("END")
env.reset()
sys.exit(0)

