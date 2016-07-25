#!/usr/bin/env python3
import json, subprocess

def to_svg(G):
    content = ['graph{bgcolor="transparent";']
    for i, x in enumerate(G):
        content.append('{}[label="",shape=point];'.format(i));
        for j in range(i+1, len(G)):
            if x&(1<<j):
                content.append('{}--{};'.format(i, j))
    content.append('}')
    print(''.join(content))
    return subprocess.check_output(['neato', '-Tsvg'], input=bytes(''.join(content), 'utf-8'))

with open('data.js') as f:
    s = f.read();
    s = s[s.find('['):s.rfind(';')];
    s = json.loads(s)

    for i, graph in enumerate(s):
        with open('thumbs/{}.svg'.format(i), 'wb') as g:
            g.write(to_svg(graph['G']))
