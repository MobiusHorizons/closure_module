export
typedef struct {
  void * ctx;
  void * (*fn)(void * ctx, void * arg);
} closure_t;
export typedef closure_t t;

export
closure_t new(void * (*fn)(void*, void*), void * ctx){
  return (closure_t){ ctx, fn };
}

export
void * call(closure_t c, void * arg){
  return c.fn(c.ctx, arg);
}
