from functools import lru_cache
from magma import *

@lru_cache(maxsize=32)
def DefineAnd(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    And = DeclareCircuit('ir_and', *args)
    def _And():
        return And(N=N)
    return _And

def And(N):
    return DefineAnd(N)()

def DefineNAnd(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    NAnd = DeclareCircuit('ir_nand', *args)
    def _NAnd():
        return NAnd(N=N)
    return _NAnd

def DefineOr(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    Or = DeclareCircuit('ir_or', *args)
    def _Or():
        return Or(N=N)
    return _Or

def DefineNOr(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    NOr = DeclareCircuit('ir_nor', *args)
    def _NOr():
        return NOr(N=N)
    return _NOr

def DefineXOr(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    XOr = DeclareCircuit('ir_xor', *args)
    def _XOr():
        return XOr(N=N)
    return _XOr

def DefineNXOr(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", In(ArrayN), "C", Out(ArrayN)]
    NXOr = DeclareCircuit('ir_nxor', *args)
    def _NXOr():
        return NXOr(N=N)
    return _NXOr




@lru_cache(maxsize=32)
def DefineReduceAnd(N):
    ArrayN = Array(N, Bit)
    args = ["A", In(ArrayN), "B", Out(Bit)]
    ReduceAnd = DeclareCircuit('ir_reduce_and', *args)
    def _ReduceAnd():
        return ReduceAnd(N=N)
    return _ReduceAnd

def ReduceAnd(N):
    return DefineReduceAnd(N)()

