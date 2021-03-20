# include <iostream>
# include <vector>
# include <fstream>
# include <regex>
# include <algorithm>
# include <sstream>
# include <chrono>
# include <fmt/format.h>

using namespace fmt::literals;
using namespace std::literals;

int main(int, const char** argv)
{
    std::ifstream ins("dict.txt");
    std::array<std::ofstream, 26> ous;
    for (unsigned i = 0; i < 26; i++)
        ous[i].open("dict/{}.txt"_format(char('a' + i)));
    std::vector<std::string> words;
    std::string s;
    static auto start_time = std::chrono::steady_clock::now();

    while (std::getline(ins, s))
        words.push_back(s);
    std::cout << "read finish.\n";

    std::sort(words.begin(), words.end());
    std::cout << "sort finish.\n";

    // ignore first one
    for (unsigned i = 1; i < words.size(); i++)
    {
        if ((i == 0 || words[i] != words[i - 1]))
        {
            unsigned space_location = words[i].find(' ');
            while (words[i].find("lue") != std::string::npos)
                words[i].replace(words[i].find("lue"), 3, "lve");
            while (words[i].find("nue") != std::string::npos)
                words[i].replace(words[i].find("nue"), 3, "nve");
            ous[words[i][1] - 'a'] << words[i].substr(space_location + 1) << '\t' << words[i].substr(1, space_location - 1) << "\t0\n";
        }
        if (i % 1'000'000 == 0)
            std::cout << "output {}/{} words ({} %) in {} seconds.\n"_format(i, words.size(), i * 100, (std::chrono::steady_clock::now() - start_time) / 1s);
    }
    std::cout << "write finish.\n";

    return 0;
}