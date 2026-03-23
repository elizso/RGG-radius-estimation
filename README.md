## RGG Radius Estimation 
This github repository contains an C++ implementation of estimating the radius $r_c$ in a random geometric graph (RGG).
Specifically, this is implemented for an assignment, COMP4600 A1 Q4. The python file [`graph.py`](graph.py) is used to generate graphs from the estimated $r_c$ stored [here](output/rc_estimate_results.csv). 

## Running the `.cpp`
### MacOS
Compile using 
```
clang++ rc_estimate.cpp -std=c++17 -O2 -Wall -Wextra -o rc_estimate
```
Then run 
```
./rc_estimate
```

### Windows 
Compile using 
```
g++ -std=c++17 -O2 -o rc_estimate.exe rc_estimate.cpp
```
Then run
```
rc_estimate.exe
```

### Linux 
Compile using 
```
g++ -std=c++17 -O3 -march=native -o rc_estimate rc_estimate.cpp
```
Then run
```
./rc_estimate
```
