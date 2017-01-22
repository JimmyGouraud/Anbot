#include "research.hpp"

Research::Research(string job, string location, string distance, string no_wanted)
{
  this->job = job;
  this->location = location;
  this->distance = distance;
  this->no_wanted = no_wanted;
}

Research::~Research(){}

string Research::get_job()
{
  return this->job;
}

string Research::get_location()
{
  return this->location;
}

string Research::get_distance()
{
  return this->distance;
}

string Research::get_no_wanted()
{
  return this->no_wanted;
}
