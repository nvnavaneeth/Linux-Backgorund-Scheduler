#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sched.h>
#include<sys/time.h>
#include<sys/resource.h>

using namespace std;

#ifndef SCHED_BACKGROUND
#define SCHED_BACKGROUND 4
#endif

long long count_max = 10000000000ll;

int main() {
  // Change scheduling policy to SCHED_BACKGROUND.
  sched_param sch_param = {0};
  int ret_val = sched_setscheduler(0, SCHED_BACKGROUND, &sch_param);

  if (ret_val < 0) {
    cout<<"Error in changing policy";
    return 0;
  }

  rusage usage;
  timeval start,end;

  // Count till count_max
  cout<<"SCHED_BACKGROUND: Counting till : "<<count_max<<endl;
  long long int count = 0;


  // getrusage(RUSAGE_SELF, &usage);
  // start = usage.ru_utime;
  gettimeofday(&end, NULL);
  while(count < count_max) {
    count +=1;
    // Following statement prevents the compiler from optimizing out the while loop.
    asm("");
  }
  // getrusage(RUSAGE_SELF, &usage);
  // end = usage.ru_utime;
  gettimeofday(&end, NULL);

  long long int run_time_sec = (end.tv_sec - start.tv_sec);
  long long int run_time_usec = run_time_sec*1000*1000ll + (end.tv_usec-start.tv_usec);


  cout<<"SCHED_BACKGROUND: Time taken in usecs: "<<run_time_usec<<endl;

  return 0;
}
