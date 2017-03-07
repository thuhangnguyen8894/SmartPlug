"""
File: csmartdevice.py
=========================

Copyright (c) Trang Tran

Modified History
----------------
2017-Mar-01 Created tn-trang.tran@outlook.com
"""

class SmartDevice:

	def __init__(self, idSmartDevice, ip_port, idRoom, nameSmartDevice, listIdTimer = None):
		self.idSmartDevice = idSmartDevice
		self.ip_port = ip_port
		self.idRoom = idRoom
		self.nameSmartDevice = nameSmartDevice

		if listIdTimer is None:
			self.listIdTimer = []
		else:
			self.listIdTimer = listIdTimer

	def addEmplementIdTimer(self, idTimer):
		self.listIdTimer.append(idTimer)
		return self.listIdTimer