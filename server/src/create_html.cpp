#include "create_html.hpp"


string indent(int nb_indent)
{
  string indentation;
  for (int i = 0; i < nb_indent; i++)
  {
    indentation += "  ";
  }
  return indentation;
}


void generate_html (std::vector<Website *> * tab_website)
{
  ofstream file("offers.php", ios::app);
  
  int num_website = 0;
  string parity;
  
  for (int i = 0; i < tab_website->size(); i++)
  {
    num_website++;
    parity = num_website%2 == 0?"even":"odd";
    
    file << indent(2) << "<section class=\"section-padding " << parity << "\">" << endl;
    file << indent(3) << "<div class=\"container\">" << endl;
    file << indent(4) << "<div class=\"row\">" << endl;

    generate_html_website((* tab_website)[i]);

    file << indent(4) << "</div>" << endl;
    file << indent(3) << "</div>" << endl;
    file << indent(2) << "</section>" << endl;
  }
}


void generate_html_website (Website * website)
{
  ofstream file("offers.php", ios::app);

  generate_html_title(website->get_website(), website->get_nb_offers());

  file << indent(5) << "<div class=\"row feature-info\">" << endl;
  for (int i = 0; i < website->get_nb_offers(); i++)
  {
    generate_html_offer(website->get_offer(i), i+1);
  }
  file << indent(5) << "</div>" << endl;
  
}

string get_src_img(string title)
{
  if (strstr(title.c_str(), "www.indeed.fr") != 0)
  {
    return "logo-indeed.png";
  }
  if (strstr(title.c_str(), "www.jobisjob.fr") != 0)
  {
    return "logo-jobisjob.png";
  }
  if (strstr(title.c_str(), "candidat.pole-emploi.fr") != 0)
  {
    return "logo-pole-emploi.png";
  }
  return "";
}

void generate_html_title (string title, int nb_offers)
{
  ofstream file("offers.php", ios::app);

  file << indent(5) << "<div class=\"header-section text-center\">" << endl;
  file << indent(6) << "<img src=\"img/" << get_src_img(title) << "\"> " << endl;
  //file << indent(6) << "<h2>" << title << "</h2>" << endl;
  file << indent(6) << "<h4>Pâtissier - Saint-André-de-Cubzac - 50km</h4>" << endl;
  file << indent(6) << "<h4>(nombre d'offres trouvées : " << nb_offers  << ")</h4>" << endl;
  file << indent(6) << "<hr class=\"bottom-line\">" << endl;
  file << indent(5) << "</div>" << endl;
}

string display_class_types (Offer * offer)
{
  string types;
  for (int i = 0; i < offer->get_nb_type(); i++)
  {
    types.append(offer->get_type(i));
    if (i != offer->get_nb_type() - 1)
    {
      types.push_back(' ');
    }
  }
  return types;
}

string convert_type (string type)
{
  if (strstr(type.c_str(), "permanent") != NULL) // -> CDI
  {
    return "CDI";
  }
  if (strstr(type.c_str(), "contract") != NULL) // -> CDI
  {
    return "CDD";
  }
  if (strstr(type.c_str(), "fulltime") != NULL) // -> Temps plein
  {
    return "Temps plein";
  }
  if (strstr(type.c_str(), "parttime") != NULL) // -> Temps partiel
  {
    return "Temps partiel";
  }
  if (strstr(type.c_str(), "temporary") != NULL) // -> Intérim
  {
    return "Intérim";
  }
  if (strstr(type.c_str(), "subcontract") != NULL) // -> Freelance / Indépendant 
  {
    return "Freelance / Indépendant";
  }
  if (strstr(type.c_str(), "apprenticeship") != NULL) // -> Apprentissage / Alternance
  {
    return "Apprentissage / Alternance";
  }
  if (strstr(type.c_str(), "internship") != NULL) // -> Stage
  {
    return "Stage";
  }
  return type;
}

string display_types (Offer * offer)
{
  string types;
  for (int i = 0; i < offer->get_nb_type(); i++)
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
  file << indent(10) << "<div>" << endl;
  file << indent(11) << "<span class=\"offer_company\">" << offer->get_company() << "</span>" << endl;
  file << indent(11) << " - " << endl;
  file << indent(11) << "<span class=\"offer_location\">" << offer->get_location() << "</span>" << endl;
  file << indent(10) << "</div>" << endl;

  // Types
  file << indent(10) << "<div>" << endl;
  file << indent(11) << "<span class=\"offer_type\">" << display_types(offer) << "</span>" << endl;
  file << indent(10) << "</div>" << endl;

  // Description
  file << indent(10) << "<div>" << endl;
  file << indent(11) << "<span class=\"offer_description\">" << offer->get_description() << "</span>" << endl;
  file << indent(10) << "</div>" << endl;
}

void generate_html_offer(Offer * offer, int num_offer)
{
  ofstream file("offers.php", ios::app);

  file << indent(6) << "<div class=\"" << display_class_types(offer) << "\">" << endl;
  file << indent(7) << "<div class=\"col-md-4 col-sm-6\">" << endl;
  
  file << indent(8) << "<div class=\"text-center\">Offre N°" << num_offer << " - " << offer->get_date() << "</div>" << endl;
  
  file << indent(8) << "<a href=\"" << offer->get_url() << "\">" << endl;
  file << indent(9) << "<div class=\"box-offer\">" << endl;
  generate_html_informations(offer);
  file << indent(9) << "</div>" << endl;
  file << indent(8) << "</a>" << endl;
  
  file << indent(7) << "</div>" << endl;
  file << indent(6) << "</div>" << endl;
}


