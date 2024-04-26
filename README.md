# Macrograd

### How to run:

```
cmake -S . -B build
cmake --build build
cd build
./macrograd
```

### Running valgrind to check memory leaks:


```
cd build/tests/
valgrind --leak-check=full ./BuildingBlocks_test 2>../../valgrind-logs/BuildingBlocksHeap.txt
```