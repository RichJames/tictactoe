#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//----------------------------------------------------------------------------
template <typename T>
struct input_t
{
  // mutable T &n;
  T &n;
  explicit input_t(T &n) : n(n) {}
  input_t(const input_t<T> &i) : n(i.n) {}
};

//----------------------------------------------------------------------------
template <typename T>
inline input_t<T>
input(T &n)
{
  input_t<T> result(n);
  return result;
}

//----------------------------------------------------------------------------
template <typename T>
istream &operator>>(istream &ins, const input_t<T> &i)
{
  // Read a line (terminated by ENTER|NEWLINE) from the user
  string s;
  getline(ins, s);

  // Get rid of any trailing whitespace
  s.erase(s.find_last_not_of(" \f\n\r\t\v") + 1);

  // Read it into the target type
  istringstream ss(s);
  ss >> i.n;

  // Check to see that there is nothing left over
  if (!ss.eof())
    ins.setstate(ios::failbit);

  return ins;
}

//----------------------------------------------------------------------------
int main()
{
  int n;

  cout << "Please enter an integer> " << flush;
  cin >> input(n);
  while (!cin)
  {
    cin.clear();
    cout << "Please, enter only an INTEGER> " << flush;
    cin >> input(n);
  }

  cout << "Good job!\n"
          "You entered the number "
       << n << endl;

  cout << "I"
          " didn't"
          " know "
          "I could do this\n";

  return 0;
}