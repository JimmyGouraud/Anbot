#ifndef OFFER_H
#define OFFER_H

#include <iostream>
#include <vector>

using namespace std;

class Offer
{
 public:
  Offer ();
  ~Offer ();
  void set_title (string title);
  void set_location (string location);
  void set_company (string company);
  void set_description (string description);
  void set_url (string url);
  void set_date (int day);
  void add_type (string type);

  string get_title (void);
  string get_location (void);
  string get_company (void);
  string get_description (void);
  string get_url (void);
  int get_date (void);
  string get_type (unsigned pos);

  unsigned get_nb_type ();
  void display(void);
  
 private:
  string title;
  std::vector<string> types; // CDI, interim, ..
  string location;
  string company;
  string description;
  string url;
  int date;
};

#endif /* OFFER_H */
