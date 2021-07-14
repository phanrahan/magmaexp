HalfCleaner
ReverseHalfCleaner
BitonicSorter
Merger
Sorter

Rewrite this in terms of higher-order functions.
Parameterize these functions with Circuits

Functional version that doesn't generate new Circuits.

Introduce bit permutation functions array(n,T) = permute(array(n,T))

cut a : array(n,T) -> array(n/2 Array(n,T))
flat a : array(m, array(n, T)) -> array(m*n, T)
reverse : array(n, T) -> array(n, T)
riffle : array(n, T) -> array(n, T)
unriffle : array(n, T) -> array(n, T)
permute a index : array(n, T) -> array(n, T) -- out[i] = in[index[i]]
  note that this can also be used to duplicate entries
evens a : array(n,T) -> array(n/2,T)
odds a : array(n,T) -> array(n/2,T)
zip a1 a2 : array(n,T) array(n,T) -> array(n,Array(2,T))

a.as_list()

These could also be higher order circuit functions


Ideas

col(f, n, delta=1)
row(f, n, delta=1)

rewrite braid.py flat to operate on a circuit instance

DefineCircuit(f, name, *args)
   f should be a pure function

ifthenelse(if, then, else)


