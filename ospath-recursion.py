import os

def endless():
    i = 0
    while True:
        yield i
        i += 1

for i in endless():
    code = "os.path. " * i
    code += "os.path"
    print "Round %s" % i
    eval(code)
