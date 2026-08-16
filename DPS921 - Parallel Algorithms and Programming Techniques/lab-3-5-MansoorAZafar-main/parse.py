import subprocess
import sys
from pathlib import Path

tasks = [
    ("pi_serial.cpp", "pi_serial"), 
    ("pi_naive.cpp", "pi_naive"),
    ("pi_padded.cpp", "pi_padded"),
    ("pi_synchronized.cpp", "pi_synchronized"),
]

output_dir = Path("./executables")
data_dir = Path("./data")

output_dir.mkdir(exist_ok=True)
data_dir.mkdir(exist_ok=True)

for cpp_file, base_name in tasks:
    for suffix in ["_nop.exe", "_op.exe"]:
        exe_name = f"{base_name}{suffix}"
        exe_path = output_dir / exe_name

        if not exe_path.exists():
            # Step 1: Compile if it doesn't exist
            cmd = ["g++", cpp_file, "-o", str(exe_path)]

            if "pi_serial" not in base_name:
                cmd.append("-fopenmp")
            
            if suffix == "_op.exe":
                cmd.append("-O3")
            else:
                cmd.append("-O0")
            
            subprocess.run(cmd, check=True)
            print(f"Created: {exe_path}")

        # Step 2: Running Tests
        # subprocess.run([str(exe_path)])
        INPUT_SIZE = 1000000000
        threads = [1, 2, 4, 8, 16, 32, 64]

        _type = "-O0" if suffix.split('.')[0] == "_nop" else "-O3"
        file_name = ""
        if "pi_serial" not in base_name:
            # Run with threads
            for thread in threads:
                file_name = f"data/{base_name}{suffix.split('.')[0]}-Threads_{thread}.txt"
                print(f"Writing to: {file_name}")

                strs = f"\n\n************** {base_name} {_type}   Threads={thread} **************\n\n"
                for i in range(10):
                    res = subprocess.run([str(exe_path), str(INPUT_SIZE), str(thread)], text=True, capture_output=True)
                    strs += res.stdout + "\n\n";

                with open(file_name, "w") as file:
                    file.write(strs)
                
                print(f"Wrote to: {file_name}\n")
        else:
            file_name = f"data/{base_name}{suffix.split('.')[0]}.txt"
            print(f"Writing to: {file_name}")

            strs = f"\n\n************** {base_name} {_type} **************\n\n"
            for i in range(10):
                res = subprocess.run([str(exe_path), str(INPUT_SIZE)], text=True, capture_output=True)
                strs += res.stdout + "\n\n";

            with open(file_name, "w") as file:
                file.write(strs)
            
            print(f"Wrote to: {file_name}\n")
        