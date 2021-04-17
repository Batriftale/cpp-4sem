#include <iostream>
#include <ctime>
#include <thread>
#include <random>
#include <algorithm>
#include <execution>
#include <vector>
#include <functional>

using namespace std;

int main()
{
    vector<int> vec = {1, 5, 3, 7, 9, 1};
    vector<int>::iterator it;
//#4
//sorting 
    auto start = chrono::high_resolution_clock::now();
    sort(execution::par, vec.begin(), vec.end());
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto rng = default_random_engine {};
    shuffle(begin(vec), end(vec), rng);

    auto start = chrono::high_resolution_clock::now();
    sort(execution::seq, vec.begin(), vec.end());
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto rng = default_random_engine {};
    shuffle(begin(vec), end(vec), rng);
//finding
    auto start = chrono::high_resolution_clock::now();
    it = find(execution::par, vec.begin(), vec.end(), 5);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto start = chrono::high_resolution_clock::now();
    it = find(execution::seq, vec.begin(), vec.end(), 5);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;

//counting
    auto start = chrono::high_resolution_clock::now();
    it = count(execution::par, vec.begin(), vec.end(), 1);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for parallel : " << chrono::duration<float>(end - start).count() << " s" << endl;

    auto start = chrono::high_resolution_clock::now();
    it = count(execution::seq, vec.begin(), vec.end(), 1);
    auto end   = chrono::high_resolution_clock::now();

    cout << "time taken for sequenced : " << chrono::duration<float>(end - start).count() << " s" << endl;
}
//#1
void Pi_search(int N, int Radius)
{
    int N_in = 0;

    random_device random_device; 
    mt19937 generator(random_device());

    uniform_int_distribution<> distribution(-Radius, Radius); 

    for (int i = 0; i < 2 * N; i++)
    {
        int x = distribution(generator);
        int y = distribution(generator);
        if ((x * x + y * y) <= Radius * Radius)
        {
            N_in++;
        }
    }
    cout << 4 * double(N_in) / double(N) << endl; 
}

int main(int argc, char ** argv)
{
    int N = 1000000;
    int n = thread::hardware_concurrency();
    int Radius = 1;

    vector<thread> threads;

    int each = N/n;

    for (size_t i = 0 ; i < n; i++)
    {
        threads.push_back(thread(Pi_search, each, Radius));

    }
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
}
