def print_header(title):
    print('\n\n*****************************')
    print(title)
    print('*****************************\n\n')

def calculate_speedup(tpar, tseq):
    return tpar/tseq


noop = []
o1op = []
o3op = []

noopMag = []
o1opMag = []
o3opMag = []


selected = noop
selectedMag = noopMag
with open('data.txt', 'r') as file:
    for line in file:
        if "O1" in line:
            selected = o1op
            selectedMag = o1opMag
        elif "O3" in line:
            selected = o3op
            selectedMag = o3opMag
       
        if line.startswith("- all"):
            selected.append(float(line.split(' ')[7]))
        elif line.startswith("- mag"):
            selectedMag.append(float(line.split(' ')[6]))
            

N = ['100', '200', '300', '400', '500', '600', '700', '800', '900', '1000'];

print_header("Allocation")
print("n, No optimizations, O1, O3")
for i,n in enumerate(N):
    print(f"{n}, {noop[i]}, {o1op[i]}, {o3op[i]}");
    
 
print_header("Allocation Speedup")
print("n, O1 Speedup, O3 Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(noop[i], o1op[i])}, {calculate_speedup(noop[i], o3op[i])}");
    
 
 
    
print_header("Magnitude")
print("n, No optimizations, O1, O3")
for i,n in enumerate(N):
    print(f"{n}, {noopMag[i]}, {o1opMag[i]}, {o3opMag[i]}");
    
   
print_header("Magnitude Speedup")
print("n, O1 Speedup, O3 Speedup")
for i,n in enumerate(N):
    print(f"{n}, {calculate_speedup(noopMag[i], o1opMag[i])}, {calculate_speedup(noopMag[i], o3opMag[i])}");
