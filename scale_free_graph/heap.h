#ifndef HEAP_WJP_H_
#define HEAP_WJP_H_

/*
  Min-heapify operations on an array
  1. include a priority member in any struct you want to use as a pq node.
  2. maintain a heap struct.   

  Author: Jipeng
  Date:   Oct 29, 2015 
*/
typedef struct wjp_heap{
  double** A;      // A[i] stores the pointers to priorities
  int    size;   // size of heap 
  int    len;    // length of allocated memory
}heap;
#define CO(ptr, type) (ptr ? ((type*) (((char*) ptr) - offsetof(type, priority))) : NULL)
#define PO(c) (&c.priority)
static inline int             parent(int i) {return (i+1)/2-1;}   
static inline int             left(int i)   {return 2*i+1;}       
static inline int             right(int i)  {return 2*i+2;}
static inline heap*           create_heap(){
  heap* tmp = (heap*)malloc(sizeof(heap));
  tmp->len  = 1000;
  tmp->size = 0;
  tmp->A    = (double**)malloc(sizeof(int*)*tmp->len);
  return tmp;
}
static inline void            extend_heap(heap*h){
  if(h->size==h->len){
    h->len*=2;
    h->A=(double**)realloc(h->A,sizeof(int*)*h->len);
    assert(h->A);
  }  
}  
static inline void            heapify_node(heap*h, int i){
  if(i<0)return;
  int l=left(i), r=right(i), smallest=i;
  if(l < h->size && *h->A[l]<*h->A[i]){
    smallest=l;
  }  
  if(r < h->size && *h->A[r]<*h->A[smallest]){
    smallest=r;
  }  
  if(smallest!=i){
    double* tmp=h->A[i];
    h->A[i]=h->A[smallest];
    h->A[smallest]=tmp;
    heapify_node(h,smallest);
  }  
}
static inline void            heapify(heap*h){           
  for(int i=h->size-1;i>=0;i--){
    heapify_node(h, i);
  }  
}  
static inline void            hh_insert(heap*h, double*p){   //buttom-up heapify
  extend_heap(h);
  h->A[h->size++]=p;
  heapify(h);
}
static inline int             hh_empty(heap*h){
  return h->size==0;
}  
static inline double*         hh_root(heap*h){             //top-down heapify
  if(hh_empty(h))return NULL;
  double* tmp=h->A[0];
  h->A[0]=h->A[h->size-1];
  h->size--;
  heapify_node(h,0);
  return tmp;
}  
static inline void            hh_print(heap*h){
  for(int i=0;i<h->size;i++){
    printf("%f,", *h->A[i]);
  }
  printf("\n");
}  
#endif
