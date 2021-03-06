# compress column down to m bits
def daddacolumn3(bits, m):
    ones = []
    twos = []
    for i in range(0, n, 3):
        if i + 3 < n:
            c = compress3to2()
            c(bits[i], bits[i+1], bits[i+2])
            ones.append(c.O[0])
            twos.append(c.O[1])
        else:
            break
    while i < n:
        ones.append(bits[i])
        i += 1
    return ones, twos

# compress columns to less than or equal to n bits
def dadda3(bits, n):
    res = []
    lasttwos = []
    for b in bits:
        twos, ones = daddacolumn3(b, n)
        res.append(ones + lasttwos)
        lasttwos = twos
    if len(lasttwos) > 0:
        res.append(lasttwos)

# dadda scheme
def dadda(partials):
    pass
