#ifndef RESEARCH_HPP
#define RESEARCH_HPP

#include <string>

using namespace std;

class Research
{
 public:
  Research(string job, string location, string distance, string no_wanted);
  ~Research();
  string get_job();
  string get_location();
  string get_distance();
  string get_no_wanted();
  
 private:
  string job;
  string location;
  string distance;
  string no_wanted;
};


#endif /* RESEARCH_HPP */
