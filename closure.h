#ifndef _closure_
#define _closure_

typedef struct {
  void * ctx;
  void * (*fn)(void * ctx, void * arg);
} closure_closure_t;
typedef closure_closure_t closure_t;
closure_closure_t closure_new(void * (*fn)(void*, void*), void * ctx);
void * closure_call(closure_closure_t c, void * arg);

#endif
