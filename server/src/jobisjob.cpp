#include "website.hpp"

/* ==========================================
   ==  Part Jobisjob - extraction of data  ==
   ========================================== */


Jobisjob::Jobisjob (Research * research)
{
  this->website = "www.jobisjob.fr";
  string url = this->website;
  
  url.append("/");
  url.append(research->get_location());
  url.append("/");
  url.append(research->get_job());
  url.append("/emploi?");
  url.append("distance=");
  url.append("3");
  //url.append(research->get_distance());
  
  
  tab_url.push_back(url + "&jobType=CDI");
  tab_url.push_back(url + "&jobType=CDI,+Temps+Plein");
  tab_url.push_back(url + "&jobType=CDI,+Temps+Partiel");
  tab_url.push_back(url + "&jobType=CDD");
  tab_url.push_back(url + "&jobType=CDD,+Temps+Plein");
  tab_url.push_back(url + "&jobType=CDD,+Temps+Partiel");
  tab_url.push_back(url + "&jobType=Temps+Plein");
  tab_url.push_back(url + "&jobType=Temps+Partiel");
  tab_url.push_back(url + "&jobType=Intérim");
  tab_url.push_back(url + "&jobType=Freelance");
  tab_url.push_back(url + "&jobType=Contrat+D´alternance");
  tab_url.push_back(url + "&jobType=Contrat+D´apprentissage");
  tab_url.push_back(url + "&jobType=Stage");
}


void Jobisjob::extract_offers (GumboNode * node)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;
  
  if (node->v.element.tag == GUMBO_TAG_DIV &&
      node->parent->v.element.tag == GUMBO_TAG_DIV &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "class")))
  {
    if (strstr(attributes1->value, "offer") != NULL &&
        strstr(attributes2->value, "box_offer") != NULL)
    {
      unsigned num_offer = add_offer();
      extract_informations(node, num_offer);
      
      string title = this->tab_offer[num_offer]->get_title();
      if (strstr(title.c_str(), "Vendeur") != NULL ||
	  strstr(title.c_str(), "vendeur") != NULL ||
          strstr(title.c_str(), "Livreur") != NULL ||
	  strstr(title.c_str(), "livreur") != NULL ||
	  strstr(title.c_str(), "Chauffeur") != NULL ||
	  strstr(title.c_str(), "chauffeur") != NULL)
      {
        tab_offer.pop_back();
      }

      string description = this->tab_offer[num_offer]->get_description();
      if (strstr(description.c_str(), "- Règles d'hygiène et de sécurité alimentaire- Procédure d'encaissement- Utilisation de trancheuse- Calcul de quantité") != NULL ||
          strstr(description.c_str(), "- Procédures de fabrication de produits de boulangerie- Éléments de base en pâtisserie") != NULL)
      {
        tab_offer.pop_back();
      }
    }
  }
}


void Jobisjob::extract_informations (GumboNode * node, unsigned num_offer)
{
  if (node->type != GUMBO_NODE_ELEMENT)
  {
    return;
  }
  
  extract_title_and_url (node, num_offer);
  extract_company (node, num_offer);
  extract_location (node, num_offer);
  extract_description(node, num_offer);
  extract_type(node, num_offer);
  extract_date(node, num_offer);

  GumboVector * children = &node->v.element.children;
  for (unsigned i = 0; i < children->length; ++i)
  {
    extract_informations(static_cast<GumboNode*>(children->data[i]), num_offer);
  }
}


void Jobisjob::extract_title_and_url (GumboNode * node, unsigned num_offer)
{
  GumboAttribute * attributes;

  if (node->v.element.tag == GUMBO_TAG_A &&
      (attributes = gumbo_get_attribute(&node->v.element.attributes, "itemprop")))
  {  
    if (strstr(attributes->value, "title") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child->v.text.text != NULL) {
        string text = child->v.text.text;
        for (unsigned i = 0; i < text.length(); ++i) {
          if (text[i] == '\n') {
            text.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_title(text);
      }
          
      attributes = gumbo_get_attribute(&node->v.element.attributes, "href");      
      tab_offer[num_offer]->set_url(attributes->value);
    }
  }
}


void Jobisjob::extract_company (GumboNode * node, unsigned num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if ((node->v.element.tag == GUMBO_TAG_STRONG ||
       node->v.element.tag == GUMBO_TAG_A) &&
      node->parent->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "itemprop")))
  {  
    if (strstr(attributes1->value, "name") != NULL &&
        strstr(attributes2->value, "hiringOrganization") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child->v.text.text != NULL)
      {
        string company = child->v.text.text;
        for (unsigned i = 0; i < company.length(); ++i)
        {
          if (company[i] == '\n')
          {
            company.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_company(company);
      } else {
	tab_offer[num_offer]->set_company("?");
      }
    }
  }
}

void Jobisjob::extract_description (GumboNode * node, unsigned num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;  

  if (node->v.element.tag == GUMBO_TAG_P &&
      node->parent->v.element.tag == GUMBO_TAG_DIV &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "class")))
  {
    if (strstr(attributes1->value, "description") != NULL &&
        strstr(attributes2->value, "offer") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child->v.text.text != NULL )
      {
        string description = child->v.text.text;
        for (unsigned i = 0; i < description.length(); ++i)
        {
          if (description[i] == '\n')
          {
            description.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_description(description);
      }
    }
  }
}


