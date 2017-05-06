#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <math.h>

using std::cout;
using std::cerr;
using std::endl;

//A global variable accessible to all threads.
int slices, thread_count;
double x1, x2, n, h;
double answer=0;
pthread_mutex_t mymutex;

void* Hello(void* rank);    /* The function for each thread to run */

int main(int argc, char** argv) {
    pthread_t* thread_handles;

    //get the number of threads from the command line
    if (argc < 2) {
        cerr << "Error, usage: " << endl;
        cerr << "    " << argv[0] << " <number of threads>" << endl;
        exit(1);
    }

   thread_count = atoi(argv[1]);
	slices = atoi(argv[2]);
	x1 = atof(argv[3]);
	x2 = atof(argv[4]);
	
	//double temp[thread_count];
	//answer = temp;

	
	//double approximation = (sin(x1) + sin(x2)) / 2.0;
	h = (x2 - x1) / (thread_count*slices); //where x2 > x1
//   thread_handles = malloc(thread_count * sizeof(pthread_t));
   thread_handles = new pthread_t[thread_count];

   pthread_mutex_init(&mymutex, NULL);

   long thread;
   for (thread = 0; thread < thread_count; thread++) {
       pthread_create(&thread_handles[thread], NULL, Hello, (void*)thread);
   }

//   cout << "Hello from the main thread" << endl;
    //printf("Hello from the main thread!\n");

	

   for (thread = 0; thread < thread_count; thread++) {
       pthread_join(thread_handles[thread], NULL);
   }
	//approximation = h * approximation;
   free(thread_handles);

	double answers=0;
	for(int i=0;i<thread_count;i++) {
	//	//printf("%lf \n",answer[i]);
	//	answers+=answer[i];
	}

	answer = (answer*h)/2;
	printf("%lf \n",answer);

   return 0;
}

void* Hello(void* rank) {
    long my_rank = (long)rank;

    //cout << "Hello from thread " << my_rank << " of " << thread_count << endl;
    //printf("Hello from thread %ld of %d\n", my_rank, thread_count);

	

	//double h = (x2 - x1) / (my_rank+1); //where x2 > x1
	double start = x1+(my_rank)*(x2-x1)/thread_count;
	double fin = x1+(my_rank+1)*(x2-x1)/thread_count;
	//double approximation = (sin(x1) + sin(x2)) / 2.0;

	//double approximation = 0;
	double approximation = sin(start);

	for (int i = 1; i <= slices-1; i++) {   
		double x_i = start + i * h;
		//printf("Thread #%ld \nSlice #%ld \nSlice: %lf\n\n",my_rank,slices,sin(x_i));
 	  approximation += 2*sin(x_i);
	}
	
	approximation += sin(fin);
	//approximation = approximation/2;
	//approximation = h * approximation;
	
	//printf("Thread #%ld \nApprox: %lf\n\n",my_rank,approximation);


	pthread_mutex_lock(&mymutex);
	answer += approximation;
	pthread_mutex_unlock(&mymutex);
	
    return NULL;
}

