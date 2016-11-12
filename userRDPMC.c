#include "shim.h"

#define NR_EVENT (2)
char *default_counter_name[NR_EVENT] = {"INSTRUCTION_RETIRED","UNHALTED_CORE_CYCLES"};
hw_event_t *perf_events;

int
main(int argc, char **argv)
{
  pfm_initialize();
  bind_processor(0);
  unsigned long start[10];
  unsigned long end[10];
  memset(start, 0, sizeof(start));
  memset(end, 0, sizeof(end));
  perf_events = shim_create_hw_events(NR_EVENT, default_counter_name);
  int nr_read = read_counters(start, perf_events, NR_EVENT);
  unsigned long now = rdtscp();
  while (rdtscp() - now < 10000)
    ;
  bind_processor(0);
  nr_read = read_counters(end, perf_events, NR_EVENT);
  for (int i=0; i<nr_read; i++) {
    printf(" [%d, %lu, %lu, %lu] \n", i, start[i], end[i], end[i] - start[i]);
  }
  return 0;
}
