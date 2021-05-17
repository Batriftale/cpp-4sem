#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <thread>
#include <mutex>
#include <future>
#include <algorithm>
#include <vector>
#include <random>
#include <queue>
#include <stdio.h>
#include <string>
#include <math.h>

using namespace std;

//#1
double Random(double min, double max)
{
    double ZeroOne = rand() / static_cast<double>(RAND_MAX);
    double Interval = ZeroOne * (max - min);
    double MinMax = Interval + min;
    return MinMax;
}

mutex mtx;

void Pi_search(double R, int n, double& m)
{
    n = n / 4;
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; i++)
    {
        double x = Random(-R, R);
        double y = Random(-R, R);
        if (pow(x, 2) + pow(y, 2) < pow(R, 2))
        {
            mtx.lock();
            m++;
            mtx.unlock();
        }
    }
}
int main()
{
    double R, m;
    int n;
    m = 0;
    cin >> R >> n;
    thread t1(Pi_search, R, n, ref(m));
    thread t2(Pi_search, R, n, ref(m));
    thread t3(Pi_search, R, n, ref(m));
    thread t4(Pi_search, R, n, ref(m));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    double pi = 4 * m / n;
    cout << pi << endl;
    return 0;
}
//#2
void generate(int len, string& s)
{
    for (int i = 0; i < len; i++)
    {
        int k = rand() % 4;
        if (k == 0) { s[i] = 'A'; }
        if (k == 1) { s[i] = 'G'; }
        if (k == 2) { s[i] = 'T'; }
        if (k == 3) { s[i] = 'C'; }
    }

}

void search(string s, string sfind, int len1, int len2, int beg, int end, vector<int>& iter)
{
    int j = 0;
    vector<int> iter_curr;
    for (int i = beg; i <= end; i++)
    {
        if (s[i] == sfind[j] && j != len2 - 1)
        {
            j += 1;
        }
        else if (s[i] == sfind[j] && j == len2 - 1)
        {
            iter_curr.push_back(i - len2 + 1);
            j = 0;
        }
        else
        {
            j = 0;
        }
    }
    mutex door;
    door.lock();
    iter.insert(iter.end(), iter_curr.begin(), iter_curr.end());
    door.unlock();
}

int main()
{
    string find;
    cin >> find;
    vector<int> iter;
    int len2 = find.size();
    int len = 100;
    string s(len, 'a');
    thread t(generate, len, ref(s));
    t.join();
    cout << s << endl;
    thread f1(search, s, find, len, len2, 0, len / 2, ref(iter));
    thread f2(search, s, find, len, len2, len / 2 - (len2 - 1), len, ref(iter));
    f1.join();
    f2.join();
    for (auto a : iter)
    {
        cout << a << endl;
    }
}

//3
template <class T>
class ThreadSafePriorityQueue
{
	mutex mut;
	priority_queue<T> queue;
public:
	void push(T val)
	{
		mut.lock();
		queue.push(val);
		mut.unlock();
	}
	T pop()
	{
		T val = T();
		mut.lock();
		if (!queue.empty())
		{
			val = queue.top();
			queue.pop();
		}
		mut.unlock();
		return val;
	}
}
