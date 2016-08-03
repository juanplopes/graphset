#!/usr/bin/env python3
import json, subprocess, sys

def to_svg(G):
    content = ['graph{bgcolor="transparent";']
    for i, x in enumerate(G):
        content.append('{}[label="",shape=point];'.format(i));
        for j in range(i+1, len(G)):
            if x&(1<<j):
                content.append('{}--{};'.format(i, j))
    content.append('}')
    return subprocess.check_output(['neato', '-Tsvg'], input=bytes(''.join(content), 'utf-8'))

def normalize(graph):
    graph['n'] = len(graph['G'])
    graph['b'] = max(x.bit_length() for x in graph['S'])


data = []
with open(sys.argv[1]) as f:
    for i, line in enumerate(f):
        print('Graph #{}'.format(i))

        s = line[line.find('{'):line.rfind('}')+1];
        graph = json.loads(s)
       
        normalize(graph)
        with open('html/thumbs/{}.svg'.format(i), 'wb') as g:
            g.write(to_svg(graph['G']))
            
        data.append(graph)
with open('html/data.js', 'w') as g:
    g.write('var data = {};'.format(json.dumps(data)))

