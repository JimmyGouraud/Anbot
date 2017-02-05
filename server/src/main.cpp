#include "website.hpp"
#include "research.hpp"
#include "create_html.hpp"

void init_tab_website (std::vector<Website *> * tab_website, Research * research)
{
  tab_website->push_back(new Indeed(research));
  
  tab_website->push_back(new Jobisjob(research));

  tab_website->push_back(new PoleEmploi(research));
  
  //tab_website->push_back(new Research("www.optioncarriere.com", "recherche/emplois?", "s=", "", "l=", "", ""));
}


int main (int argc, char *argv[])
{
  ofstream file("offers.php", ios::trunc);
  ofstream file2("cookie.txt", ios::trunc);

  Research * research = new Research("patissier",
				     "Saint-Andr%C3%A9-de-Cubzac+(33240)",
				     "50",
				     "vendeur+vendeuse+livreur+BTP+caisse+caisses+caissier+caissière");
  
  std::vector<Website *> tab_website;

  init_tab_website(&tab_website, research);
 
  for (unsigned i = 0; i < tab_website.size(); i++)
  {
    cout << " ===== " << tab_website[i]->get_website() << " ===== " << endl;
    tab_website[i]->run();
    //tab_website[i]->display_offers();
  }
  
  generate_html(&tab_website);

  for (unsigned i = 0; i < tab_website.size(); i++)
  {
    delete tab_website[i];
  }
  
  return 0;
}

