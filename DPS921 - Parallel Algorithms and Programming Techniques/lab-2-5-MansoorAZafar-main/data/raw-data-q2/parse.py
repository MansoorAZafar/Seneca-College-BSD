from pathlib import Path
from enum import Enum
import csv

class NValue(Enum):
    ONE     = 100
    TWO     = 200
    FOUR    = 400
    EIGHT   = 800
    SIXTEEN = 1600

data = { key: [] for key in NValue }
def parse_file(file, name):
    data = []
    with open(file, "r") as f:
        for line in f:
            if any(sub in line for sub in ["allocation", "matrix-matrix"]):
                data.append(float(line.split(" ")[-2]))
    
    # From 0-n every even step is initialization and every odd step is conversion
    # return avg of values
    return { "alloc & init": sum(data[::2]) / 5, "matrix multi": sum(data[1::2]) / 5, "name": name }


current_dir = Path(".")
avg_seq = None

n_range = []
for path in current_dir.iterdir():
    if not path.is_file() or path.name == "parse.py": continue
    
    VAL = int(path.name.split("_")[-1].removesuffix(".txt"))
    KEY = NValue(VAL)
    if path.name.startswith("q2"):
        data[KEY].append(parse_file(path, f"s-{VAL}"))
    else:
        data[KEY].append(parse_file(path, f"c-{VAL}"))


print(data)





########################
matrix = {}
alloc = {}

for nvalue, records in data.items():
    n = nvalue.value

    matrix[n] = {}
    alloc[n] = {}

    for r in records:
        key = "c" if r["name"].startswith("c") else "s"

        matrix[n][f"{key}_matrix"] = r["matrix multi"]
        alloc[n][f"{key}_alloc"] = r["alloc & init"]

with open("matrix.csv", "w", newline="") as f:
    writer = csv.writer(f)

    writer.writerow(["NValue", "c_matrix", "s_matrix"])

    for n in sorted(matrix.keys()):
        writer.writerow([
            n,
            matrix[n].get("c_matrix", ""),
            matrix[n].get("s_matrix", "")
        ])

with open("alloc.csv", "w", newline="") as f:
    writer = csv.writer(f)

    writer.writerow(["NValue", "c_alloc", "s_alloc"])

    for n in sorted(alloc.keys()):
        writer.writerow([
            n,
            alloc[n].get("c_alloc", ""),
            alloc[n].get("s_alloc", "")
        ])