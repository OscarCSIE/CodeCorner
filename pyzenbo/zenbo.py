from pyzenbo.modules.line_follower import LineFollower
from pyzenbo.modules.line_follower import LineFollowerConfig
from pyzenbo.modules.motion import Motion
from pyzenbo.modules.sensor import Sensor


def main():
    config = LineFollowerConfig()

    # Add a rule to the configuration
    #only if 'SPEED_LEVEL'(needs a speed var ) or 'ROTATION'(needs a rotation angle var)
    color = LineFollowerConfig.COLOR['BLUE']
    behavior = LineFollowerConfig.BEHAVIOR['CROSSROAD_LEFT']
    speed_level = LineFollowerConfig.SPEED['L2']
    
    config.add_rule(color, behavior)

    # Get the rule for a specific color
    rule = config.get_rule(color)
    print(rule)  # Output: {2: 2}

    # Remove the rule for a specific color
    config.remove_rule(color)

    # Get the updated rule list
    rule_list = config.get_rule_list()
    print(rule_list)  # Output: {}

    # Build the configuration as a JSON string
    config_json = config.build()
    print(config_json)  # Output: "{}"


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
    config.add_rule([color_blue, color_white], [behavior_blue, behavior_white], ['', speed_level_white])
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

if __name__ == '__main__':
    main()