#include "website.hpp"
#include <stdlib.h>

/* =============================================
   ==  Part Pole-Emploi - extraction of data  ==
   ============================================= */

static size_t poleEmploi_curl_callback (void *data, size_t size, size_t nmemb, void *pointer)
{
  ((string*) pointer)->append((char*) data, size * nmemb);
  return size * nmemb;
}

PoleEmploi::PoleEmploi (Research * research)
{
  this->website = "candidat.pole-emploi.fr";
  string url = this->website;
  url = "candidat.pole-emploi.fr/candidat/rechercheoffres/resultats/A_";
  url.append(research->get_job());
  url.append("_COMMUNE_33240_");
  url.append(research->get_distance());
  url.append("__P__________INDIFFERENT_______________________");
  tab_url.push_back(url);
}


void PoleEmploi::extract_offers (GumboNode * node)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;
  GumboAttribute * attributes3;

  if (node->v.element.tag == GUMBO_TAG_IMG &&
      node->parent->v.element.tag == GUMBO_TAG_TD &&
      node->parent->parent->v.element.tag == GUMBO_TAG_TR &&
      node->parent->parent->parent->v.element.tag == GUMBO_TAG_TBODY &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "alt")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "headers")) &&
      (attributes3 = gumbo_get_attribute(&node->parent->parent->v.element.attributes, "itemtype")))
  {
    if (strstr(attributes1->value, "optimale") != NULL &&
        strstr(attributes2->value, "pertinence") != NULL &&
        strstr(attributes3->value, "http://schema.org/JobPosting") != NULL)
    {
      int num_offer = add_offer();
      extract_informations(node->parent->parent, num_offer);
      if (strstr(tab_offer[num_offer]->get_type(0).c_str(), "Reprise entreprise") != NULL)
      {
        tab_offer.pop_back();
      }
    }
  }
}

void PoleEmploi::extract_informations (GumboNode * node, int num_offer)
{
  if (node->type != GUMBO_NODE_ELEMENT)
  {
    return;
  }

  extract_title_and_url (node, num_offer);
  extract_company (node, num_offer);
  extract_location (node, num_offer);
  extract_description (node, num_offer);
  extract_type(node, num_offer);
  extract_date(node, num_offer);

  GumboVector * children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; i++)
  {
    extract_informations(static_cast<GumboNode*>(children->data[i]), num_offer);
  }
}


void PoleEmploi::extract_title_and_url (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes;
  
  if (node->v.element.tag == GUMBO_TAG_A &&
      (attributes = gumbo_get_attribute(&node->v.element.attributes, "itemprop")))
  {  
    if (strstr(attributes->value, "title") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child != NULL && child->v.text.text != NULL )
      {
        string text = child->v.text.text;
        for (int i = 0; i < text.length(); i++)
        {
          if (text[i] == '\n')
          {
            text.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_title(text);
      }
      
      if (attributes = gumbo_get_attribute(&node->v.element.attributes, "href"))
      {
        string url = "http://" + this->website + attributes->value;
        tab_offer[num_offer]->set_url(url);
      }
    }
  }
}


void PoleEmploi::extract_company (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;  

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      node->parent->v.element.tag == GUMBO_TAG_SPAN &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "itemprop")))
  {
    if (strstr(attributes1->value, "name") != NULL &&
        strstr(attributes2->value, "hiringOrganization") != NULL)
    {
      
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
      
      if (child != NULL && child->v.text.text != NULL)
      {
        string company = child->v.text.text;
        for (int i = 0; i < company.length(); i++)
        {
          if (company[i] == '\n')
          {
            company.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_company(company);
      }
    }
  }
}


void PoleEmploi::extract_location (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;  

  if (node->v.element.tag == GUMBO_TAG_SPAN &&
      node->parent->v.element.tag == GUMBO_TAG_TD &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "itemprop")))
  {  
    if (strstr(attributes1->value, "addressLocality") != NULL &&
        strstr(attributes2->value, "jobLocation") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child != NULL && child->v.text.text != NULL )
      {
        string location = child->v.text.text;
        for (int i = 0; i < location.length(); i++)
        {
          if (location[i] == '\n')
          {
            location.erase(i, 1); // erase 1 character at pos i.
          }
        }
        tab_offer[num_offer]->set_location(location);
      }
    }
  }
}


