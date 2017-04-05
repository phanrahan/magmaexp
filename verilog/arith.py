from magma import *

def DefineAdd(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    Add = DeclareCircuit('ir_trunc_add', *args)
    def _Add():
        return Add(N=N)
    return _Add

def DefineAdc(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "CIN", In(Bit), 
            "C", Out(ArrayN), "COUT", Out(Bit)]
    Adc = DeclareCircuit('ir_adc', *args)
    def _Adc():
        return Adc(N=N)
    return _Adc

def DefineSub(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    Sub = DeclareCircuit('ir_trunc_sub', *args)
    def _Sub():
        return Sub(N=N)
    return _Sub

def DefineSbc(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "CIN", In(Bit), 
            "C", Out(ArrayN), "COUT", Out(Bit)]
    Sbc = DeclareCircuit('ir_sbc', *args)
    def _Sbc():
        return Sbc(N=N)
    return _Sbc
