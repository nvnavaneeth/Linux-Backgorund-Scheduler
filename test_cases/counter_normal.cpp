#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<sched.h>
#include<sys/time.h>
#include<sys/resource.h>

using namespace std;

long long count_max = 10000000000ll;

int main() {

  rusage usage;
  timeval start,end;

  // Count till count_max
  cout<<"SCHED_OTHER: Counting till : "<<count_max<<endl;
  long long int count = 0;


  // getrusage(RUSAGE_SELF, &usage);
  // start = usage.ru_utime;
  gettimeofday(&start, NULL);
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


  cout<<"SCHED_OTHER: Time taken in usecs: "<<run_time_usec<<endl;

  return 0;
}
