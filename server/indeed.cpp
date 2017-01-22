#include "website.hpp"

/* ========================================
   ==  Part Indeed - extraction of data  ==
   ======================================== */

Indeed::Indeed (Research * research)
{
  this->website = "www.indeed.fr";
  string url = this->website;
  url.append("/emplois?");
  url.append("as_any=");
  url.append(research->get_job());
  url.append("&l=");
  url.append(research->get_location());
  url.append("&radius=");
  url.append(research->get_distance());

  if (!research->get_no_wanted().empty())
  {
    url.append("&as_not=");
    url.append(research->get_no_wanted());
  }
  
  url.append("&limit=1000");

  tab_url.push_back(url + "&jt=permanent");      // -> CDI
  tab_url.push_back(url + "&jt=contract");       // -> CDD
  tab_url.push_back(url + "&jt=fulltime");       // -> Temps plein
  tab_url.push_back(url + "&jt=parttime");       // -> Temps partiel
  tab_url.push_back(url + "&jt=temporary");      // -> Intérim
  tab_url.push_back(url + "&jt=subcontract");    // -> Freelance / Indépendant 
  tab_url.push_back(url + "&jt=apprenticeship"); // -> Apprentissage / Alternance
  tab_url.push_back(url + "&jt=internship");     // -> Stage
}



void Indeed::extract_offers (GumboNode * node)
{
  GumboAttribute * attributes;
  
  if (node->v.element.tag == GUMBO_TAG_DIV &&
      (attributes = gumbo_get_attribute(&node->v.element.attributes, "data-tn-component")))
  {
    if (strstr(attributes->value, "organicJob") != NULL)
    {
      int num_offer = add_offer();
      extract_informations(node, num_offer);

      int tmp_num_offer = find_offer(tab_offer[num_offer]->get_url());
      if (tmp_num_offer != num_offer && tmp_num_offer != -1)
      {
        tab_offer[tmp_num_offer]->add_type(tab_offer[num_offer]->get_type(0));
        tab_offer.pop_back();
      }
    }
  }
}


void Indeed::extract_informations (GumboNode * node, int num_offer)
{
  if (node->type != GUMBO_NODE_ELEMENT)
  {
    return;
  }

  extract_title_and_url (node, num_offer);
  extract_company (node, num_offer);
  extract_location (node, num_offer);
  extract_description (node, num_offer);
  extract_type (node, num_offer);
  extract_date (node, num_offer);
  
  GumboVector * children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; i++)
  {
    extract_informations(static_cast<GumboNode*>(children->data[i]), num_offer);
  }
}


void Indeed::extract_company (GumboNode *node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      node->parent->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "class")))
  {
    if (strstr(attributes1->value, "name") != NULL &&
        strstr(attributes2->value, "company") != NULL)
    {
      
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
      if (child->v.text.text != NULL )
      {
        string text = child->v.text.text;
        for (int i = 0; i < text.length(); i++)
        {
          if (text[i] == '\n' || text[i] == '\t')
          {
            text.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_company(text);
      }
            
      GumboVector * children = &node->v.element.children;
      for (unsigned int i = 0; i < children->length; i++)
      {
        child = static_cast<GumboNode*>(children->data[i]);
        if (child->type == GUMBO_NODE_ELEMENT &&
            child->v.element.tag == GUMBO_TAG_A)
        {
          GumboNode * child2 = static_cast<GumboNode*>(child->v.element.children.data[0]);
          if (child2->v.text.text != NULL )
          {
            string text = child2->v.text.text;
            for (int i = 0; i < text.length(); i++)
            {
              if (text[i] == '\n' || text[i] == '\t')
              {
                text.erase(i, 1); // erase 1 character at pos i.
              }
            }
            tab_offer[num_offer]->set_company(text);
          }
        }
      }
    }
  }
}



void Indeed::extract_title_and_url (GumboNode *node, int num_offer)
{
  GumboAttribute * attributes;

  if (node->v.element.tag == GUMBO_TAG_A && (attributes = gumbo_get_attribute(&node->v.element.attributes, "data-tn-element")))
  {
    if (strstr(attributes->value, "jobTitle") != NULL)
    {
      if (attributes = gumbo_get_attribute(&node->v.element.attributes, "title"))
      {
        tab_offer[num_offer]->set_title(attributes->value);
      }
      
      if (attributes = gumbo_get_attribute(&node->v.element.attributes, "href"))
      {
        string url = "http://" + this->website + attributes->value;
        tab_offer[num_offer]->set_url(url);
      }
    }
  }
}

void Indeed::extract_description (GumboNode *node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
      (attributes2 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")))
  {
    if (strstr(attributes1->value, "summary") != NULL &&
        strstr(attributes2->value, "description") != NULL)
    {
      GumboVector * children = &node->v.element.children;
      string description;

      for (unsigned int i = 0; i < children->length; i++)
      {
        GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[i]);
        if (child->type == GUMBO_NODE_ELEMENT)
        {
          child = static_cast<GumboNode*>(child->v.element.children.data[0]);
        }
        description.append(child->v.text.text);
      }

      tab_offer[num_offer]->set_description(description);
    }
  }
}

void Indeed::extract_location (GumboNode *node, int num_offer)
{
  GumboAttribute * attributes;

  if (node->v.element.tag == GUMBO_TAG_SPAN && (attributes = gumbo_get_attribute(&node->v.element.attributes, "itemprop")))
    {
      if (strstr(attributes->value, "addressLocality") != NULL)
	{
	  GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
	  if (child->v.text.text != NULL )
	    {
	      string text = child->v.text.text;
	      tab_offer[num_offer]->set_location(text);
	    }
	}
    }
}

void Indeed::extract_type (GumboNode * node, int num_offer)
{
  std::size_t pos = this->current_url.find_last_of("=");
  string type = this->current_url.substr(pos+1);

  for (int i = 0; i < tab_offer[num_offer]->get_nb_type(); i++)
  {
    if (strstr(tab_offer[num_offer]->get_type(i).c_str(), type.c_str()) != NULL)
    {
      return;
    }
  }

  tab_offer[num_offer]->add_type(type);  
}



void Indeed::extract_date (GumboNode *node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      node->parent->v.element.tag == GUMBO_TAG_DIV &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "class")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "class")))
  {
    if (strstr(attributes1->value, "date") != NULL &&
        strstr(attributes2->value, "result-link-bar") != NULL)
    {
      GumboVector * children = &node->v.element.children;
      string date;

      for (unsigned int i = 0; i < children->length; i++)
      {
        GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[i]);
        if (child->type == GUMBO_NODE_ELEMENT)
        {
          child = static_cast<GumboNode*>(child->v.element.children.data[0]);
        }
        date.append(child->v.text.text);
      }

      tab_offer[num_offer]->set_date(date);
    }
  }
}

void Indeed::extract_pages (GumboNode * node)
{
  
}

