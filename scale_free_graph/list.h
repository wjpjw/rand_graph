#ifndef LIST_H_
#define LIST_H_

#define WJP(ptr, type, member) (ptr ? ((type*) (((char*) ptr) - offsetof(type, member))) : NULL)
typedef struct node_wjp{
  struct node_wjp* next;
  struct node_wjp* prev;
}list_node;
static inline void     init(list_node* head){
  head->next = head;
  head->prev = head;
}
static inline void     link(list_node* prev, list_node* next){
  next->prev = prev;
  prev->next = next;
}
static inline void     insert_between(list_node* prev, list_node* next, list_node* it){
  link(it,next);
  link(prev,it);
}  
static inline int          empty (list_node* head)                              {return head->next==head;}
static inline list_node*   begin (list_node* head)                              {return head->next;}
static inline int          not_ended(list_node* head, list_node* it)            {return it!=head;}
static inline void         push_front(list_node* head, list_node* it)           {insert_between(head, head->next, it);}
static inline void         push_back(list_node* head, list_node *it)            {insert_between(head->prev, head, it);}
static inline void         erase(list_node* it)                                 {link(it->prev,it->next);}

#endif
