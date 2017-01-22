# Anbot - Web Crawler

Author : Jimmy

== TO DO LIST ==

   - WebServer
   - WebSocket


== TO DO LIST SECONDARY ==

 - Remplacer les inputs pour des toggles.


== COMPILATION ==

g++ *.cpp *.hpp -o main -lcurl `pkg-config --cflags --libs gumbo`

g++ webSocket.cc -o websocket -I/net/cremi/jimgouraud/espaces/travail/libnavajo/include -pthread -L/net/cremi/jimgouraud/espaces/travail/libnavajo/lib/ -lnavajo
