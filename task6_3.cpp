#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <chrono>
namespace ls = std::filesystem;
int main()
{
	ls::current_path(ls::temp_directory_path());
    for(auto& p: ls::recursive_directory_iterator("path"))
    std::cout << p.path() << ls::is_directory;
    if(ls::is_regular_file("path")) std::cout << "обычный файл" << endl;
    if (ls::is_directory("path")) std::cout << "директория" << endl;
    std::cout << " Время последнего  изменения: " << ls::last_write_time("path") << endl;
}
