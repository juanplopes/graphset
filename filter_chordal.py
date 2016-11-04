import networkx

def is_chordal(G):
    return networkx.chordal.is_chordal(networkx.Graph(G))


try:
    while True:
        first = raw_input()
        second = raw_input()
        G = [int(x) for x in second.strip().split(' ') if x != '']
        G = zip(G[::2], G[1::2])
        
        if is_chordal(G):
            print first
            print second
except EOFError:
    pass
