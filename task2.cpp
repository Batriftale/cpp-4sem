//#2
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <iterator>
#include <algorithm>

using namespace std;
using namespace chrono;

// шаблон функции для измерения времени сортировки контейнера
template<typename T>
auto measureSortingTime(T container)
{
    auto start = high_resolution_clock::now();
    sort(container.begin(), container.end());
    auto end = high_resolution_clock::now();
    return end - start;
}

// специализация шаблона для list
template<>
auto measureSortingTime(list<int> container)
{
    auto start = high_resolution_clock::now();
    container.sort();
    auto end = high_resolution_clock::now();
    return end - start;   
}


int main()
{
    default_random_engine generator; //генератор случайных чисел
    uniform_int_distribution<int> distribution(0,10000); //равномерное распределение от 0 до 1000
    auto gen = [&distribution, &generator](){
                   return distribution(generator); // лямбда-функция, которая генерирует случайное число
               };

    //можно поэспериментировать с разными размерами контейнеров
    vector<int> v(100000);
    // заполнение вектора случайными числами
    generate(v.begin(), v.end(), gen);
    array<int, 100000> a;
    deque<int> d(100000);
    list<int> l(100000);
    // нам нужно, чтобы все контейнеры были запонены одинаковыми даннными
    // поэтому скопируем данные из вектора в другие контейнеры
    copy (v.begin(), v.end(), a.begin()); //копирование элементов вектора v в массив a
    copy (v.begin(), v.end(), d.begin());
    copy (v.begin(), v.end(), l.begin());
    //sort(v.begin(), v.end()); // сортировка у vector, array и deque
    //l.sort() // сортировка у list
    
    auto vectorTime = measureSortingTime(v);
    duration<double> time_span_vector = duration_cast<duration<double>>(vectorTime);

    auto arrayTime = measureSortingTime(a);
    duration<double> time_span_array = duration_cast<duration<double>>(arrayTime);

    auto dequeTime = measureSortingTime(d);
    duration<double> time_span_deque = duration_cast<duration<double>>(dequeTime);

    auto listTime = measureSortingTime(l);
    duration<double> time_span_list = duration_cast<duration<double>>(listTime);

    cout << time_span_vector.count() << endl;
    cout << time_span_array.count() << endl;
    cout << time_span_deque.count() << endl;
    cout << time_span_list.count() << endl;


    // быстрее всего array 

    return 0;
}


//#1
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main()
{
    default_random_engine gen; //генератор случайных чисел
    //равномерное распределение от 0 до 10.0
    uniform_real_distribution<double> dist(0.0,10.0);
    vector<double> v1;

    int lastCapasity = 1;

    for (int i = 0; i <= 30; i++)
    {
        v1.push_back(dist(gen));
        cout << "size1" << endl;
        cout << v1.size() << endl;
        cout << "capacity1" << endl;
        cout << v1.capacity() << endl;
        
        if (v1.capacity() > lastCapasity)
        {
            cout << "capacity1 rised" << endl;
            cout << v1.capacity() / lastCapasity << endl;
        }       
        lastCapasity = v1.capacity();
    }

    //когда ёмкости не хватает она увел. в 2 раза

    vector<int> v2;
    v2.reserve(32);

    lastCapasity = 1;

    for (int i = 0; i <= 40; i++)
    {
        v2.push_back(dist(gen));
        cout << "size2" << endl;
        cout << v2.size() << endl;
        cout << "capacity2" << endl;
        cout << v2.capacity() << endl;
        
        if (v2.capacity() > lastCapasity)
        {
            cout << "capacity2 rised" << endl;
            cout << v2.capacity() / lastCapasity << endl;
        }       
        lastCapasity = v1.capacity();
    }

    /*начальная ёмкость не меняется до того как размер не будет больше,
    чем ёмкость*/
    
    return 0;
}


//#3
#include <iostream>
#include <array>

using namespace std;

int main()
{
    array <int, 5> h = {3, 0, 2, 0, 4};
    int len = 5;

    int index_0 = 0;
    int index_n = len;

    int value_0 = 0;
    int value_n = 0;
    
    int volume = 0;
       
    while(index_0 < index_n)
    {
        
        if(h[index_n] > value_n)
        {
            value_n = h[index_n];
        }
        if(h[index_0] > value_0)
        {
            value_0 = h[index_0];
        }
        if(value_0 >= value_n)
        {
            volume += value_n - h[index_n];
            index_n--;
        }
        else
        {
            volume += value_0 - h[index_0];
            index_0++;
        }
    }
    cout << volume << endl;
        
return 0;
}