void PoleEmploi::extract_description (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes;
  
  if (node->v.element.tag == GUMBO_TAG_P &&
      (attributes = gumbo_get_attribute(&node->v.element.attributes, "class")))
  {  
    if (strstr(attributes->value, "description") != NULL)
    {
      GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
      if (child != NULL && child->v.text.text != NULL )
      {
        string description = child->v.text.text;
        for (int i = 0; i < description.length(); i++)
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


void PoleEmploi::extract_pages (GumboNode * node)
{

}


string PoleEmploi::create_cookie ()
{  
  ifstream file("cookie.txt", ifstream::in);
  string cookie = "xtvrn=$475540$; xtan475540=-; xtant475540=1";
  string line;
  int num_line = 0;
  while (getline(file, line))
  {
    string tmp;
    if (num_line > 3)
    {
      int cpt = 0;
      for (int i = 0; i < line.length(); i++){
        if (line[i] == '\t')
        {
          cpt++;
          if (cpt > 5)
          {
            tmp.push_back('=');
          }
          continue;
        }
        if (cpt > 4)
        {
          tmp.push_back(line[i]);
        }
      }
      cookie.append("; ");
      cookie.append(tmp);
    }
    num_line++;
  }
  return cookie;
}



 
void PoleEmploi::run ()
{
  tab_url.push_back(tab_url[0]);
  
  GumboOutput * output;
  int initial_size = tab_url.size();
  bool research_others_pages = true;
  
  for (int i = 0; i < tab_url.size(); i++)
    {
      if (i > initial_size)
	{
	  research_others_pages = false;
	}

      this->current_url = tab_url[i];
    
      cout << "\033[32m - " << this->current_url << "\033[00m" << endl;

      if (initialize_curl(this->current_url.c_str()) == 0)
	{
	  if (i == 0)
	    {
	      exec_command_bash();
	      continue;
	    }
   
	  output = gumbo_parse(data.c_str());
	  extract_data(output->root, research_others_pages);
	  gumbo_destroy_output(&kGumboDefaultOptions, output);
	}
    
      data.clear();
    }
}


void PoleEmploi::exec_command_bash()
{
  string cookie = create_cookie();
      
  string command_bash = "curl 'http://candidat.pole-emploi.fr/candidat/rechercheoffres/resultats.composantresultatrechercheoffre.ajouterauclasseur' -H 'Host: candidat.pole-emploi.fr' -H 'User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0' -H 'Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8' -H 'Accept-Language: en-US,en;q=0.5' --compressed -H 'Referer: http://candidat.pole-emploi.fr/candidat/rechercheoffres/resultats/A_patissier_COMMUNE_33240_50__P__________INDIFFERENT_______________________' -H 'Cookie: ";
  command_bash.append(cookie);
  command_bash.append("' -H 'Connection: keep-alive' -H 'Upgrade-Insecure-Requests: 1' --data 't%3Aac=A_p%2400e2tissier_COMMUNE_33240_50__P__________INDIFFERENT_______________________&t%3Asubmit=%5B%22nombreLignesMax%22%2C%22nombreLignesMax%22%5D&t%3Aformdata=GAizWFGMGFsH6tjv1NJCmKJuWxo%3D%3AH4sIAAAAAAAAAFvzloEVAN3OqfcEAAAA&t%3Aformdata=GWlUjVH2z4rEQ8gJL315qlhvQKw%3D%3AH4sIAAAAAAAAAK2Rv0oDQRDGJweikEJRfIPYbhrTmCqIQvA0YhCRVHubucuG291zd2LORp9AX0CwshRfIoWdhW%2FgA9haWbiXE%2F%2BQSsjANB%2FfML%2BP7%2BENFsZ70LYoBmj9mji26OpH6EYpcXJbwqjMOK7Jfkl%2FrUwbFVlMZaLRKZ47Cw1jE8Yz7i2MeIaO7EWDCVO4IhZxh6wVeZEL2pWY9mtdpFG2cTypvq4%2FfQRQCaEqjH9o0gOukGA1HPJzXk%2B5TupdslInzdzCSiGyQmSdaIiC4GfyjGC5JAunZPs8n3fM1n9jHloj0LnuKFLSOWn05LG%2FGb%2FfPQce%2BAwuIRifwsncEGuYokJNrvhHHng7tixDpoSHVGqkv6mZHCimZC61Yzvl0RSSZpFvr65v7ju9lwCCEJZEKr233S%2FgKz1YLFrDnAjWer8qK9tplhFne8k%2BAQJkSQ%2BEAgAA&nombreLignesMax=100&t%3Aformdata=NlPO6PuXdP%2FmTB9OEL9o09xG%2BEk%3D%3AH4sIAAAAAAAAAFWPT0oDUQzGQ0F0KQo9QdeZvV1JcVEoVKy7Wb15zbRveP9IMjpdeQK9gFuXnsZ7eAdnOgU1EEJ%2B%2Bb7A9%2FkNZ89bqJjsnrjvVNdMUjyQtF6Nyo1NIScxUfmE%2FkuxSq2maJp%2BWG9EqGVNGU08zMhToKjSVsGpMCxqxkwYLPZPQxtRTSZRPqDbBwyuc1HwbjRtjqbZPSdLIsdNxKX4%2FvL69rEuvyYwWcGF9a7XLrcKV6vGPJnCm7grNsou7uYlnNsUlTpVuC7%2F3NdVQ1bnHcPlAHGAOEL4rS4rTMd0t0O6xSndY8r5B1z0wI83AQAA&t%3Aformdata=bF38WMC%2BqOcR1NAKcT%2BRx3ecphg%3D%3AH4sIAAAAAAAAAO2aT0hUQRzHxyVLtIMUbR07GOTB0f2nlkWJZAabikv%2FULR5b2fXp%2B%2B9ec7M05WgLh06VHTrEBSBt7Jr18hDePFQ0T3oGkRFp4Jmdt1dl9ZAWdc3MgsL783M7%2F2%2B8%2F3MYfjxe%2FkVNC5MggmKzWlMxZ9kMhSzzjHMfJsjzk6bxPEIQy6n60OVSyFHho2Rv8msTYjHKICEZiHykBgXAR5mnC4moEkoti0D5lO42OUMJsX6tuh3L9N%2BMfziXAiAHAWtM2geQRu5WThizGCTg%2FIv5wVOfezNybtDsZ%2FLQKqfA7dBw4IBbu6URPFgzhokJ2Qm%2FivTQAzDfkMMIpMPWthOt6Uw970TV1ZaPh959zsEGpKgxSRCB7GHkYM5OJSUzndK5ztTnFputq%2BwIQ6ainnrtLf%2Bre5tlBITM5byDcdizCLuyqt0PPPr6VqZStAOTnzjsa%2BLRJlkX10IykyNHDQXB6a66pFWZm2uh4kH9zCpiCalCKmoJqUIqZgmpQipuCalCKmEJqUIqW5NShFSPZqUIqR6NSlFSJ3SpAJNqqVEKqKLFMqg0lUKZVDpMoUyqHSdQhlUulChDCpdqVAGlS5VKINK1yqUQbXXihXDILn9JB7KWi7iFnENxLbXOZDoGFn91A5urZY7B3ZbUuTGl%2BUfmdcfnu%2BkpOEtSRLJuJhKiY%2FjQUqclHxLD9iWWHIV2T7uePz24z1w%2FM96K0x5QurfX2x9aYjUeic7c4jkV3uE3OgCBV7Nvmy5s0z21HA0j03ZLYRzHEPkLrZhGzvS7PysgDOQodDD0DElCMd3S4SgNe1Ax8pZLoMXCkH5Nh3%2Bb9POkzsPHi6NjL8PgVASNBWIXErncYyDA%2BvpOTg8vqFTqdAjVupUCleX7NNi1MbOsr5Ha9eftbJ2u3RqAQAh%2BdDnqUU9tivUZfYzHByrHjDV5csF54ueDijmaTyInkYqPR1SzNNEED2NVnp6WTFPu4PoaazS0zHFPO0JoqfxSk%2BvKeZpbxA9TVR6OqGIp1u9n3d3tX7rnVy6f7Z8P2dgrlaSDMI5ceR1TYyLAGteROLI5jSOFiKSImJURKSKEV4tj0h1VZuLClcXVT4g8nbt%2FQXdrpi3QzEAAA%3D%3D&t%3Aformdata=H%2F7PyGVbI7Bls5m862Q9GoVVREg%3D%3AH4sIAAAAAAAAAFWPvU7DUAyFrUqojAim7p2dnU5QMSBVKqJjppuLk97o%2FkS2A%2BnEE8ALsDLyNLwH70B%2BKkEtWZY%2Fn2PpfP3A2UsFxGT3xH2nsmSS7JGk9WpUrm0KTRITlY%2FoVIpFajVFU%2FfDeiNCLRdJNQU08bAkT4GiSlsEp8KwLhkbwmCx%2FxvaiGoaEuUDun3A4DoXBe8m0240LR84WRIZNxGX4sfr2%2FvnNv%2BewWwD59a7Xnv%2FpHC5qc2zybyJVbZTdrFa5TC3KSp1qnCV%2F7tvi5qsrjqGiwHiAHGC8Fddo7CYAt4MAdfHgLdjwOYXy0KyWj0BAAA%3D'");

  int res = system (command_bash.c_str());
}


int PoleEmploi::initialize_curl (const char* url)
{
  CURL * curl;
  CURLcode res;
  
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, poleEmploi_curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.90 Safari/537.36");
    
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
    string cookie = create_cookie(); // Réutilise le même cookie que la première requète
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());

     
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      curl_easy_strerror(res);
      fprintf(stderr, " === Error curl ===\n");
      return 1;
    }
    curl_easy_cleanup(curl);
  }
  return 0;
}

void PoleEmploi::extract_type (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;  

  if (node->v.element.tag == GUMBO_TAG_TD &&
      node->parent->v.element.tag == GUMBO_TAG_TR &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->parent->v.element.attributes, "itemtype")))
    {  
      if (strstr(attributes1->value, "employmentType") != NULL &&
	  strstr(attributes2->value, "http://schema.org/JobPosting") != NULL)
	{
	  GumboNode * child = static_cast<GumboNode*>(node->v.element.children.data[0]);
          
	  if (child != NULL && child->v.text.text != NULL )
	    {
	      string type = child->v.text.text;
	      for (int i = 0; i < type.length(); i++)
		{
		  if (type[i] == '\n')
		    {
		      type.erase(i, 1); // erase 1 character at pos i.
		    }
		}
	      tab_offer[num_offer]->add_type(convert_type(type));
	    }
	}
    }
}

