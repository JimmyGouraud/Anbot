#include "website.hpp"
#include <algorithm>
using namespace std;


static size_t curl_callback (void *data, size_t size, size_t nmemb, void *pointer)
{
  ((string*) pointer)->append((char*) data, size * nmemb);
  return size * nmemb;
}

Website::~Website()
{
  tab_url.clear();
  for (unsigned i = 0; i < tab_offer.size(); ++i) {
    delete tab_offer[i];
  }
  remove("cookie.txt");
}

string Website::get_website()
{
  return this->website;
}

Offer* Website::get_offer(unsigned i)
{
  return tab_offer[i];
}

unsigned Website::get_nb_offers()
{
  return tab_offer.size();
}


unsigned Website::add_offer ()
{
  tab_offer.push_back(new Offer());
  return tab_offer.size() - 1;
}

void Website::display_offers()
{
  for (unsigned i = 0 ; i < tab_offer.size(); ++i) {  
    cout << "Offer N°" << i+1 << endl;
    tab_offer[i]->display();
  }
}


int Website::initialize_curl (const char* url)
{
  CURL * curl;
  CURLcode res;
  
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/42.0.2311.90 Safari/537.36");
    
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
   
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


void Website::run ()
{
  GumboOutput * output;
  unsigned initial_size = tab_url.size();
  bool research_others_pages = true;
  
  for (unsigned i = 0; i < tab_url.size(); ++i) {
    if (i > initial_size) {
      research_others_pages = false;
    }

    this->current_url = tab_url[i];
    
    cout << "\033[32m - " << this->current_url << "\033[00m" << endl;

    if (initialize_curl(this->current_url.c_str()) == 0) {      
      output = gumbo_parse(data.c_str());
      extract_data(output->root, research_others_pages);
      gumbo_destroy_output(&kGumboDefaultOptions, output);
    }
    
    data.clear();
  }
  
  sort_tab_offer();
}

void Website::extract_data (GumboNode * node, bool research_others_pages)
{
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }

  extract_offers(node);
  if (research_others_pages) {
    extract_pages(node);
  }
  
  GumboVector * children = &node->v.element.children;
  for (unsigned i = 0; i < children->length; ++i) {
    extract_data(static_cast<GumboNode*>(children->data[i]), research_others_pages);
  }
}




int Website::find_offer(string url)
{
  for (unsigned i = 0; i < tab_offer.size(); ++i) {
    if (strstr(tab_offer[i]->get_url().c_str(), url.c_str()) != NULL) {
      return i;
    }
  }
  
  return -1;
}

bool sort_offers (Offer* i, Offer* j)
{
  return (i->get_date() < j->get_date());
}

void Website::sort_tab_offer(void)
{
  std::sort (tab_offer.begin(), tab_offer.end(), sort_offers);
}
