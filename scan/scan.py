import magma as m
from mantle import ReduceOr

def Or4():
    return ReduceOr(4)

def wiren(circuit, n):
    ninput = len(circuit.I)
    if n == ninput:
       return circuit

    m.wire(m.repeat(0,ninput-n), circuit.I[n:])
    return m.AnonymousCircuit("I", circuit.I[0:n], "O", circuit.O)

def scan(n, k, op):
    ops = None
    while n > 4:
        nextops = wiren( m.flat(m.join(m.map_(op, (n+k-1)//k))), n )
        ops = m.compose(nextops, ops) if ops else nextops
        n = len(ops.O)
    if n > 1:
        nextops = wiren( op(), n )
        ops = m.compose(nextops, ops) if ops else nextops
        ops.O = m.bits(ops.O)
        n = len(ops.O)
    assert n == 1
    return ops
        
N = 11

main = m.DefineCircuit("main", "I", m.In(m.Bits(N)), "O", m.Out(m.Bit))
ors = scan(N, 4, Or4)
m.wire(main.I, ors.I)
m.wire(ors.O[0], main.O)
m.EndCircuit()