void Jobisjob::extract_location (GumboNode * node, unsigned num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;  

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      node->parent->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "itemprop")))
  {  
    if (strstr(attributes1->value, "addressLocality") != NULL &&
        strstr(attributes2->value, "address") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child->v.text.text != NULL )
      {
        string location = child->v.text.text;
        for (unsigned i = 0; i < location.length(); ++i)
        {
          if (location[i] == '\n')
          {
            location.erase(i, 1); // erase 1 character at pos i.
          }
        }
        size_t pos = location.find(", Aquitaine Limousin Poitou-Charentes");
        if (pos != string::npos)
        {
          location.erase (location.begin() + pos, location.end());
        }
        tab_offer[num_offer]->set_location(location);
      }
    }
  }
}


void Jobisjob::extract_pages (GumboNode * node)
{
  GumboAttribute * attributes;
  
  if (node->v.element.tag == GUMBO_TAG_A &&
      node->parent->v.element.tag == GUMBO_TAG_LI &&
      node->parent->parent->v.element.tag == GUMBO_TAG_UL &&
      node->parent->parent->parent->v.element.tag == GUMBO_TAG_DIV &&
      (attributes = gumbo_get_attribute(&node->parent->parent->parent->v.element.attributes, "class")))
  {
    if (strstr(attributes->value, "paginator") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
      if (child->v.element.tag != GUMBO_TAG_STRONG) // if it's not the "next page"
      {
        attributes = gumbo_get_attribute(&node->v.element.attributes, "href");
        string value = attributes->value;
        size_t pos1 = value.find("/emploi");
        size_t pos2 = value.find("?", pos1);
        size_t pos3 = this->current_url.find("/emploi");
        string url = this->current_url;
        url.replace(pos3, 7, value.substr(pos1, pos2-pos1));
        tab_url.push_back(url);
      }
    }
  }
}

string Jobisjob::convert_type (string type)
{
  if (strstr(type.c_str(), "CDI") != NULL) {
    return "permanent";
  }
  
  if (strstr(type.c_str(), "CDD") != NULL) {
    return "contract";
  }
  
  if (strstr(type.c_str(), "Temps Plein") != NULL) {
    return "fulltime";
  }
  
  if (strstr(type.c_str(), "Temps Partiel") != NULL) {
    return "parttime";
  }
  
  if (strstr(type.c_str(), "Intérim") != NULL) {
    return "temporary";
  }
  
  if (strstr(type.c_str(), "Freelance") != NULL) {
    return "subcontract";
  }
  
  if (strstr(type.c_str(), "Contrat D´alternance") != NULL ||
      strstr(type.c_str(), "Contrat D´apprentissage") != NULL) {
    return "apprenticeship";
  }
  
  if (strstr(type.c_str(), "Stage") != NULL) {
    return "internship";
  }
  
  return type;
}

void Jobisjob::extract_type (GumboNode * node, unsigned num_offer)
{
  size_t pos = this->current_url.find_last_of("=");
  string type = this->current_url.substr(pos+1);
  vector<string> types;
  pos = type.find(",");
  if (pos != string::npos) {
    types.push_back(type.substr(0, pos));
    types.push_back(type.substr(pos+1, type.length() - pos));
  }
  else {
    types.push_back(type);
  }

  for (unsigned i = 0; i < types.size(); ++i) {
    type = types[i];
    for (unsigned j = 0; j < type.size(); ++j) {
      if (type[j] == '+') {
	if (j == 0) {
	  type.erase(0,1);
	} else {
	  type[j] = ' ';
	}
      }
    }
    types[i] = type;
  }

  for (unsigned i = 0; i < types.size(); ++i) {
    types[i] = convert_type(types[i]);
  }

  for (unsigned i = 0; i < tab_offer[num_offer]->get_nb_type(); ++i) {
    for (unsigned j = 0; j < types.size(); ++j) {
      if (strstr(tab_offer[num_offer]->get_type(i).c_str(), types[j].c_str()) != NULL) {
	return;
      }
    }
  }

  for (unsigned i = 0; i < types.size(); ++i) {
    tab_offer[num_offer]->add_type(types[i]);
  }
}


int Jobisjob::extract_day(string date)
{
  int day = 30;
  if (strstr(date.c_str(), "aujourd'hui") != NULL) {
    day = 0;
  } else if (strstr(date.c_str(), "Hier") != NULL) {
    day = 1;
  } else if (strstr(date.c_str(), "jour") != NULL) {
    size_t pos = date.find(" jours");
    day = atoi(date.substr(pos-2, 2).c_str());
  } else {
    cerr << " FAIL CONVERT DATE : " << date << endl;
  }
    
  return day;
}



void Jobisjob::extract_date (GumboNode * node, unsigned num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
      (attributes2 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")))
  {
    if (strstr(attributes1->value, "date") != NULL &&
	strstr(attributes2->value, "datePosted") != NULL)
    {
      GumboVector * children = &node->v.element.children;
      string date;

      for (unsigned i = 0; i < children->length; ++i) {
	GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[i]);
	if (child->type == GUMBO_NODE_ELEMENT) {
	  child = static_cast<GumboNode*>(child->v.element.children.data[0]);
	}
	date.append(child->v.text.text);
      }
      size_t pos = date.find_first_of("-");
      if (pos != string::npos) {
	date.erase(pos, 2);
      }

      tab_offer[num_offer]->set_date(extract_day(date));
    }
  }
}
