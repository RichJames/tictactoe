#include <iostream>
#include <bitset>
#include <vector>

void test1()
{
  const int max = 8;

  std::bitset<max> b;
  while (std::cin >> b)
  {
    std::cout << b << std::endl;
    for (int i = 0; i < max; ++i)
      std::cout << b[i];
    std::cout << std::endl;
  }
}

void test2()
{
  int i;
  while (std::cin >> i)
    std::cout << std::dec << i << "=="
              << std::hex << "0x" << i << "=="
              << std::bitset<8 * sizeof(int)>(i) << std::endl;
}

void test3()
{
  const int max = 10;
  std::vector<int> v(max, 77);

  for (auto item : v)
    std::cout << item << std::endl;
}

void test4()
{
  enum BIT_VECTOR
  {
    bit7 = 1 << 7, // 128
    bit6 = 1 << 6, // 64
    bit5 = 1 << 5, // 32
    bit4 = 1 << 4, // 16
    bit3 = 1 << 3, // 8
    bit2 = 1 << 2, // 4
    bit1 = 1 << 1, // 2
    bit0 = 1       // 1
  };

  unsigned char val = bit4 | bit2; // val = 16 + 4 = 20
  val |= bit1;                     // val = 16 + 4 + 2 = 22
  if (!(val & bit0))
    std::cout << "bit0 of " << (int)val << " is NOT set! (" << std::bitset<8 * sizeof(int)>(val) << ")" << std::endl;

  unsigned char new_val = val & (bit3 | bit4);  // new_val = 16
  BIT_VECTOR another = BIT_VECTOR(bit3 | bit1); // 8 + 2 = 10

  std::cout << "new_val = " << (int)new_val << std::endl;
  std::cout << "another = " << another << std::endl;
}

int main(int argc, char const *argv[])
{
  // test1();
  test2();
  // test3();
  // test4();

  return 0;
}
