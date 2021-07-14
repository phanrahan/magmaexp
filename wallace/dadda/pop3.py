def col2to2(bits):
    n = len(bits)
    m = n / 2
    if m != 0:
        print m, 'csa2to2'
        return m * [1], (n-m) * [1]
    else:
        return [], bits

def col3to2(bits):
    n = len(bits)
    m = n / 3
    if m != 0:
        print m, 'csa3to2'
        return m * [1], (n-2*m) * [1]

    return col2to2(bits)

def reduce3to2(bits):
    res = []
    lasttwos = []
    for b in bits:
        twos, ones = col3to2(b)
        res.append(lasttwos + ones)
        lasttwos = twos
    if len(lasttwos) > 0:
        res.append(lasttwos)
    return res

# returns True if there is 1 bit in each place
def ripple(bits):
    for b in bits:
         if len(b) >= 2:
             return False
    return True

N = 8
r = [N*[1]]
print r
while not ripple(r):
    r = reduce3to2(r)
    print r
