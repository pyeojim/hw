#14502

a,b=map(int,input().split())
c=[]
e1=[]
for i in range(a):
    d=list(map(int,input().split())) 
    for j in range(b):
        if d[j]==2:
            e1.append([i*b+j])
        else:
            pass
    c+=d

while e1:
    print('\n')
    c2=[c[omg:omg+b] for omg in range(a)]
    c2=[str(io).strip('[]').replace(',','') for io in c2]
    c2=str(c2).strip("[]").replace(', ','\n')
    c2=c2.replace('\'','')
    print(c2)
    u=e1.pop()
    for w in u:
        cache=[]
        for x in [w-1,w+1]:
            if x>0 and x<a*b and (not c[x]):
                c[x]=2
                cache.append(x)
        for y in [w-b,w+b]:
            if y>0 and y<a*b and (not c[x]) and y//b==w//b:
                c[y]=2
                cache.append(x)
        e1.append(cache)

c2=[c[omg:omg+b] for omg in range(a)]
c2=[str(io).strip('[]').replace(',','') for io in c2]
c2=str(c2).strip("[]").replace(', ','\n')
c2=c2.replace('\'','')

print(c2)
