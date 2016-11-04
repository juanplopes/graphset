#0 1 0 2 0 3 1 2 1 3 2 3 4 0 4 1 4 2 4 3 5 0 5 1 5 2 5 3 6 1 6 3 7 0 7 1 7 4
import subprocess, os, shutil, sys, networkx
from collections import defaultdict
from tempfile import mkdtemp

def is_chordal(G):
    return networkx.chordal.is_chordal(networkx.Graph(G))

def name1(i):
    return chr(ord('A')+i)

def name2(x, n):
    return ''.join(name1(i) for i in xrange(n) if x&(1<<i))

def print_model(fp, L, U, n, G):
    for x in range(1, 2**n):
        fp.write('var c{}, integer, >=0;\n'.format(name2(x, n)))

    for i in range(n):
        for j in range(i+1, n):
            a, b = U if G[i][j] else L
            mult = -1 if G[i][j] else 1
            
            line = []
            for x in range(2**n):
                coeff = 0
                if x&(1<<i) and x&(1<<j): coeff += mult * b
                if x&(1<<i) or x&(1<<j): coeff -= mult * a
                line.append(coeff)
            expr = ' + '.join('{}*c{}'.format(x, name2(i, n)) for i,x in enumerate(line) if x)
            fp.write("s.t. s{}{}: {} <= 0;\n".format(name1(i), name1(j), expr))

    for i in range(n):
        expr = ' + '.join('c{}'.format(name2(x, n)) for x in range(2**n) if x&(1<<i))
        fp.write("s.t. m{}: {} >= 1;\n".format(name1(i), expr))

    fp.write("minimize z: {};\n".format(' + '.join('c' + name2(x, n) for x in range(1, 2**n))))

    fp.write('solve;\n');
    fp.write('end;\n');

def print_sets(n, values):
    sets = [[] for i in range(n)]

    values = list(values)
    for i in range(1, len(values)):
        values[i] += values[i-1]
        
        for j in range(n):
            if i&(1<<j):
                sets[j].extend(range(values[i-1], values[i]))
                
    for i in range(n):
        print i, sets[i]
        

tempd = mkdtemp()
try:
    inname = os.path.join(tempd, 'input')
    outname  = os.path.join(tempd, 'output')
    with open(inname, 'wb') as fp:
        EE = map(int, sys.argv[1:])
        E = zip(EE[::2], EE[1::2])

        N = max(map(max, E))+1
        G = defaultdict(lambda: defaultdict(lambda: False))
        for a, b in E:
            G[a][b] = G[b][a] = True

        if not is_chordal(G):
            sys.stdout.write("MEH ")
            sys.exit(0)

        print_model(fp, (1,3), (1,2), N, G)
        fp.flush()
        #, stdout=open(os.devnull, 'w')
        subprocess.call(['glpsol', '--model', inname, '--write', outname], stderr=subprocess.STDOUT)
    with open(outname, 'rb') as fp:
        rows, variables = map(int, fp.readline().strip().split(' '))
        #print rows, variables
        A, B = map(int, fp.readline().strip().split(' '))
        #print A, B

        values = [0] + [int(x.strip()) for x in fp.readlines()[-variables:]]
        #print_sets(N, )
        if B==0 or sum(values) == 0: print "ERROR", EE
        else: sys.stdout.write("OK"+str(B)+" ")

finally:
    shutil.rmtree(tempd)
