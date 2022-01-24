def x(i,j):
    global ted
    global s
    global ss
    global size

    if ss==s[i:j]:
        ted+=1
        if(j+size<=len(s)):
            x(j,j+size)
ted=0;
ma=0
s=input()
ss=input()
size=len(ss)
for i in range(len(s)-size):
    ted=0
    x(i , i+size)
    ma=max(ted,ma)

print(ma)