#ifndef CREATE_HTML_HPP
#define CREATE_HTML_HPP

#include "website.hpp"
#include <sstream>

string indent (int nb_indent);
void generate_html (std::vector<Website *> * tab_website);
void generate_html_website (Website * website);
void generate_html_title (string title, unsigned nb_offers);
void generate_html_offer (Offer * offer, unsigned num_offer);
void generate_html_informations (Offer * offer);
string display_types (Offer * offer);

#endif /* CREATE_HTML_HPP */
