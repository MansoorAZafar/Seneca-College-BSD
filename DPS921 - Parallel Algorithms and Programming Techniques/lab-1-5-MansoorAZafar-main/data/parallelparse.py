def print_header(title):
    print('\n\n*****************************')
    print(title)
    print('*****************************\n\n')

def calculate_speedup(tseq, tpar):
    if tpar <= 0:
        tpar = 0.001 # transform to the nanoseconds
    return tseq/tpar


thread0 = []
thread2 = []
thread4 = []
thread8 = []
thread16 = []

thread0Mag = []
thread2Mag = []
thread4Mag = []
thread8Mag = []
thread16Mag = []

selected = thread0
selectedMag = thread0Mag
with open('data.txt', 'r') as file:
    for line in file:
        if "Optimizations 2 Threads" in line:
            selected = thread2
            selectedMag = thread2Mag
        elif "Optimizations 4 Threads" in line:
            selected = thread4
            selectedMag = thread4Mag
        elif "Optimizations 8 Threads" in line:
            selected = thread8
            selectedMag = thread8Mag
        elif "Optimizations 16 Threads" in line:
            selected = thread16
            selectedMag = thread16Mag
       
        if line.startswith("- all"):
            selected.append(float(line.split(' ')[7]))
        elif line.startswith("- mag"):
            selectedMag.append(float(line.split(' ')[6]))
            

N = ['100', '200', '300', '400', '500', '600', '700', '800', '900', '1000'];

print_header("Allocation")
print("n, 2 Threads, 4 Threads, 8 Threads, 16 Threads")
for i,n in enumerate(N):
    print(f"{n}, {thread2[i]}, {thread4[i]}, {thread8[i]}, {thread16[i]}");
    
 
print_header("Allocation Speedup")
print("n, 2 Speedup, 4 Speedup, 8 Speedup, 16 Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(thread0[i], thread2[i])}, {calculate_speedup(thread0[i], thread4[i])}, {calculate_speedup(thread0[i], thread8[i])}, {calculate_speedup(thread0[i], thread16[i])}");
    
 
 
    
print_header("Magnitude")
print("n, 2 Threads, 4 Threads, 8 Threads, 16 Threads")
for i,n in enumerate(N):
    print(f"{n}, {thread2Mag[i]}, {thread4Mag[i]}, {thread8Mag[i]}, {thread16Mag[i]}");
    
   
print_header("Magnitude Speedup")
print("n, 2 Speedup, 4 Speedup, 8 Speedup, 16 Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(thread0[i], thread2Mag[i])}, {calculate_speedup(thread0[i], thread4Mag[i])}, {calculate_speedup(thread0[i], thread8Mag[i])}, {calculate_speedup(thread0[i], thread16Mag[i])}");
