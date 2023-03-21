#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record {
  void *ptr;              // address of the allocated memory
  size_t size;            // size of the allocated memory
  int line_num;           // line number, at which a call to malloc or calloc happens
  const char *file_name;  // name of the file, in which the call to malloc or calloc happens
};

struct Record records[MAX_RECORDS + 1];

int len = 0;
void *recorded_malloc(size_t size, int line, const char *file) {
  if(size == 0) return NULL;
  void *ptr = malloc(size);
  if (ptr != NULL) {
    // record this allocation
    len++;
    records[len].ptr = ptr;
    records[len].size = size;
    records[len].line_num = line;
    records[len].file_name = file;
  }
  return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line, const char *file) {
  if(cnt * each_size == 0) return NULL;
  void *ptr = calloc(cnt, each_size);
  if (ptr != NULL) {
    // record this allocation
    len++;
    records[len].ptr = ptr;
    records[len].size = cnt * each_size;
    records[len].line_num = line;
    records[len].file_name = file;
  }
  return ptr;
}

void recorded_free(void *ptr, int line, const char *file) {
  // ...
  // for(int i = 1; i <= len; ++i)
  // {
  //   printf("line: %p  ",(void *)records[i].ptr);
  // }
  // printf("\n");
  if(ptr == NULL)return;
  int flag = 0;
  //printf("LINE:%d\n",line);
  for(int i = 1; i <= len; ++i)
  {
    if(records[i].ptr == ptr)
    {
      records[i].ptr = NULL;
      flag = 1;
      free(ptr);
      break;
    }
  }
  if (flag == 0) printf("Invalid free in file %s, line %d\n", file, line);
  return;
}

#define malloc(SIZE) recorded_malloc(SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE) recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

void check_leak(void) __attribute__((destructor));

void check_leak(void) {
  // Traverse your array to see whether any allocated memory is not freed.
  printf("Summary:\n");
  int cnt = 0;
  long long sum = 0;
  for(int i = 1; i <= len; ++i)
  {
    if(records[i].ptr == NULL) continue;
    printf("%ld bytes memory not freed (allocated in file %s, line %d)\n", records[i].size, records[i].file_name, records[i].line_num);
    cnt++;
    sum += records[i].size;
  }
  if(cnt != 0) printf("%d allocation records not freed (%lld bytes in total).\n", cnt, sum);
  else printf("All allocations have been freed.\n");
}

#endif