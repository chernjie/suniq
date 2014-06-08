/*
 * Copyright 2013 Chow Loong Jin <hyperair@debian.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <map>
#include <iterator>

template <typename Iter>
void print (Iter i, Iter end)
{
    for (; i != end; std::advance (i, 1))
        std::cout << '\t' << i->first << '\t' << i->second << std::endl;
}

void read_lines (std::istream &in, std::unordered_map<std::string, int> &map)
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
    std::unordered_map<std::string, int> map;

    bool reverse = false;

    for (char **i = argv + 1; *i; ++i) {
        if (std::strcmp (*i, "-r") == 0) {
            reverse = true;
            continue;
        }

        std::ifstream f (*i);

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
