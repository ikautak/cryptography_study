// Block chiper ECB mode.
// byte permutation, block length = 4byte and key is (1, 3, 0, 2).

#include <iostream>

class ECB {
 public:
  ECB(int* key, const int block_len) : BLOCK_LEN(block_len) {
    mKey = new int[BLOCK_LEN];
    for (int i = 0; i < BLOCK_LEN; ++i) {
      mKey[i] = key[i];
    }
  }

  ~ECB() { delete[] mKey; }

  std::string Encrypt(std::string& t) {
    // padding last block.
    int remain = t.size() % BLOCK_LEN;
    for (int i = 0; i < BLOCK_LEN - remain; ++i) {
      t += ' ';
    }

    std::string e = t;
    int block_num = e.size() / BLOCK_LEN;
    for (int i = 0; i < block_num; ++i) {
      for (int c = 0; c < BLOCK_LEN; ++c) {
        e[mKey[c] + i * BLOCK_LEN] = t[c + i * BLOCK_LEN];
      }
    }

    return e;
  }

  std::string Decrypt(std::string& t) {
    std::string p = t;
    int block_num = p.size() / BLOCK_LEN;
    for (int i = 0; i < block_num; ++i) {
      for (int c = 0; c < BLOCK_LEN; ++c) {
        p[c + i * BLOCK_LEN] = t[mKey[c] + i * BLOCK_LEN];
      }
    }

    return p;
  }

 private:
  const int BLOCK_LEN;
  int* mKey;
};

int main(void) {
  int key[4] = {1, 3, 0, 2};
  ECB* ecb = new ECB(key, 4);

  std::string p = "Hello World! block chiper ECB mode.";
  std::cout << "p   : " << p << std::endl;

  std::string e = ecb->Encrypt(p);
  std::cout << "enc : " << e << std::endl;

  p = ecb->Decrypt(e);
  std::cout << "dec : " << p << std::endl;

  delete ecb;

  return 0;
}