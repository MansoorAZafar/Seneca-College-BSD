from pathlib import Path
from enum import Enum
import csv

class NValue(Enum):
    ONE  = 10000000
    TWO  = 20000000
    FOUR = 40000000

data = { NValue.ONE: [], NValue.TWO: [], NValue.FOUR: [] }
def parse_file(file, alloc_name, nthreads, filter = None):
    data = []
    with open(file, "r") as f:
        for line in f:
            if any(sub in line for sub in [alloc_name, "Conversion"]) and (filter is None or filter(line)):
                data.append(float(line.split(" ")[-2]))
    
    # From 0-n every even step is initialization and every odd step is conversion
    # return avg of values
    return { "init": sum(data[::2]) / 5, "conv": sum(data[1::2]) / 5, "n": nthreads }


current_dir = Path(".")
avg_seq = None

SEQ_ALLOC_NAME = "Initialization"
PAR_ALLOC_NAME = "Allocation"

n_range = []
for path in current_dir.iterdir():
    if not path.is_file() or path.name == "parse.py": continue
    
    KEY = NValue(int(path.name.split("_")[-1].removesuffix(".txt")))
    if path.name.startswith("seq"):
        data[KEY].append(parse_file(path, SEQ_ALLOC_NAME, 1))
    else:
        nthreads = int(path.name.split("_")[1])
        data[KEY].append(parse_file(path, PAR_ALLOC_NAME, nthreads, lambda x: x.split(" ")[1] == "0:"))


n_values = sorted( {record["n"] for records in data.values() for record in records} )

def generate_init_csv():
    lookup = {
        enum.name: {r["n"]: r["init"] for r in records}
        for enum, records in data.items()
    }

    with open("init.csv", "w", newline="") as f:
        writer = csv.writer(f)

        headers = ["n"] + [enum.name for enum in data.keys()]
        writer.writerow(headers)

        for n in n_values:
            writer.writerow(
                [n] + [lookup[enum.name].get(n, "") for enum in data.keys()]
            )


def generate_conv_csv():
    lookup = {
        enum.name: {r["n"]: r["conv"] for r in records}
        for enum, records in data.items()
    }

    with open("conv.csv", "w", newline="") as f:
        writer = csv.writer(f)

        headers = ["n"] + [enum.name for enum in data.keys()]
        writer.writerow(headers)

        for n in n_values:
            writer.writerow(
                [n] + [lookup[enum.name].get(n, "") for enum in data.keys()]
            )

generate_init_csv()
generate_conv_csv()