#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sys/time.h>
#include<sys/resource.h>

using namespace std;


int main(int argc, char** argv) {
  if (argc == 1) {
    cout<<"Err: Filename not provided";
    return 0;
  }

  char* file_name = argv[1];
  cout<<"SCHED_OTHER: Writing to file: "<<file_name<<endl;

  fstream file;
  file.open(file_name, ios::out);

  if (!file) {
    cout<<"Error in creating/opening file"<<endl;
    return 0;
  }
  rusage usage;
  timeval start,end;

  // Num of characters to write.
  long long int n = 300000000 /*300 million*/;

  // getrusage(RUSAGE_SELF, &usage);
  // start = usage.ru_utime;
  gettimeofday(&start, NULL);
  for (long long int i = 0; i<n; ++i) {
    file<<"A";
  }
  // getrusage(RUSAGE_SELF, &usage);
  // end = usage.ru_utime;
  gettimeofday(&end, NULL);

  long long int run_time_sec = (end.tv_sec - start.tv_sec);
  long long int run_time_usec = run_time_sec*1000*1000ll + (end.tv_usec-start.tv_usec);


  cout<<"SCHED_OTHER: Time taken in usecs: "<<run_time_usec<<endl;

  return 0;
}
