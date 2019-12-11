import json

def get_sum_of_json(info):
    if isinstance(info, dict):
        if "red" in info.values():
            return 0
        return sum(get_sum_of_json(x) for x in info.values())
    if isinstance(info, list):
        return sum(get_sum_of_json(x) for x in info)
    if isinstance(info, int):
        return info
    return 0

with open("input/input12.txt") as f:
    info = json.load(f)
    print(get_sum_of_json(info))
