//#1
#include <iostream>
#include <cstdlib> 
#include <set>
#include <array>
#include <algorithm>
#include <chrono>


using namespace std;
using namespace chrono;

int main()
{
    srand(20);

    int N = 52;

    array <int, 52> all_numbers;   

    for (int i = 0; i <= all_numbers.size(); i++)
    {
        all_numbers[i] = rand();
    }

    auto start = high_resolution_clock::now();
    
    set <int, greater<int>> cont1;

    for (int i = 0; i <= all_numbers.size(); i++)
        {
            cont1.insert(all_numbers[i]);
        }
    
    auto one = high_resolution_clock::now();

    array <int, 52> cont2;

    for (int i = 0; i <= all_numbers.size(); i++)
        {
            cont2[all_numbers[i]];
        }

    sort(cont2.begin(), cont2.end());

    auto two = high_resolution_clock::now();

    duration<double> time_array = duration_cast<duration<double>>(one - start);
    duration<double> time_set = duration_cast<duration<double>>(two - one);

    cout << "array" << endl;
    cout << time_array.count() << endl;
    cout << "set" << endl;
    cout << time_set.count() << endl;

    //set быстрее

    return 0;
}


//#2
#include <unordered_set>
#include <random>
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;

// from boost (functional/hash):
// see http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html
template <typename T>
inline void hash_combine (size_t& seed, const T& val)
{
    seed ^= hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

// auxiliary generic functions to create a hash value using a seed
template <typename T>
inline void hash_val (size_t& seed, const T& val)
{
    hash_combine(seed,val);
}
template <typename T, typename... Types>
inline void hash_val (size_t& seed,
                      const T& val, const Types&... args)
{
    hash_combine(seed,val);
    hash_val(seed,args...);
}

// auxiliary generic function to create a hash value out of a heterogeneous list of arguments
template <typename... Types>
inline size_t hash_val (const Types&... args)
{
    size_t seed = 0;
    hash_val (seed, args...);
    return seed;
}

// PRINT_ELEMENTS()
// - prints optional string optstr followed by
// - all elements of the collection coll
// - in one line, separated by spaces
template <typename T>
inline void PRINT_ELEMENTS (const T& coll,
                            const string& optstr="")
{
    cout << optstr;
    for (const auto&  elem : coll) {
        cout << elem << ' ';
    }
    cout << endl;
}

using namespace std;

class Customer {
  private:
    string fname;
    string lname;
    long   no;
  public:
    Customer (const string& fn, const string& ln, long n)
      : fname(fn), lname(ln), no(n) {}
    friend ostream& operator << (ostream& strm, const Customer& c) {
        return strm << "[" << c.fname << "," << c.lname << ","
                           << c.no << "]";
    }
    friend class CustomerHash;
    friend class CustomerEqual;
};

class CustomerHash
{
  public:
    size_t operator() (const Customer& c) const {
        return hash_val(c.fname,c.lname,c.no);
    }
};

class CustomerEqual
{
  public:
    bool operator() (const Customer& c1, const Customer& c2) const {
        return c1.no == c2.no;
    }
};

string random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    string str(length,0);
    generate_n( str.begin(), length, randchar );
    return str;
}

int main()
{
    default_random_engine gen;
    uniform_int_distribution<int> dist(3,10);
    uniform_int_distribution<int> distNum(100000,999999);
    CustomerHash chash;
    size_t hashNum;
    int lengthFname;
    int lengthLname;
    int number;
    string fname;
    string lname;
    int counter = 0;

    for (int i = 0; i <= 100000; i++)
    {
        lengthFname = dist(gen);
        lengthLname = dist(gen);
        number = distNum(gen);
        fname = random_string(lengthFname);
        lname = random_string(lengthLname);

        
        unordered_set <int> cont;
    
        Customer customer(fname, lname, number); 
        cout << customer << endl;
        hashNum = chash(customer);
        cout << hashNum << endl;
        if (cont.find(hashNum) == cont.end())
        {
            cont.insert(hashNum);
        }
        else
        {
            counter += 1;
        }
    }
    
    cout << counter << endl;
     
    return 0;
}


//#3
#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>

using namespace std;

unsigned int RSHash(const char* str, unsigned int length) 
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length) // 1
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}

void random_string(char *randomStr, size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    generate_n(randomStr, length, randchar);
}

int main()
{
    default_random_engine gen;
    uniform_int_distribution<int> dist(3,10);
    vector<unordered_set<int>> v(9); // вектор из 9 unordered_set
    // каждый из unordered_set для соответствующей хэш-функции
    array<int, 9> collisions; // массив из 9 элементов для подсчета коллизий
    collisions.fill(0); // заполнение массива нулями
    char *randomStr;
    int length;
    int N = 20000; // N можно выбрать любое
    for (int i = 0; i<N; i++)
    {
      length = dist(gen);
      randomStr = new char[length];
      random_string(randomStr, length);
      array <int, 9> hash = {RSHash(randomStr, length), JSHash(randomStr, length), PJWHash(randomStr, length),
                            ELFHash(randomStr, length), BKDRHash(randomStr, length), SDBMHash(randomStr, length), 
                            DJBHash(randomStr, length), DEKHash(randomStr, length), APHash(randomStr, length)};

      for (int i = 0; i < 9; i++)
      {
         if (v[i].find(hash[i]) == v[i].end())
         {
            v[i].insert(hash[i]);
         }
         else
         {
            collisions[i] += 1;
         }
      }
    
    }
   for (int i = 0; i < 9; i++)
   {
      cout << collisions[i] << endl;
   }   
  
   return 0;
}
