#ifndef CREATE_HTML_HPP
#define CREATE_HTML_HPP

#include "website.hpp"
#include "offer.hpp"
#include <sstream>
#include <algorithm>

string indent(int nb_indent);
void generate_html (std::vector<Website *> * tab_website);
void html_by_date(std::vector<Website *> * tab_website, std::ostringstream* oss);
void html_by_website (std::vector<Website *> * tab_website, std::ostringstream* oss);
void html_website (Website * website, std::ostringstream* oss);
void html_title (string title, unsigned nb_offers, std::ostringstream* oss);
void html_informations (Offer * offer, std::ostringstream* oss);
void html_date (Offer * offer, std::ostringstream* oss);
void html_offer(Offer* offer, unsigned num_offer, std::ostringstream* oss);

string get_src_img (string title);
string display_class_types (Offer * offer);
string convert_type (string type);
string display_types (Offer * offer);

#endif /* CREATE_HTML_HPP */
