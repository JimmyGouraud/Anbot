#include "create_html.hpp"

using namespace std;

string indent(int nb_indent)
{
  string indentation;
  for (unsigned i = 0; i < (unsigned)nb_indent; ++i) {
    indentation += "  ";
  }
  
  return indentation;
}


void generate_html (std::vector<Website *> * tab_website)
{
  std::ostringstream* oss_website = new ostringstream();
  html_by_website(tab_website, oss_website);
  ofstream file_website("offers_by_website.php", ios::trunc);
  file_website << oss_website->str();
  delete oss_website;

  std::ostringstream* oss_date = new ostringstream();
  html_by_date(tab_website, oss_date);
  ofstream file_date("offers_by_date.php", ios::trunc);
  file_date << oss_date->str();
  delete oss_date;
}

bool sort_offers2 (Offer* i, Offer* j)
{
  return (i->get_date() < j->get_date());
}

void sort_tab_offer(std::vector<Offer *>* tab_offer)
{
  std::sort (tab_offer->begin(), tab_offer->end(), sort_offers2);
}

void html_by_date(std::vector<Website *> * tab_website, std::ostringstream* oss)
{
  std::vector<Offer *> * tab_all_offers = new std::vector<Offer *>;
  Website* website;
  for (unsigned i = 0; i < tab_website->size(); ++i) {
    website = (* tab_website)[i];
    for (unsigned j = 0; j < website->get_nb_offers(); ++j) {
      tab_all_offers->push_back(website->get_offer(j));
    }
  }

  sort_tab_offer(tab_all_offers);

  bool a = true, b = false;
  Offer* offer;
  for (unsigned i = 0; i < tab_all_offers->size(); ++i) {
    offer = (* tab_all_offers)[i];
    if (offer->get_date() < 5) {
      if (a){
	*oss << indent(2) << "<section class=\"section-padding odd\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 0 à 4 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	a = false;
	b = true;
      }
    } else if (offer->get_date() < 10) {
      if (b){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding even\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 5 à 9 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	b = false;
	a = true;
      }
    } else if (offer->get_date() < 15) {
      if (a){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding odd\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 10 à 14 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	a = false;
	b = true;
      }
    } else if (offer->get_date() < 20) {
      if (b){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding even\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 15 à 19 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	b = false;
	a = true;
      }
    } else if (offer->get_date() < 25) {
      if (a){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding odd\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 20 à 24 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	a = false;
	b = true;
      }
    } else if (offer->get_date() < 30) {
      if (b){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding even\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
      	     << indent(6) << "<h4>Offres datant de 25 à 29 jours</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	b = false;
	a = true;
      }
    }else {
      if (a){
	*oss << indent(4) << "</div>" << endl
	     << indent(3) << "</div>" << endl
	     << indent(2) << "</section>" << endl
	     << indent(2) << "<section class=\"section-padding odd\">" << endl
	     << indent(3) << "<div class=\"container\">" << endl
	     << indent(4) << "<div class=\"row\">" << endl
	     << indent(5) << "<div class=\"header-section text-center\">" << endl
	     << indent(6) << "<h4>Offres datant de 30 jours ou plus</h4>" << endl
	     << indent(6) << "<hr class=\"bottom-line\">" << endl
	     << indent(5) << "</div>" << endl;
	a = false;
      }
    }
    html_offer(offer, i+1, oss);
  }
  *oss << indent(4) << "</div>" << endl
       << indent(3) << "</div>" << endl
       << indent(2) << "</section>" << endl;
}


void html_by_website(std::vector<Website *> * tab_website, std::ostringstream* oss)
{
  string parity;
  for (unsigned i = 0; i < tab_website->size(); ++i) {
    parity = (i%2 == 0? "odd" : "even");
    
    *oss << indent(2) << "<section class=\"section-padding " << parity << "\">" << endl
	 << indent(3) << "<div class=\"container\">" << endl
	 << indent(4) << "<div class=\"row\">" << endl;

    html_website((* tab_website)[i], oss);

    *oss << indent(4) << "</div>" << endl
	 << indent(3) << "</div>" << endl
	 << indent(2) << "</section>" << endl;
  }
}


void html_website (Website * website, std::ostringstream* oss)
{
  html_title(website->get_website(), website->get_nb_offers(), oss);

  *oss << indent(5) << "<div class=\"row feature-info\">" << endl;
  for (unsigned i = 0; i < website->get_nb_offers(); ++i) {
    html_offer(website->get_offer(i), i+1, oss);
  }
  *oss << indent(5) << "</div>" << endl;
}

