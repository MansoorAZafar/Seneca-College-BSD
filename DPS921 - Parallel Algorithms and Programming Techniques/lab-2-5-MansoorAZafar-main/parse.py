import subprocess
import sys

exe = "./q1_parallel.exe"
seq_exe = "./q1_seq.exe"
cuda_exe = "./q2parallel.exe"
cuda_par = "./q2_seq.exe"

nums = [10000000, 20000000, 40000000]
cnums = [100, 200, 400]
threads = [4,8,16,32]

script_name = sys.argv[1] 
strs = ""
if script_name == "s":
    for num in nums:
        strs = ""
        strs += f"\n\n**************  RUNNING WITH n = {num}  **************\n\n"
        for i in range(5):
            res = subprocess.run([seq_exe, str(num)], text=True, capture_output=True)
            strs += res.stdout + "\n\n";
        
        with open(f"data/seq_{num}.txt", "w") as file:
            file.write(strs)
elif script_name == "c":
    for num in cnums:
        strs = ""
        strs += f"\n\n************** Q2 CUDA RUNNING WITH n = {num}  **************\n\n"
        
        for i in range(5):
            res = subprocess.run([cuda_exe, str(num)], text=True, capture_output=True)
            strs += res.stdout + "\n\n";
        
        with open(f"data/cuda_{num}.txt", "w") as file:
            file.write(strs)
elif script_name == "cs":
    for num in cnums:
        strs = ""
        strs += f"\n\n************** Q2 Sequential RUNNING WITH n = {num}  **************\n\n"
        
        for i in range(5):
            res = subprocess.run([cuda_par, str(num)], text=True, capture_output=True)
            strs += res.stdout + "\n\n";
        
        print(strs)
        with open(f"data/q2_seq_{num}.txt", "w") as file:
            file.write(strs)
else:
    for num in nums:
        for thread in threads:
            strs = ""
            strs += f"\n\n**************  RUNNING N = {thread} THREADS WITH n = {num}  **************\n\n"
            
            for i in range(5):
                res = subprocess.run(["mpiexec.exe", "-np", str(thread), exe, str(num)], text=True, capture_output=True)
                strs += res.stdout + "\n\n"
        
            with open(f"data/par_{thread}_{num}.txt", "w") as file:
                file.write(strs)
