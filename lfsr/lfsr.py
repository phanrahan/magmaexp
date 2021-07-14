import os
import csv

_lfsrtaps = {}

def readtaps():
    global _lfsrtaps

    if len(_lfsrtaps) != 0:
        return

    name = os.path.join(os.path.dirname(__file__), 'lfsr.csv')

    f = open(name)
    row = csv.reader(f)

    for data in row:
        if data[0].isdigit():
            tap = int(data[0])
            _lfsrtaps[tap] = [int(v) for v in data[1].split(',')]


# 
# Galois LFSR
#
def lfsr(n):
    poly = 0
    for tap in _lfsrtaps[n]:
        poly |= 1 << (tap-1)

    state = 1
    while True:
        yield state
        lsb = state & 1
        state >>= 1
        if lsb:
            state ^= poly

readtaps()

l = lfsr(4)
for i in range(16):
    print(hex(next(l)))
