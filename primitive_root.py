#!/usr/bin/env python


def is_primitive_root(a, p):
    # Is "a" primitive root of "p" ? 
    s = set()
    for i in range(p):
        q, r = divmod(a ** i, p)
        s.add(r)
        if len(s) == p - 1:
            return True
    return False
