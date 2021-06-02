#include <string_utils.h>

std::vector<std::string> split(std::string s, std::string delimiter)
{
    std::vector<std::string> result;
    size_t pos = s.find(delimiter);
    size_t prevPos = 0;

    if (pos == std::string::npos)
    {
        result.push_back(s);
        return result;
    }
    while (pos != std::string::npos)
    {
        std::string split = s.substr(prevPos, pos - prevPos);
        result.push_back(split);
        prevPos = pos + delimiter.size();
        pos = s.find(delimiter, prevPos);
    }

    if (prevPos < s.size())
    {
        result.push_back(s.substr(prevPos));
    }
    return result;
}