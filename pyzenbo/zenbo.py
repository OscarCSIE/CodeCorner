import logging
import os


import pyzenbo.modules.inter_communication as _inter_comm
import pyzenbo.modules.zenbo_command as commands
from pyzenbo.modules.baidu import Baidu
from pyzenbo.modules.dialog_system import DialogSystem
from pyzenbo.modules.inter_communication import DESTINATION
from pyzenbo.modules.line_follower import LineFollower
from pyzenbo.modules.media import Media
from pyzenbo.modules.motion import Motion
from pyzenbo.modules.sensor import Sensor
from pyzenbo.modules.system import System
from pyzenbo.modules.utility import Utility
from pyzenbo.modules.vision_control import VisionControl
from pyzenbo.modules.wheel_lights import WheelLights

logger = logging.getLogger('pyzenbo')


class PyZenbo:

    _inter_comm = _inter_comm.InterComm()

    motion = Motion(_inter_comm)

    robot = DialogSystem(_inter_comm)

    utility = Utility(_inter_comm)

    wheelLights = WheelLights(_inter_comm)

    baidu = Baidu(_inter_comm)

    vision = VisionControl(_inter_comm)

    lineFollower = LineFollower(_inter_comm)

    sensor = Sensor(_inter_comm)

    system = System(_inter_comm)

    media = Media(_inter_comm)


    def __init__(self, destination, on_state_change_callback=None, on_result_callback=None):
        if os.getenv('KEY_RUN_LOCALLY', 'false') == 'true':
            destination = '127.0.0.1'
        self._inter_comm.init((destination, 55555), on_state_change_callback, on_result_callback, timeout=2)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.release()

    @property
    def on_state_change_callback(self):
        return self._inter_comm.on_state_change_callback

    @on_state_change_callback.setter
    def on_state_change_callback(self, on_state_change_callback):
        logger.debug(self._inter_comm.on_state_change_callback)
        self._inter_comm.on_state_change_callback = on_state_change_callback
        logger.debug(self._inter_comm.on_state_change_callback)

    @on_state_change_callback.deleter
    def on_state_change_callback(self):
        del self._inter_comm.on_state_change_callback

    @property
    def on_result_callback(self):
        return self._inter_comm.on_result_callback

    @on_result_callback.setter
    def on_result_callback(self, on_result_callback):
        self._inter_comm.on_result_callback = on_result_callback

    @on_result_callback.deleter
    def on_result_callback(self):
        del self._inter_comm.on_result_callback

    @property
    def on_vision_callback(self):
        return self._inter_comm.on_vision_callback

    @on_vision_callback.setter
    def on_vision_callback(self, on_vision_callback):
        self._inter_comm.on_vision_callback = on_vision_callback

    @on_vision_callback.deleter
    def on_vision_callback(self):
        del self._inter_comm.on_vision_callback

    def release(self):
        logger.info('PyZenboSDK prepare release, cancel all command')
        self._inter_comm.release()
        logger.info('PyZenboSDK released')

    def cancel_command(self, command, sync=True, timeout=None):
        des = DESTINATION["coordinator"]
        cmd = commands.CANCEL
        data = {
            'command': int(command),
            'target_id': 0,
        }
        serial, error = self._inter_comm.send_command(des, cmd, data, sync, timeout)
        return serial, error

    def cancel_command_by_serial(self, serial, sync=True, timeout=None):
        des = DESTINATION["coordinator"]
        cmd = commands.CANCEL
        data = {
            'command': 0,
            'target_id': int(serial),
        }
        serial, error = self._inter_comm.send_command(des, cmd, data, sync, timeout)
        return serial, error

    def cancel_command_all(self, sync=True, timeout=None):
        des = DESTINATION["coordinator"]
        cmd = commands.CANCEL
        data = {
            'command': 0,
            'target_id': 0,
        }
        serial, error = self._inter_comm.send_command(des, cmd, data, sync, timeout)
        return serial, error

    def get_connection_state(self):
        return self._inter_comm.skt.stateSend, \
            self._inter_comm.skt.stateReceive


def main():
    pass

if __name__ == '__main__':
    main()