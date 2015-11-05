#include "user_program.h"
#include "stdio.h"
#include "scheduler.h"
#include "constants.h"
#include "cli.h"


void thread1(void)
{
  rpi_printf("Thread 0 starting");
  int a = 0;
  for(a = 0; a < 400; a++) {
    rpi_printf("Thread 0: %d\n", a);
  }
}

void thread2(void)
{
  rpi_printf("Thread 1 starting");
  int a = 0;
  for(a = 0; a < 800; a+=2) {
    rpi_printf("Thread 1: %d\n", a);
  }
}

void thread3(void)
{
  rpi_printf("Thread 2 starting");
  int a = 0;
  for(a = 1;a < 1000; a*=2) {
    rpi_printf("Thread 2: %d\n", a);
  }
}

void thread4(void)
{
  rpi_printf("Thread 3 starting");
  int a = 1;
  for(a = 1; a < 10000; a*=3) {
    rpi_printf("Thread 3: %d\n", a);
  }
}


void main_program(void)
{
    // create_process(thread1, NULL);
    // print_debug("Thread 0 created");
    //
    // create_process(thread2, NULL);
    // print_debug("Thread 1 created");
    //
    // create_process(thread3, NULL);
    // print_debug("Thread 2 created");
    //
    // create_process(thread4, NULL);
    // print_debug("Thread 3 created");
    //
    // bootstrap_scheduler();

    command_line();
}
