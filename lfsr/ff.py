import inspect

def ff(init):
    value = init
    while True:
        value = yield value

l = ff(0)
print(l.gi_frame.f_locals)
print(next(l))
print(l.gi_frame.f_locals)
print(l.send(1))
print(l.gi_frame.f_locals)
print(l.send(0))
print(l.send(0))
