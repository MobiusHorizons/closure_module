/* test-closure.module.c */
package "main";

import closure from "./deps/closure/closure.module.c";
#include <stdio.h>

struct state {
  int count;
};

void * callback(void * ctx, void * arg){
  if (ctx == NULL) return NULL;
  struct state * state = (struct state *)ctx;
  state->count++; // increment invocation counter

  printf("callback has been called %d times, Message was '%s'\n", state->count, (char*) arg);
  return NULL;
}

int main(){
  struct state state = {
    .count = 0,
  };

  closure.t cb = closure.new(callback, &state);

  closure.call(cb, "Hello World!!");
  closure.call(cb, "Lorem");
  closure.call(cb, "Ipsum ...");
  closure.call(cb, "You Get the picture.");

  printf("Our callback was called %d times\n", state.count);
}
