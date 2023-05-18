#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>
#include <string_view>
#include <iostream>


namespace Utils
{
    //Это из второй работы
    void split(const std::string& str, std::vector<std::string>& out, char d)
    {
        auto stop = str.find_first_of(d);
        decltype(stop) start = 0;

        while(stop != std::string::npos)
        {
            out.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }
        out.push_back(str.substr(start));
    }
}

#endif // UTILS_HPP