string get_src_img(string title)
{
  if (strstr(title.c_str(), "www.indeed.fr") != NULL) {
    return "logo-indeed.png";
  }
  if (strstr(title.c_str(), "www.jobisjob.fr") != NULL) {
    return "logo-jobisjob.png";
  }
  if (strstr(title.c_str(), "candidat.pole-emploi.fr") != NULL) {
    return "logo-pole-emploi.png";
  }
  return "";
}

void html_title (string title, unsigned nb_offers, std::ostringstream* oss)
{
  *oss << indent(5) << "<div class=\"header-section text-center\">" << endl
      << indent(6) << "<img src=\"img/" << get_src_img(title) << "\"> " << endl
      << indent(6) << "<h4>Pâtissier - Saint-André-de-Cubzac - 50km</h4>" << endl
      << indent(6) << "<h4>(nombre d'offres trouvées : " << nb_offers  << ")</h4>" << endl
      << indent(6) << "<hr class=\"bottom-line\">" << endl
      << indent(5) << "</div>" << endl;
}

string display_class_types (Offer * offer)
{
  string types;
  for (unsigned i = 0; i < offer->get_nb_type(); ++i) {
    types.append(offer->get_type(i));
    if (i != offer->get_nb_type() - 1) {
      types.push_back(' ');
    }
  }
  
  return types;
}

string convert_type (string type)
{
  if (strstr(type.c_str(), "permanent") != NULL) { // -> CDI
    return "CDI";
  }
  if (strstr(type.c_str(), "contract") != NULL) { // -> CDI
    return "CDD";
  }
  if (strstr(type.c_str(), "fulltime") != NULL) { // -> Temps plein
    return "Temps plein";
  }
  if (strstr(type.c_str(), "parttime") != NULL) { // -> Temps partiel
    return "Temps partiel";
  }
  if (strstr(type.c_str(), "temporary") != NULL) { // -> Intérim
    return "Intérim";
  }
  if (strstr(type.c_str(), "subcontract") != NULL) { // -> Freelance / Indépendant 
    return "Freelance / Indépendant";
  }
  if (strstr(type.c_str(), "apprenticeship") != NULL) { // -> Apprentissage / Alternance
    return "Apprentissage / Alternance";
  }
  if (strstr(type.c_str(), "internship") != NULL) { // -> Stage
    return "Stage";
  }
  return type;
}

string display_types (Offer * offer)
{
  string types;
  for (unsigned i = 0; i < offer->get_nb_type(); ++i)
  {
    types.append(convert_type(offer->get_type(i)));
    if (i != (offer->get_nb_type() - 1))
    {
      types.append(" & ");
    }
  }
  return types;
}

void html_informations (Offer * offer, std::ostringstream* oss)
{
  // Title
  *oss << indent(10) << "<h4>" << offer->get_title() << "</h4> "<< endl
 
  // Company & Location
      << indent(10) << "<div>" << endl
      << indent(11) << "<span class=\"offer_company\">" << offer->get_company() << "</span>" << endl
      << indent(11) << " - " << endl
      << indent(11) << "<span class=\"offer_location\">" << offer->get_location() << "</span>" << endl
      << indent(10) << "</div>" << endl

  // Types
      << indent(10) << "<div>" << endl
      << indent(11) << "<span class=\"offer_type\">" << display_types(offer) << "</span>" << endl
      << indent(10) << "</div>" << endl

  // Description
      << indent(10) << "<div>" << endl
      << indent(11) << "<span class=\"offer_description\">" << offer->get_description() << "</span>" << endl
      << indent(10) << "</div>" << endl;
}


void html_date (Offer * offer, std::ostringstream* oss)
{
  int date = offer->get_date();
  
  switch(date)
  {
  case 0:
    *oss << "Aujourd'hui !";
    break;
  case 1:
    *oss << "Hier";
    break;
  case 30:
    *oss << "Il y a 30 jours ou plus";
    break;
  default:
    *oss << "Il y a " << date << " jours";
    break;
  }
}


void html_offer(Offer* offer, unsigned num_offer, std::ostringstream* oss)
{
  *oss << indent(6) << "<div class=\"" << display_class_types(offer) << "\">" << endl
       << indent(7) << "<div class=\"col-md-4 col-sm-6\">" << endl
       << indent(8) << "<div class=\"text-center\">Offre N°" << endl
       << indent(9) << num_offer << " - ";
  
  html_date(offer, oss);
  
  *oss << endl
       << indent(8) << "</div>" << endl
       << indent(8) << "<a href=\"" << offer->get_url() << "\">" << endl
       << indent(9) << "<div class=\"box-offer\">" << endl;

  html_informations(offer, oss);
  
  *oss << indent(9) << "</div>" << endl
       << indent(8) << "</a>" << endl
      << indent(7) << "</div>" << endl
      << indent(6) << "</div>" << endl;
}


