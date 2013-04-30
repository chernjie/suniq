#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <iterator>

template <typename Iter>
void print (Iter i, Iter end)
{
    for (; i != end; std::advance (i, 1))
        std::cout << '\t' << i->first << '\t' << i->second << std::endl;
}

void read_lines (std::istream &in, std::map<std::string, int> &map)
{
    std::string buf;
    while (std::getline (in, buf)) {
        auto iterp = map.insert ({buf, 1});
            if (!iterp.second)
                ++iterp.first->second;
    }
}

int main (int argc, char **argv)
{
    std::map<std::string, int> map;

    bool reverse = false;

    for (char **i = argv + 1; *i; ++i) {
        if (std::strcmp (*i, "-r") == 0) {
            reverse = true;
            continue;
        }

        std::ifstream f (*i);

        if (!f)
            continue;

        read_lines (f, map);
    }

    if (argc - (int)reverse == 1)
        read_lines (std::cin, map);

    std::multimap<int, std::string> revmap;
    for (const auto &p : map)
        revmap.insert ({p.second, p.first});

    if (reverse)
        print (revmap.rbegin (), revmap.rend ());

    else
        print (revmap.begin (), revmap.end ());

    return 0;
}
