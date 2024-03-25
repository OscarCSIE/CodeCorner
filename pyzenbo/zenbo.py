from pyzenbo.modules.line_follower import LineFollower
from pyzenbo.modules.line_follower import LineFollowerConfig
import pyzenbo.modules.inter_communication as _inter_comm
import pyzenbo.modules.zenbo_command as commands
from pyzenbo.modules import error_code
from pyzenbo.modules.inter_communication import DESTINATION, InterComm
from pyzenbo.modules.motion import Motion
from pyzenbo.modules.sensor import Sensor

from pyzenbo.modules.socket_state_machine import SocketStateMachine



def main():
    config = LineFollowerConfig()

    color_blue = LineFollowerConfig.COLOR['BLUE']
    behavior_blue = LineFollowerConfig.BEHAVIOR['CROSSROAD_LEFT']
    
    color_white = LineFollowerConfig.COLOR['WHITE']
    behavior_white = LineFollowerConfig.BEHAVIOR['SPEED_LEVEL']
    speed_level_white = LineFollowerConfig.SPEED['L3']
    
    color_red = LineFollowerConfig.COLOR['RED']
    behavior_red = LineFollowerConfig.BEHAVIOR['SPEED_LEVEL']
    speed_level_red = LineFollowerConfig.SPEED['L2']
    
    color_black = LineFollowerConfig.COLOR['BLACK']
    behavior_black = LineFollowerConfig.BEHAVIOR['ROTATION']
    degree_black = 90
    
    config.add_rule(color_blue, behavior_blue)
    config.add_rule(color_white, behavior_white, speed_level_white)
    config.add_rule(color_red, behavior_red, speed_level_red)
    config.add_rule(color_black, behavior_black, degree_black)

    rule_blue = config.get_rule(color_blue)
    print(f"Rule_blue = {rule_blue}")
    rule_white = config.get_rule(color_white)
    print(f"Rule_white = {rule_white}")
    rule_red = config.get_rule(color_red)
    print(f"Rule_red = {rule_red}")
    rule_black = config.get_rule(color_black)
    print(f"Rule_black = {rule_black}")

    # config.remove_rule(color_black)

    rule_list = config.get_rule_list()
    print(f"Rule_list = {rule_list}")

    config_json = config.build()
    print(f"Config_json =  {config_json}")
    
    intercom = InterComm()
    linefollow = LineFollower(intercom)
    
    # linefollow.calibrate(reset = True, sync = False, timeout = None)
    
    # linefollow.demo(sync = False, timeout = None)
    
    # linefollow.get_color(sync = False, timeout = None)
    
    # linefollow.follow_line(json_string = config_json, sync = True, timeout = None)
    
    # linefollow.update_config(json_string = config_json, sync = False, timeout = None)
    
    # linefollow.set_behavior(1, behavior_black, arg = None, sync = True, timeout = None)
    '''arg is for speed level and rotation,first parameter is speed,second parameter is rotation, otherwise dont use it'''

if __name__ == '__main__':
    main()