#include "offer.hpp"


Offer::Offer(){}

Offer::~Offer()
{
  types.clear();
}

void Offer::set_title (string title)
{
  this->title = title;
}

void Offer::set_location (string location)
{
  this->location = location;
}

void Offer::set_company (string company)
{
  this->company = company;
}

void Offer::set_description (string description)
{
  this->description = description;
}

void Offer::set_url (string url)
{
  this->url = url;
}

void Offer::set_date (string date)
{
  this->date = date;
}

void Offer::add_type (string type)
{
  this->types.push_back(type);
}



string Offer::get_title (void)
{
  return this->title;
}

string Offer::get_location (void)
{
  return this->location;
}

string Offer::get_company (void)
{
  return this->company;
}

string Offer::get_description (void)
{
  return this->description;
}

string Offer::get_url (void)
{
  return this->url;
}

string Offer::get_date (void)
{
  return this->date;
}

string Offer::get_type (int pos)
{
  return this->types[pos];
}



int Offer::get_nb_type (void)
{
  return this->types.size();
}


void Offer::display(void)
{
  cout << " Title       -> " << this->title << endl;
  cout << " Type        -> ";
  for (int i = 0; i < this->types.size(); i++)
  {
    cout << this->types[i];
    if (i != this->types.size() - 1)
    {
      cout << " ; ";
    }
  }
  cout << endl;
  cout << " Location    -> " << this->location << endl;
  cout << " Company     -> " << this->company << endl;
  cout << " Description -> " << this->description << endl;
  cout << " URL         -> " << this->url << endl;
}
