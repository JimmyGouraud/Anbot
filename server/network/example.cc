//********************************************************
/**
 * @file  example2.cc 
 *
 * @brief libnavajo example code.
 *
 * @author T.Descombes (descombes@lpsc.in2p3.fr)
 *
 * @version 1  
 * @date 27/01/15
 */
//********************************************************

#include <signal.h> 
#include <string.h> 
#include "libnavajo/libnavajo.hh"
#include "libnavajo/LogStdOutput.hh"

WebServer *webServer = NULL;

void exitFunction(int dummy)
{
  if (webServer != NULL) webServer->stopService();
}

class MyDynamicRepository : public DynamicRepository
{
  
  class MyDynamicPage : public DynamicPage
  {/*
  protected:
    bool isValidSession(HttpRequest* request)
      {
	void *myAttribute = request->getSessionAttribute("username");          
	return myAttribute != NULL;
	}*/
  };    
  
  
  class Bouh: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
      {
	return fromString("{\"error\" : You don't have a valid token, retry please\"}", response);
      }  
  } bouh;
  
  class Controller: public MyDynamicPage
  {
    bool getPage(HttpRequest* request, HttpResponse *response)
      {
	std::cout << " in ! " << std::endl;
	response->forwardTo("index.php");
        return true;
      }
  } controller;
     
public:
  MyDynamicRepository() : DynamicRepository()
    {
      add("index.html", &controller);
      add("bouh.txt", &bouh);
    }
};

/***********************************************************************/

int main()
{
  // connect signals
  signal(SIGTERM, exitFunction);
  signal(SIGINT, exitFunction);
  
  NVJ_LOG->addLogOutput(new LogStdOutput);
  webServer = new WebServer;

  LocalRepository * myLocalRepo = new LocalRepository("", "../../client");
  webServer->addRepository(myLocalRepo);

  MyDynamicRepository myRepo;
  webServer->addRepository(&myRepo);

  webServer->startService();

  webServer->wait();
  
  LogRecorder::freeInstance();
  return 0;
}


