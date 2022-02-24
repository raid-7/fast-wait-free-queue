#ifndef LPRQ_H
#define LPRQ_H

#ifdef LPRQ

#include "align.h"
#include "hzdptr.h"

#define EMPTY ((void *) -1)

#ifndef LPRQ_RING_SIZE
#define LPRQ_RING_SIZE (1ull << 12)
#endif

typedef struct RingNode {
  volatile uint64_t val;
  volatile uint64_t idx;
  uint64_t pad[14];
} RingNode DOUBLE_CACHE_ALIGNED;

typedef struct RingQueue {
  volatile int64_t head DOUBLE_CACHE_ALIGNED;
  volatile int64_t tail DOUBLE_CACHE_ALIGNED;
  struct RingQueue *next DOUBLE_CACHE_ALIGNED;
  RingNode array[LPRQ_RING_SIZE];
} RingQueue DOUBLE_CACHE_ALIGNED;

typedef struct {
  RingQueue * volatile head DOUBLE_CACHE_ALIGNED;
  RingQueue * volatile tail DOUBLE_CACHE_ALIGNED;
  int nprocs;
} queue_t;

typedef struct {
  RingQueue * next;
  hzdptr_t hzdptr;
} handle_t;

#endif

#endif /* end of include guard: LPRQ_H */
