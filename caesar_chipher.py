#!/usr/bin/env python
""" Caesar Cipher sample. 
"""


class CaesarCipher(object):
    def __init__(self, key):
        self.key = key

    def encrypt(self, t):
        return ''.join(map(lambda x: chr(ord(x) + self.key), t))

    def decrypt(self, t):
        return ''.join(map(lambda x: chr(ord(x) - self.key), t))


if __name__ == '__main__':
    caesar = CaesarCipher(5)
    p = 'CRYPTO'
    e = caesar.encrypt(p)
    print(e)

    p = caesar.decrypt(e)
    print(p)
