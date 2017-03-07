"""
File: cdevice_timer.py
=========================

Copyright (c) Trang Tran

Modified History
----------------
2017-Mar-01 Created tn-trang.tran@outlook.com
"""

class Device_Timer:
	def __init__(self, idTimer, idSmartDevice, stateElectric, stateRelay):
		self.idTimer  = idTimer
		self.idSmartDevice  = idSmartDevice
		self.stateElectric  = stateElectric
		self.stateRelay  = stateRelay
		