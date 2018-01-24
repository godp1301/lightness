#!/usr/bin/env python

import time
import requests

url='http://192.168.1.112/{0}'

requests.get(url.format('on'))
requests.get(url.format('white'))

for i in range(0, 8):
  time.sleep(75)
  requests.get(url.format('increase'))

