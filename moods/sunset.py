#!/usr/bin/env python

import time
import requests

url='http://192.168.1.112/{0}'

for i in range(0, 8):
  requests.get(url.format('decrease'))
  time.sleep(75)

