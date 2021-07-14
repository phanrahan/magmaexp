from magma import cache_definition
from .t import In, Out
from .bit import Bit
from .array import Array
from .circuit import Circuit, wire

__all__  = ['DefineSplitter', 'Splitter']
__all__ += ['DefinePermute', 'Permute']
__all__ += ['Identity']


def DefinePermute(n, permutation, T=Bit, basename='Permute'):
    permutation = tuple(permutation)
    ni = n
    no = len(permutation)
    if basename == 'Permute':
        basename = '{}{}x{}_{:4X}'.format(basename,ni,no,hash(permutation)&0xffff)
    else:
        basename = '{}{}'.format(basename,ni)
    class _Permute(Circuit):
        name = basename
        IO = ["I", In(Array(ni,T)), "O", Out(Array(no,T))]
        @classmethod
        def definition(io):
            [wire(io.I[permutation[i]], io.O[i]) for i in range(len(io.I))]
    return _Permute

def Permute(name,permutation, T=Bit, basename='Permute', **kwargs):
    return DefinePermute(name,permutation, T, basename)(**kwargs)

def Identity(n, T=Bit, **kwargs):
    return DefinePermute(n, range(n), T, basename='Identity')(**kwargs)

@cache_definition
def DefineSplitter(n, T=Bit):
    class _Splitter(Circuit):
        name = 'Splitter{}'.format(n)
        IO = ["I", In(T), "O", Out(Array(n, T))]
        @classmethod
        def definition(io):
            [wire(io.I, io.O[i]) for i in range(len(io.O))]
    return _Splitter

def Splitter(n, T=Bit, **kwargs):
    return DefineSplitter(n, T)(**kwargs)
   


