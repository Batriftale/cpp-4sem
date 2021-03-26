#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

bool comp1(int a){
    return a % 2 == 1;
}

bool comp2(int a){
    if(a < 0){
        a =-a;
    }
    if(a == 0){
        return false;
    }
    if(a == 1){
        return false;
    }
    int n = (int) sqrt(a);
    for(int i = 2; i <= n; i++){
        if(a % i == 0)
            return false;
    }
    return true;
}

int comp3(int a){
    return a * a;
}

int comp4(int a, int b){
    return a - b;
}

int comp5(int a){
    if(a < 0){
        return 0;
    }
    else{
        return a;
    }
}
int main()
{
    vector<int> p1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> p1_srt;
    vector<int>::iterator ip;
    int n, i, temp, pos;
    cout <<"Type how many numbers do you want to add"<< endl;
    cin >> n;
    cout << "Type in the numbers" << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> temp;
        p1.push_back(temp);
    }
    auto rng = default_random_engine {};
    shuffle(begin(p1), end(p1), rng);
    
    sort(p1.begin(), p1.end());
    ip = std::unique(p1.begin(), p1.begin() + 10 + n);
    p1.resize(std::distance(p1.begin(), ip));


    cout << count_if(p1.begin(), p1.end(), comp1) << endl; 
    cout << *min_element(p1.begin(), p1.end()) << " - min in p1" << endl;
    cout << *max_element(p1.begin(), p1.end()) << " - max in p1" << endl;
    cout << *find_if(p1.begin(), p1.end(), comp2) << endl; 
    transform(p1.begin(), p1.end(), p1.begin(), comp3);

    vector <int> p2(p1.size());
    generate(p2.begin(), p2.end(), rand);
    cout << accumulate(p2.begin(), p2.end(), 0) << endl; 
    fill(p2.begin(), p2.begin() + 2, 1);

    vector<int> p3;
    transform(p1.begin(), p1.end(), p2.begin(), back_inserter(p3), comp4);
    transform(p3.begin(), p3.end(), p3.begin(), comp5);
    remove(p3.begin(), p3.end(), 0);
    reverse(p3.begin(), p3.end());
    sort(p3.begin(), p3.end());
    cout << p3[p3.size() - 1] << " " << p3[p3.size() - 2] << " " << p3[p3.size() - 3];
}
