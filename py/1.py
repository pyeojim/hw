#14940

import sys
import copy
input=sys.stdin.readline
a,b=map(int,input().split())
c=[]
c1=[[0]*(b+2) for _ in range(a+2)]
for i in range(a):
    u=list(map(int,input().split()))
    if u.count(2):
        d=[i,u.index(2)]
    c.append(u)
c1[d[0]+1][d[1]+1]=1
c[d[0]][d[1]]=0
c23=copy.deepcopy(c)
c23[d[0]][d[1]]=1

while 1:
    c2=copy.deepcopy(c1)
    for y in range(1,a+1):
        for x in range(1,b+1):
            ong=max([c1[y-1][x],c1[y][x-1],c1[y+1][x],c1[y][x+1]])
            if c[y-1][x-1] and ong:
                c2[y][x]=ong+1
                c[y-1][x-1]=0
            else:
                pass
    if c2==c1:
        break
    else:
        c1=c2[:]

c3=c1[1:-1]
for o1, o2 in zip(c3,c23):
    o3=o1[1:-1]
    omg=[]
    for x, y in zip(o3, o2):
        omg.append(x-y)
    print(str(omg).strip('[]').replace(',',''))