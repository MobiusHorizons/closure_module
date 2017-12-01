typedef struct {
  void * ctx;
  void * (*fn)(void * ctx, void * arg);
} closure_t;

closure_t closure_new(void * (*fn)(void*, void*), void * ctx){
  return (closure_t){ ctx, fn };
}

void * closure_call(closure_t c, void * arg){
  return c.fn(c.ctx, arg);
}
