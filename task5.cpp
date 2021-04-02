#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

#define C_ALL(X) cbegin(X), cend(X)

int main()
{
    //setlocale(LC_ALL, "Russian");
    string data = "We are bob@gmail.com, and amy@mamba.com, 10.00.00 not @phystech.com 23.59.01 or jane@mipt.org";
    //string names = "ваня, гена, ира";
    smatch m;

    const regex r(R"(\w+@\w+\.(?:com|in))");
    const vector<smatch> matches{
        sregex_iterator{C_ALL(data), r},
        sregex_iterator{}
        };

    const regex date(R"(\d[0-23]+\.\d[0-59]+\.\d[0-59]+)");
    const vector<smatch> dates{
        sregex_iterator{C_ALL(data), date},
        sregex_iterator{}
        };

    for (int i = 0; i < matches.size(); i++)
    {
        for (int j = 0; j < matches[i].size(); j++)
        {
            string temp = matches[i].str(j);
            bool found = regex_search(temp, m, regex(R"(@\w+\.(?:com|in))"));
            cout << matches[i].str(j) << '\t' << m.str() << endl;
        };
    };

    for (int i = 0; i < dates.size(); i++)
    {
        for (int j = 0; j < dates[i].size(); j++)
        {
            cout << dates[i].str(j) << endl;;
        };
    };
    
    /*map<string,string> letters = {
    {"а", "a"}, {"б", "b"}, {"в", "v"}, {"г", "g"},
    {"д", "d"}, {"е", "e"}, {"ж", "gh"}, {"з", "z"},
    {"и", "i"}, {"й", "j"}, {"к", "k"}, {"л", "l"},
    {"м", "m"}, {"н", "n"}, {"о", "o"}, {"п", "p"},
    {"р", "r"}, {"с", "s"}, {"т", "t"}, {"у", "u"},
    {"ф", "f"}, {"х", "h"}, {"ц", "c"}, {"ч", "ch"},
    {"ш", "sh"}, {"щ", "sch"}, {"ы", "y"}, {"э", "e"},
    {"ю", "yu"}, {"я", "ya"}
    };*/
    return 0;
}