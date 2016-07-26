# graphset


## To generate data:
```
truncate data.json --size 0
showg -eq graphs/graph2c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph3c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph4c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph5c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph6c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph7c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
showg -eq graphs/graph8c.g6 | (g++ -O3 tools/datagen.cpp && time ./a.out) >> data.json
```

## To export data for display:
```
./normalize.py
```
