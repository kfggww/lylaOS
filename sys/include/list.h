#ifndef _LIST_H_
#define _LIST_H_

struct list_head {
    struct list_head *next;
    struct list_head *prev;
};

#define LIST_HEAD_INIT(name)                                                   \
    {                                                                          \
        (&name), (&name)                                                       \
    }
#define LIST_HEAD(name)      struct list_head name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(name) ((name).next) = ((name).prev) = (&(name))

static inline void list_add(struct list_head *node, struct list_head *head)
{
    node->next = head->next;
    node->prev = head;
    head->next = node;
    node->next->prev = node;
}

static inline int list_empty(struct list_head *head)
{
    return (head == 0) || (head->next == head->prev && head->next == head);
}

static inline struct list_head *list_del_prev(struct list_head *head)
{
    if (list_empty(head))
        return 0;
    struct list_head *res = head->prev;
    head->prev = res->prev;
    res->prev->next = head;
    res->next = res;
    res->prev = res;
    return res;
}

#define list_for_each(pos, head)                                               \
    for (struct list_head *pos = (head)->next; pos != head; pos = (head)->next)

#endif