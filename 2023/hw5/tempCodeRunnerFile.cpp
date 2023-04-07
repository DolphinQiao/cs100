#include <cstddef>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
std::string strip(const std::string &str);
std::string join(const std::string &sep, const std::vector<std::string> &strings);
std::vector<std::string> split(const std::string &str, const std::string &sep);
std::string swapcase(std::string str);
std::string strip(const std::string &str)
{
  std::size_t begin = 0, end = str.size() - 1;
  for(std::size_t i = 0; i < str.size(); ++i)
  {
    begin = i;
    if(!std::isspace(str[i])) break;
  }
  for(std::size_t i = str.size() - 1; i != std::size_t(-1); --i)
  {
    end = i;
    if(!std::isspace(str[i])) break;
  }
  if(end < begin) return std::string("");
  return std::string(str.substr(begin, end - begin + 1));
}
std::string join(const std::string &sep, const std::vector<std::string> &strings)
{
  if(strings.size() == 0) return std::string("");
  if(strings.size() == 1) return strings[0];
  std::string ans=strings[0];
  for(std::size_t i = 1; i < strings.size(); ++i)
    ans += sep + strings[i];
  return ans;
}
std::vector<std::string> split(const std::string &str, const std::string &sep)
{
  std::size_t now = 0;
  std::vector<std::string> ans;
  ans.clear();
  while(1)
  {
    int pos = str.find(sep, now);
    if(pos == -1) break;
    pos += now;
    if(int(now) == pos) ans.push_back(std::string(""));
    else ans.push_back(str.substr(now, pos - now));
    now = pos + sep.size();
  }
  ans.push_back(str.substr(now, str.size() - now));
  return ans;
}
std::string swapcase(std::string str)
{
  for(std::size_t i = 0; i < str.size(); ++i)
  {
    if(std::islower(str[i])) str[i] = std::toupper(str[i]);
    else if(std::isupper(str[i])) str[i] = std::tolower(str[i]);
  }
  return str;
}
int main()
{
for(auto x :split("fwafew240=-p[';['l;.]]", "]]"))
{
  std::cout<<x+"a"<<std::endl;
}
  return 0;
}