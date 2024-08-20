import os
import json
from pathlib import Path
import subprocess

HOME = Path.home()
CONFIG_PATH = HOME / Path(".config/webspeeddial/config.json")

# Loads config
data = {"runner": "fzf", "bookmarks": []}
if not os.path.exists(CONFIG_PATH):
    os.system("mkdir -p " + str(HOME / Path(".config/webspeeddial")))
    with open(CONFIG_PATH, "w") as f:
        json.dump(data, f)
else:
    with open(CONFIG_PATH, "r") as f:
        data = json.load(f)

# Get all bookmarks
names = []
for i in data["bookmarks"]:
    names.append(i["name"])

names_str = "\n".join(names)
runner = data["runner"]

# Selection
command = f'echo $"{names_str}" | {runner}'
out = subprocess.check_output(["bash", "-c", command])
out = out.decode("UTF-8").replace("\n", "").strip()

# Find bookmark
for i in data["bookmarks"]:
    if i["name"] == out:
        addr = i["address"]
        os.system(f"xdg-open {addr}")
        exit(0)
print(f"Couldn't find selected bookmark: '{out}'")
exit(1)
