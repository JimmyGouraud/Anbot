#ifndef WEBSITE_H
#define WEBSITE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <curl/curl.h>
#include "gumbo.h"
#include "offer.hpp"
#include "research.hpp"

class Website
{
 public:
  ~Website ();
  
  string website;  // the website (ex : "www.indeed.fr")
  std::vector<string> tab_url; // Contains URL
  std::vector<Offer *> tab_offer;  // contains offers
  string data; // Contains HTML of the actual page
  string current_url;
  
  string get_website ();
  Offer * get_offer (int i);
  int get_nb_offers ();
  int add_offer();
  void display_offers ();
  int find_offer(string url);

  virtual void run();
  virtual int initialize_curl (const char* url);
  virtual void extract_data (GumboNode * node, bool research_others_pages);
  
  virtual void extract_offers (GumboNode * node) = 0;
  virtual void extract_informations (GumboNode * node, int num_offer) = 0;
  virtual void extract_title_and_url (GumboNode * node, int num_offer) = 0;
  virtual void extract_type (GumboNode * node, int num_offer) = 0;
  virtual void extract_location (GumboNode * node, int num_offer) = 0;
  virtual void extract_company (GumboNode * node, int num_offer) = 0;
  virtual void extract_description (GumboNode * node, int num_offer) = 0;
  virtual void extract_date (GumboNode * node, int num_offer) = 0;
  virtual void extract_pages (GumboNode * node) = 0;
};


class Indeed : public Website
{
 public:
  Indeed (Research * research);
  
  void extract_offers (GumboNode * node);
  void extract_informations (GumboNode * node, int num_offer);
  void extract_title_and_url (GumboNode * node, int num_offer);
  void extract_type (GumboNode * node, int num_offer);
  void extract_location (GumboNode * node, int num_offer);
  void extract_company (GumboNode * node, int num_offer);
  void extract_description (GumboNode * node, int num_offer);
  void extract_date (GumboNode * node, int num_offer);
  void extract_pages (GumboNode * node);
};


class Jobisjob : public Website
{
 public:
  Jobisjob (Research * research);

  void extract_offers (GumboNode * node);
  void extract_informations (GumboNode * node, int num_offer);
  void extract_title_and_url (GumboNode * node, int num_offer);
  void extract_type (GumboNode * node, int num_offer);
  void extract_location (GumboNode * node, int num_offer);
  void extract_company (GumboNode * node, int num_offer);
  void extract_description (GumboNode * node, int num_offer);
  void extract_date (GumboNode * node, int num_offer);
  void extract_pages (GumboNode * node);

  string convert_type (string type);
};


class PoleEmploi : public Website
{
 public:
  PoleEmploi (Research * research);

  int initialize_curl (const char* url);
  void run ();
  
  void extract_offers (GumboNode * node);
  void extract_informations (GumboNode * node, int num_offer);
  void extract_title_and_url (GumboNode * node, int num_offer);
  void extract_type (GumboNode * node, int num_offer);
  void extract_location (GumboNode * node, int num_offer);
  void extract_company (GumboNode * node, int num_offer);
  void extract_description (GumboNode * node, int num_offer);
  void extract_date (GumboNode * node, int num_offer);
  void extract_pages (GumboNode * node);

 private:
  string create_cookie ();
  void exec_command_bash();
  //int curl_post(string url);
  string convert_type (string type);
};

#endif /* WEBSITE_H */
