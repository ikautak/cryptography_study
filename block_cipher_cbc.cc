// http://ikautak.hatenablog.com/entry/2013/05/14/224310

#include <iostream>

class CBC {
 public:
  CBC(int *key, const int block_len, const unsigned char iv)
      : BLOCK_LEN(block_len), IV(iv) {
    key_ = new int[BLOCK_LEN];

    for (int i = 0; i < BLOCK_LEN; ++i) {
      key_[i] = key[i];
    }
  }

  ~CBC() { delete[] key_; }

  std::string Encrypt(std::string &m) {
    std::string c = m;
    unsigned char v = IV;

    int block_num = c.size();
    for (int i = 0; i < block_num; ++i) {
      unsigned char c_i = 0x00;

      // permute from MSB.
      for (int b = 0; b < BLOCK_LEN; ++b) {
        unsigned char m_i = ((v ^ m[i]) >> key_[b]) & 0x01;
        c_i |= m_i << (BLOCK_LEN - b - 1);
      }

      c[i] = c_i;
      v = c_i;
    }

    return c;
  }

  std::string Decrypt(std::string &c) {
    std::string m = c;
    unsigned char v = IV;

    int block_num = m.size();
    for (int i = 0; i < block_num; ++i) {
      unsigned char m_i = 0x00;

      // permute from MSB.
      for (int b = 0; b < BLOCK_LEN; ++b) {
        unsigned char c_i = (c[i] >> (BLOCK_LEN - b - 1)) & 0x01;
        m_i |= c_i << key_[b];
      }

      m[i] = v ^ m_i;
      v = c[i];
    }

    return m;
  }

 private:
  const int BLOCK_LEN;
  const unsigned char IV;
  int *key_;
};

int main(void) {
  int key[8] = {6, 5, 4, 3, 2, 1, 0, 7};
  unsigned char IV = 0xAA;
  CBC *cbc = new CBC(key, 8, IV);

  std::string p = "Hello World! block cipher CBC mode.";
  std::cout << "p   : " << p << std::endl;

  std::string e = cbc->Encrypt(p);
  std::cout << "enc : " << e << std::endl;

  p = cbc->Decrypt(e);
  std::cout << "dec : " << p << std::endl;

  delete cbc;

  return 0;
}