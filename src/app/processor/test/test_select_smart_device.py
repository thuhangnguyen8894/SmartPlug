import sys
import os
import unittest

LIDT_ROOT = os.environ['LIDT_ROOT']
sys.path.append(LIDT_ROOT + '/src/app/processor')

import lib_db_manager

class TestSelectSmartDeviceMethods(unittest.TestCase):

    def test_selectSmartDevice(self):
        lib_db_manager_obj = lib_db_manager.LibDBManager()
        expected_result = [
            {
                'idSmartDevice': 'SD002', 
                'idRoom': 'R0001',
                'nameSmartDevice': 'DEVICE_LIGHT'
            },
            {
                'idSmartDevice': 'SD003', 
                'idRoom': 'R0001',
                'nameSmartDevice': 'DEVICE_PLUS'
            },
            {
                'idSmartDevice': 'SD004', 
                'idRoom': 'R0001',
                'nameSmartDevice': 'DEVICE_LIGHT'
            },
            {
                'idSmartDevice': 'SD005', 
                'idRoom': 'R0001',
                'nameSmartDevice': 'DEVICE_FAN'
            },
            {
                'idSmartDevice': 'SD006', 
                'idRoom': 'R0001',
                'nameSmartDevice': 'DEVICE_TIVI'
            }
        ]

        try:
            result = lib_db_manager_obj.select_smartdevice()
            self.assertTrue(True)
        except:
            self.assertTrue(False)

        self.assertEqual(expected_result, result)


if __name__ == '__main__':
    unittest.main()