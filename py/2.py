#7576
from collections import deque
import sys
inp=sys.stdin.readline
a,b=map(int,inp().split())
c=[]

def tomato(x,c,y1):
    m=len(c)
    for _ in range(len(y1)):
        u=y1.pop()
        g1=[u-1,u+1]
        g2=[u-x,u+x]
        for a1 in g1:
            if a1//x==u//x and c[a1]!=-1:
                c[a1]=1
                y1.appendleft(a1)
            else:
                pass
        for a2 in g2:
            if a2>=0 and a2<m and c[a2]!=-1:
                y1.appendleft(a2)
                c[a2]=1
            else:
                pass
    return c,y1

for _ in range(b):
    c+=list(map(int,inp().split()))

f1=c.index(1)
count=0
y1=deque()
y1.append(f1)

while 1:
    c1,y1=tomato(a,c,y1)
    if c1==c:
        if c1.count(0):
            print(-1)
        else:    
            print(count)
        break
    else:
        print(c1)
        c=c1[:]
        count+=1
