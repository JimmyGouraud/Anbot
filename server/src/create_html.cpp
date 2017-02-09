#include "create_html.hpp"

using namespace std;

string indent(int nb_indent)
{
  string indentation;
  for (unsigned i = 0; i < (unsigned)nb_indent; i++) {
    indentation += "  ";
  }
  
  return indentation;
}


void generate_html (std::vector<Website *> * tab_website)
{
  ofstream file("offers.php", ios::app);
  string parity;
  
  for (unsigned i = 0; i < tab_website->size(); i++) {
    parity = (i%2 == 0? "odd" : "even");
    
    file << indent(2) << "<section class=\"section-padding " << parity << "\">" << endl
	 << indent(3) << "<div class=\"container\">" << endl
	 << indent(4) << "<div class=\"row\">" << endl;

    generate_html_website((* tab_website)[i]);

    file << indent(4) << "</div>" << endl
	 << indent(3) << "</div>" << endl
	 << indent(2) << "</section>" << endl;
  }
}


void generate_html_website (Website * website)
{
  ofstream file("offers.php", ios::app);

  generate_html_title(website->get_website(), website->get_nb_offers());

  file << indent(5) << "<div class=\"row feature-info\">" << endl;
  for (unsigned i = 0; i < website->get_nb_offers(); i++) {
    generate_html_offer(website->get_offer(i), i+1);
  }
  file << indent(5) << "</div>" << endl;
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

void generate_html_title (string title, unsigned nb_offers)
{
  ofstream file("offers.php", ios::app);

  file << indent(5) << "<div class=\"header-section text-center\">" << endl
       << indent(6) << "<img src=\"img/" << get_src_img(title) << "\"> " << endl
       << indent(6) << "<h4>Pâtissier - Saint-André-de-Cubzac - 50km</h4>" << endl
       << indent(6) << "<h4>(nombre d'offres trouvées : " << nb_offers  << ")</h4>" << endl
       << indent(6) << "<hr class=\"bottom-line\">" << endl
       << indent(5) << "</div>" << endl;
}

string display_class_types (Offer * offer)
{
  string types;
  for (unsigned i = 0; i < offer->get_nb_type(); i++) {
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
  for (unsigned i = 0; i < offer->get_nb_type(); i++)
  {
    types.append(convert_type(offer->get_type(i)));
    if (i != (offer->get_nb_type() - 1))
    {
      types.append(" & ");
    }
  }
  return types;
}

void generate_html_informations (Offer * offer)
{
  ofstream file("offers.php", ios::app);

  // Title
  file << indent(10) << "<h4>" << offer->get_title() << "</h4> "<< endl;

  // Company & Location
  file << indent(10) << "<div>" << endl
       << indent(11) << "<span class=\"offer_company\">" << offer->get_company() << "</span>" << endl
       << indent(11) << " - " << endl
       << indent(11) << "<span class=\"offer_location\">" << offer->get_location() << "</span>" << endl
       << indent(10) << "</div>" << endl;

  // Types
  file << indent(10) << "<div>" << endl
       << indent(11) << "<span class=\"offer_type\">" << display_types(offer) << "</span>" << endl
       << indent(10) << "</div>" << endl;

  // Description
  file << indent(10) << "<div>" << endl
       << indent(11) << "<span class=\"offer_description\">" << offer->get_description() << "</span>" << endl
       << indent(10) << "</div>" << endl;
}

string generate_html_date (Offer * offer)
{
  int date = offer->get_date();
  
  ostringstream str_date;
  switch(date)
  {
  case 0:
    str_date << "Aujourd'hui !";
    break;
  case 1:
    str_date << "Hier";
    break;
  case 30:
    str_date << "Il y a plus de 30 jours";
      break;
  default:
    str_date << "Il y a " << date << " jours";
    break;
  }
  
  return str_date.str();
}


void generate_html_offer(Offer* offer, unsigned num_offer)
{
  ofstream file("offers.php", ios::app);

  file << indent(6) << "<div class=\"" << display_class_types(offer) << "\">" << endl
       << indent(7) << "<div class=\"col-md-4 col-sm-6\">" << endl
       << indent(8) << "<div class=\"text-center\">Offre N°" << endl
       << indent(9) << num_offer << " - " << generate_html_date(offer) << endl
       << indent(8) << "</div>" << endl
       << indent(8) << "<a href=\"" << offer->get_url() << "\">" << endl
       << indent(9) << "<div class=\"box-offer\">" << endl;

  generate_html_informations(offer);
  
  file << indent(9) << "</div>" << endl
       << indent(8) << "</a>" << endl
       << indent(7) << "</div>" << endl
       << indent(6) << "</div>" << endl;
}


