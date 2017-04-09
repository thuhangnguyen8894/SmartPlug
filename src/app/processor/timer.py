"""
File: ctimer.py
=========================

Copyright (c) Trang Tran

Modified History
----------------
2017-Mar-01 Created tn-trang.tran@outlook.com
"""

class Timer:
    def __init__(self, idTimer, daySD, monthSD, yearSD, hourSD, minuteSD, secondSD):
        self.idTimer  = idTimer
        self.daySD  = daySD
        self.monthSD  = monthSD
        self.yearSD  = yearSD
        self.hourSD  = hourSD
        self.minuteSD = minuteSD
        self.secondSD = secondSD