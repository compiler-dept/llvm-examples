#include <stdio.h>
#include "wrap.h"
#include "event.h"

int main(){
  struct position_event event;
  event.x = 10;
  event.y = 20;
  add(&event);
  printf("%d\n", event.z);
}
