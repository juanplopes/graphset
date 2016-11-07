import sys
for i in range(3):
    for j in range(i+1, 3):
        sys.stdout.write(" {} {}".format(i, j))
        
for i in range(1, 2**3):
    for j in range(3):
        if i&(1<<j):
            sys.stdout.write(" {} {}".format(2+i, j))

print
