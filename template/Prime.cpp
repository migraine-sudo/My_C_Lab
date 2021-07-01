#include <cstdio> 

template <size_t, size_t, bool> 
struct Check;

template <size_t i, size_t p> 
struct Check<i, p, true> 
{
  enum { value = Check<i, p - 1, i % p != 0>::value };
}; 

template <size_t i, size_t p> 
struct Check<i, p, false> 
{ 
  enum { value = false }; 
}; 

template <size_t i>
struct Check<i, 1, true> 
{ 
  enum { value = true }; 
}; 

template<size_t i, bool b> 
//struct Prime 
//{ 
// enum { is_prime = Check<i, i - 1, true>::value }; 
//}
;

template<size_t i> 
struct Prime<i, false> 
{ 
  enum { is_prime = false };
}; 

template <size_t i> 
struct PrintPrime 
{ 
  enum 
  { count = PrintPrime<i - 1>::count +
    (Prime<i, Check<i, i - 1, true>::value>::is_prime ? 1 : 0)
  }; 
  PrintPrime() 
  {
    PrintPrime<i - 1>();
    if (Prime<i, Check<i, i - 1, true>::value>::is_prime)
    { 
      printf(" No.%d : %d\n", count, i);
    } 
  }
};

template <> 
struct PrintPrime<1>
{ 
  enum { count = 0 };
  PrintPrime() {} 
};

int main() 
{
  PrintPrime<0x1f3>(); // 499
}