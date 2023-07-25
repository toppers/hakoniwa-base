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
import hako_robomodel_ev3 as ev3

def handler(signum, frame):
  print(f'SIGNAL(signum={signum})')
  sys.exit(0)

def sync_pdu(robo):
  for channel_id in robo.actions:
    robo.hako.write_pdu(channel_id, robo.actions[channel_id])

print("START TEST")

# signal.SIGALRMのシグナルハンドラを登録
signal.signal(signal.SIGINT, handler)

#do simulation
#create hakoniwa env
env = hako_env.make("EV3TrainModel", "ev3")

while True:
  print("WAIT START:")
  env.hako.wait_event(hako.HakoEvent['START'])
  print("WAIT RUNNING:")
  env.hako.wait_state(hako.HakoState['RUNNING'])
  print("WAIT PDU CREATED:")
  env.hako.wait_pdu_created()

  robo = env.robo()
  print("GO:")

  while True:
    if env.hako.execute_step() == False:
      if env.hako.state() != hako.HakoState['RUNNING']:
        print("WAIT_STOP")
        env.hako.wait_event(hako.HakoEvent['STOP'])
        print("WAIT_RESET")
        env.hako.wait_event(hako.HakoEvent['RESET'])
        print("DONE")
        break
      else:
        time.sleep(0.01)
        continue
    sensors = env.hako.read_pdus()
    touch_sensor = sensors[1]['touch_sensors'][0]
    if touch_sensor['value'] == 0:
      robo.actions[0]['motors'][0]['power'] = 20
    else:
      robo.actions[0]['motors'][0]['power'] = 0
    for channel_id in robo.actions:
      env.hako.write_pdu(channel_id, robo.actions[channel_id])
