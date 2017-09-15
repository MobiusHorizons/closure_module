/* test-closure-standard-c.c */
#include "./deps/closure/closure.h"
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

  closure_t cb = closure_new(callback, &state);

  closure_call(cb, "Hello World!!");
  closure_call(cb, "Lorem");
  closure_call(cb, "Ipsum ...");
  closure_call(cb, "You Get the picture.");

  printf("Our callback was called %d times\n", state.count);
}

