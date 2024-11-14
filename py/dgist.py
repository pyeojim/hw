#2164

a=int(input())
b=[]
c=0
while 1:
    if 2**c<=500000:
        b.append(2**c)
    else:
        break
    c+=1
for x in range(len(b)):
    if b[x]>a:
        print(b[x-1])
        break
    else:
        pass
