#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

// Mutex locks
pthread_mutex_t rwlock,lock;

// Thread functions for reader and writer 
void *reader_thread(void *no);
void *writer_thread(void *no);

// The read count
int readcount;

// The shared data
int data;

// Main function
void main(){

	// Declare the variables for the program
	int res,nord,nowrt,i;
	int *arg;
	printf("\n\t\t\t\t\t\t\t\t Reader Writer Problem");
	printf("\n\n\t\t\t\tEnter the number of readers: ");
	scanf("%d",&nord);
	printf("\t\t\t\tEnter the number of writers: ");
	scanf("%d",&nowrt);

	// Create threads
	pthread_t reader,writer;
	
	// Initialize the Mutexes;
	res =  pthread_mutex_init(&rwlock, NULL);
	if (res != 0) {
		printf("\nERROR :: Semaphore initialization failed");
		printf("\nERROR :: Failed to proceed");
		exit(EXIT_FAILURE);
	}
	res = pthread_mutex_init(&lock, NULL);
	if (res != 0) {
		printf("\nERROR :: Mutex initialization failed");
		printf("\nERROR :: Failed to proceed");
		exit(EXIT_FAILURE);
	}

	// Initialize the readcount
	readcount = 0;
	
	// Create read threads
	printf("\n\t\t\t\t\t\t\t\tCreating Reading Threads");
	for(i=1;i<=nord;i++){		
		printf("\n\t\t\t\t\t\t\t    Reader R00%d succesfully created",i);
		arg = (int *) malloc(sizeof(int));
		*arg = i;
		res = pthread_create(&reader,NULL,reader_thread,arg);
		if (res != 0) {
			printf("\n\t\t\t\t\t\t\tERROR :: Thread Creation failed");
			printf("\n\t\t\t\t\t\t\tERROR :: Failed to proceed");
			exit(EXIT_FAILURE);
		}	
	}

	// Create writer threads	
	printf("\n\n\t\t\t\t\t\t\t\tCreating Writer Threads");
	for(i=1;i<=nowrt;i++){		
		printf("\n\t\t\t\t\t\t\t    Writer W00%d successfully created",i);	
		arg = (int *) malloc(sizeof(int));
		*arg = i;
		res = pthread_create(&writer,NULL,writer_thread,arg);	
		if (res != 0) {
			printf("\n\t\t\t\t\t\t\tERROR :: Thread Creation failed");
			printf("\n\t\t\t\t\t\t\tERROR :: Failed to proceed");
			exit(EXIT_FAILURE);
		}	
	}
	
	// Waiting for the threads to finish
	res = pthread_join(reader, NULL);		
	if (res != 0) {
		printf("\nERROR :: Thread Waiting failed");
		printf("\nERROR :: Failed to proceed");
		exit(EXIT_FAILURE);
	}	
	res = pthread_join(writer, NULL);		
	if (res != 0) {
		printf("\nERROR :: Thread Waiting failed");
		printf("\nERROR :: Failed to proceed");
		exit(EXIT_FAILURE);
	}	
}

// Function for the reader thread
void *reader_thread(void *no){
	int *num = (int*) no;
	while(1){
		// Entry section
		int temp = rand()%2,i;
		if (temp == 0)
			temp = 2;
		sleep(temp);

		pthread_mutex_lock(&lock);
			// Critical section for readers
			readcount++;
			if(readcount == 1)		
				pthread_mutex_lock(&rwlock);
		pthread_mutex_unlock(&lock);

		// The critical section for reader and writers
		//printf("\n\t\t\tReader R00%d : Entered in READER ",*num);
		// Read the data
		sleep(temp);
		temp = data;
		printf("\n\t\t\t\tReader R00%d read data = %d ",*num, temp);
		//printf("\n\t\t\tReader R00%d : Exited from READER ",*num);

		pthread_mutex_lock(&lock);
			// Critical section for readers
			readcount--;
			if(readcount == 0)		
				pthread_mutex_unlock(&rwlock);
		pthread_mutex_unlock(&lock);
		// Remainder section
	}	
}

// Function for the writer thread
void *writer_thread(void *no){
	int *num = (int*) no;
	while(1){
		// Entry section
		int temp = rand()%7,i;
		if (temp == 0)
			temp = 2;
		sleep(temp);

		pthread_mutex_lock(&rwlock);
			// The Critical section for readers ad writers
			//printf("\n\t\t\t\t\t\t\t\t\t\t\t\tWriter W00%d : Entered in WRITER ",*num);
			// Write the data
			data = temp * 5;
			printf("\n\t\t\t\t\t\t\t\t\t\t\t     Writer W00%d changed the data to %d",*num, data );		
			//printf("\n\t\t\t\t\t\t\t\t\t\t\t\tWriter W00%d : Exited from WRITER ",*num);
		pthread_mutex_unlock(&rwlock);		
		// Remainder section
	}	
}

