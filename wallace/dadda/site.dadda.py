def daddasequence(n):
    d = (n+1) * [0]
    d[0] = 2
    for j in range(1,n+1):
        d[j] = 3*d[j-1]/2
    return d

d = daddasequence(5)

print d




