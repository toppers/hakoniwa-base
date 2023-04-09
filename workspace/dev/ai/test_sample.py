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
from types import MethodType
import hako_robomodel_any


def handler(signum, frame):
  print(f'SIGNAL(signum={signum})')
  sys.exit(0)
  
print("START TB3 TEST")

# signal.SIGALRMのシグナルハンドラを登録
signal.signal(signal.SIGINT, handler)

#create hakoniwa env
env = hako_env.make("arm_robot", "any", "dev/ai/custom.json")
print("WAIT START:")
env.hako.wait_event(hako.HakoEvent['START'])
print("WAIT RUNNING:")
env.hako.wait_state(hako.HakoState['RUNNING'])

print("GO:")

#do simulation
def delta_usec():
  return 20000

robo = env.robo()
robo.delta_usec = delta_usec

for episode in range(1):
  total_time = 0
  done = False
  state = 0
  total_reward = 0
  #100secs
  while not done and total_time < 4000:
    
    f = open('dev/ai/cmd.txt', 'r')
    value = f.readlines()
    f.close()
    
    sensors = env.hako.execute()
    
    servo_angle = robo.get_action('servo_angle')
    servo_angle['angular']['y'] = float(value[0])
    #servo_angle2 = robo.get_action('servo_angle2')
    #servo_angle2['angular']['y'] = -10
    #servo_angle3 = robo.get_action('servo_angle3')
    #servo_angle3['angular']['y'] = 10
    #servo_angle4 = robo.get_action('servo_angle4')
    #servo_angle4['angular']['y'] = -1
    #pincher_cmd = robo.get_action('pincher_cmd')
    #pincher_cmd['linear']['x'] = -1
    
    for channel_id in robo.actions:
      robo.hako.write_pdu(channel_id, robo.actions[channel_id])
    
    total_time = total_time + 1

  env.reset()


print("END")
env.reset()
sys.exit(0)