void PoleEmploi::extract_date (GumboNode * node, int num_offer)
{
  GumboAttribute * attributes1;
  GumboAttribute * attributes2;

  if (node->v.element.tag == GUMBO_TAG_TD &&
      (attributes1 = gumbo_get_attribute(&node->v.element.attributes, "itemprop")) &&
      (attributes2 = gumbo_get_attribute(&node->v.element.attributes, "headers")))
    {
      if (strstr(attributes1->value, "datePosted") != NULL &&
	  strstr(attributes2->value, "dateEmission") != NULL)
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

string PoleEmploi::convert_type (string type)
{
  if (strstr(type.c_str(), "CDI") != NULL) 
  {
    return "permanent";
  }
  if (strstr(type.c_str(), "CDD") != NULL) 
  {
    return "contract";
  }
  if (strstr(type.c_str(), "Temps Plein") != NULL) 
  {
    return "fulltime";
  }
  if (strstr(type.c_str(), "Temps Partiel") != NULL) 
  {
    return "parttime";
  }
  if (strstr(type.c_str(), "Intérim") != NULL)
  {
    return "temporary";
  }
  if (strstr(type.c_str(), "Freelance") != NULL)
  {
    return "subcontract";
  }
  if (strstr(type.c_str(), "Contrat D´alternance") != NULL ||
      strstr(type.c_str(), "Contrat D´apprentissage") != NULL)
  {
    return "apprenticeship";
  }
  if (strstr(type.c_str(), "Stage") != NULL)
  {
    return "internship";
  }
  return type;
}




/*
int PoleEmploi::curl_post(string url)
{
  CURL * curl;
  CURLcode res;
  
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  
  if(curl) {
    string url2 = "http://candidat.pole-emploi.fr/candidat/rechercheoffres/resultats.composantresultatrechercheoffre.ajouterauclasseur";
    curl_easy_setopt(curl, CURLOPT_URL, url2.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, poleEmploi_curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0");
    
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


    curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookie.txt");
    string cookie = create_cookie(); // Réutilise le même cookie que la première requète
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());

    string post = "'t%3Aac=A_p%2400e2tissier_COMMUNE_33240_50__P__________INDIFFERENT_______________________&t%3Asubmit=%5B%22nombreLignesMax%22%2C%22nombreLignesMax%22%5D&t%3Aformdata=GAizWFGMGFsH6tjv1NJCmKJuWxo%3D%3AH4sIAAAAAAAAAFvzloEVAN3OqfcEAAAA&t%3Aformdata=GWlUjVH2z4rEQ8gJL315qlhvQKw%3D%3AH4sIAAAAAAAAAK2Rv0oDQRDGJweikEJRfIPYbhrTmCqIQvA0YhCRVHubucuG291zd2LORp9AX0CwshRfIoWdhW%2FgA9haWbiXE%2F%2BQSsjANB%2FfML%2BP7%2BENFsZ70LYoBmj9mji26OpH6EYpcXJbwqjMOK7Jfkl%2FrUwbFVlMZaLRKZ47Cw1jE8Yz7i2MeIaO7EWDCVO4IhZxh6wVeZEL2pWY9mtdpFG2cTypvq4%2FfQRQCaEqjH9o0gOukGA1HPJzXk%2B5TupdslInzdzCSiGyQmSdaIiC4GfyjGC5JAunZPs8n3fM1n9jHloj0LnuKFLSOWn05LG%2FGb%2FfPQce%2BAwuIRifwsncEGuYokJNrvhHHng7tixDpoSHVGqkv6mZHCimZC61Yzvl0RSSZpFvr65v7ju9lwCCEJZEKr233S%2FgKz1YLFrDnAjWer8qK9tplhFne8k%2BAQJkSQ%2BEAgAA&nombreLignesMax=100&t%3Aformdata=NlPO6PuXdP%2FmTB9OEL9o09xG%2BEk%3D%3AH4sIAAAAAAAAAFWPT0oDUQzGQ0F0KQo9QdeZvV1JcVEoVKy7Wb15zbRveP9IMjpdeQK9gFuXnsZ7eAdnOgU1EEJ%2B%2Bb7A9%2FkNZ89bqJjsnrjvVNdMUjyQtF6Nyo1NIScxUfmE%2FkuxSq2maJp%2BWG9EqGVNGU08zMhToKjSVsGpMCxqxkwYLPZPQxtRTSZRPqDbBwyuc1HwbjRtjqbZPSdLIsdNxKX4%2FvL69rEuvyYwWcGF9a7XLrcKV6vGPJnCm7grNsou7uYlnNsUlTpVuC7%2F3NdVQ1bnHcPlAHGAOEL4rS4rTMd0t0O6xSndY8r5B1z0wI83AQAA&t%3Aformdata=bF38WMC%2BqOcR1NAKcT%2BRx3ecphg%3D%3AH4sIAAAAAAAAAO2aT0hUQRzHxyVLtIMUbR07GOTB0f2nlkWJZAabikv%2FULR5b2fXp%2B%2B9ec7M05WgLh06VHTrEBSBt7Jr18hDePFQ0T3oGkRFp4Jmdt1dl9ZAWdc3MgsL783M7%2F2%2B8%2F3MYfjxe%2FkVNC5MggmKzWlMxZ9kMhSzzjHMfJsjzk6bxPEIQy6n60OVSyFHho2Rv8msTYjHKICEZiHykBgXAR5mnC4moEkoti0D5lO42OUMJsX6tuh3L9N%2BMfziXAiAHAWtM2geQRu5WThizGCTg%2FIv5wVOfezNybtDsZ%2FLQKqfA7dBw4IBbu6URPFgzhokJ2Qm%2FivTQAzDfkMMIpMPWthOt6Uw970TV1ZaPh959zsEGpKgxSRCB7GHkYM5OJSUzndK5ztTnFputq%2BwIQ6ainnrtLf%2Bre5tlBITM5byDcdizCLuyqt0PPPr6VqZStAOTnzjsa%2BLRJlkX10IykyNHDQXB6a66pFWZm2uh4kH9zCpiCalCKmoJqUIqZgmpQipuCalCKmEJqUIqW5NShFSPZqUIqR6NSlFSJ3SpAJNqqVEKqKLFMqg0lUKZVDpMoUyqHSdQhlUulChDCpdqVAGlS5VKINK1yqUQbXXihXDILn9JB7KWi7iFnENxLbXOZDoGFn91A5urZY7B3ZbUuTGl%2BUfmdcfnu%2BkpOEtSRLJuJhKiY%2FjQUqclHxLD9iWWHIV2T7uePz24z1w%2FM96K0x5QurfX2x9aYjUeic7c4jkV3uE3OgCBV7Nvmy5s0z21HA0j03ZLYRzHEPkLrZhGzvS7PysgDOQodDD0DElCMd3S4SgNe1Ax8pZLoMXCkH5Nh3%2Bb9POkzsPHi6NjL8PgVASNBWIXErncYyDA%2BvpOTg8vqFTqdAjVupUCleX7NNi1MbOsr5Ha9eftbJ2u3RqAQAh%2BdDnqUU9tivUZfYzHByrHjDV5csF54ueDijmaTyInkYqPR1SzNNEED2NVnp6WTFPu4PoaazS0zHFPO0JoqfxSk%2BvKeZpbxA9TVR6OqGIp1u9n3d3tX7rnVy6f7Z8P2dgrlaSDMI5ceR1TYyLAGteROLI5jSOFiKSImJURKSKEV4tj0h1VZuLClcXVT4g8nbt%2FQXdrpi3QzEAAA%3D%3D&t%3Aformdata=H%2F7PyGVbI7Bls5m862Q9GoVVREg%3D%3AH4sIAAAAAAAAAFWPvU7DUAyFrUqojAim7p2dnU5QMSBVKqJjppuLk97o%2FkS2A%2BnEE8ALsDLyNLwH70B%2BKkEtWZY%2Fn2PpfP3A2UsFxGT3xH2nsmSS7JGk9WpUrm0KTRITlY%2FoVIpFajVFU%2FfDeiNCLRdJNQU08bAkT4GiSlsEp8KwLhkbwmCx%2FxvaiGoaEuUDun3A4DoXBe8m0240LR84WRIZNxGX4sfr2%2FvnNv%2BewWwD59a7Xnv%2FpHC5qc2zybyJVbZTdrFa5TC3KSp1qnCV%2F7tvi5qsrjqGiwHiAHGC8Fddo7CYAt4MAdfHgLdjwOYXy0KyWj0BAAA%3D'";
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post.size());
    curl_easy_setopt(curl, CURLOPT_REFERER, url);
     
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      curl_easy_strerror(res);
      fprintf(stderr, " === Error curl ===\n");
      return 1;
    }
    curl_easy_cleanup(curl);
  }
  return 0;
}*/
