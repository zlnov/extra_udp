#include "extra_udp.hpp"
#include <chrono>
#include <thread>
#include <cstring>
#include <iostream>
#include <vector>
int main(){

  printf("starting server 2\n");
  Node my_addr;
  my_addr.host = std::string("127.0.0.1");
  my_addr.port = 23001;
  my_addr.is_ipv6 = false;
  Extra_UDP my_pc(my_addr);

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1000ms);

  //ssize_t recv(Node *src, bool want_sender_info, void* store_location);
  char * buffer = (char*)malloc(512*sizeof(char));
  printf ("Server 2 started waiting\n");
  while(true){
    Node* recv_info = nullptr;
    ssize_t count = my_pc.recv_existing(recv_info, true, buffer, 512);
    if (count > 0){
      buffer[count] = '\0';
      printf("sv2 received from %s:%d(hash:%lu): %s\n", recv_info->host.c_str(), recv_info->port, recv_info->get_hash(), buffer);
      int a = my_pc.send(recv_info, buffer, count);
      if(!strcmp("the end.", buffer)){
        break;
      }
    }
    delete (recv_info);
    std::this_thread::sleep_for(200ms);
  }
  free(buffer);

  printf("Server 2 close \n");
}
