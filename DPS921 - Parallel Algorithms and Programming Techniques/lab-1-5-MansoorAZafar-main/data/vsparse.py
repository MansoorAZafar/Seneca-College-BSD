def print_header(title):
    print('\n\n*****************************')
    print(title)
    print('*****************************\n\n')

def calculate_speedup(tpar, tseq):
    return tpar/tseq


noop = []
o2op = []
oxop = []

noopMag = []
o2opMag = []
oxopMag = []


selected = noop
selectedMag = noopMag
with open('data.txt', 'r') as file:
    for line in file:
        if "Ox" in line:
            selected = oxop
            selectedMag = oxopMag
        elif "O2" in line:
            selected = o2op
            selectedMag = o2opMag
       
        if line.startswith("- all"):
            selected.append(float(line.split(' ')[7]))
        elif line.startswith("- mag"):
            selectedMag.append(float(line.split(' ')[6]))
            

N = ['100', '200', '300', '400', '500', '600', '700', '800', '900', '1000'];

print_header("Allocation")
print("n, No optimizations, O2, Ox")
for i,n in enumerate(N):
    print(f"{n}, {noop[i]}, {o2op[i]}, {oxop[i]}");
    
 
print_header("Allocation Speedup")
print("n, O2 Speedup, Ox Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(noop[i], o2op[i])}, {calculate_speedup(noop[i], oxop[i])}");
    
 
 
    
print_header("Magnitude")
print("n, No optimizations, O2, Ox")
for i,n in enumerate(N):
    print(f"{n}, {noopMag[i]}, {o2opMag[i]}, {oxopMag[i]}");
    
   
print_header("Magnitude Speedup")
print("n, O2 Speedup, Ox Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(noopMag[i], o2opMag[i])}, {calculate_speedup(noopMag[i], oxopMag[i])}");
