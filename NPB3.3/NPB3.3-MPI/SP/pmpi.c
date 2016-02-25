/*
@author mnsekh111
HW3
*/

#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>


#define ROOT 0

int taskId,totalTasks;
int * myStats;
int * allStats;

int MPI_Init(int *argc, char ***argv){
	
	int i,j,retVal;
	//Calling the real function
	retVal = PMPI_Init(argc,argv);
		
	//Get the current rank
	PMPI_Comm_rank(MPI_COMM_WORLD, &taskId);

	//Get the total number of processes
	PMPI_Comm_size(MPI_COMM_WORLD, &totalTasks);
		

	//Declaring and initializing the table
	myStats = (int *) calloc(totalTasks, sizeof(int));
	
	if(taskId == ROOT){
		allStats = (int *)malloc(totalTasks * totalTasks* sizeof(int));
	}
	
	return retVal;	
}


/** Inside this function we have to collect statistics based on the source and destination */
int MPI_Isend( void *buf, int count, MPI_Datatype datatype, int dest, int tag,
                      MPI_Comm comm, MPI_Request *request ){

	myStats[dest]++;
	return PMPI_Isend(buf,count,datatype,dest,tag,comm,request);
}

int MPI_Finalize(void){

	int i,j;
	PMPI_Gather(allStats,totalTasks,MPI_INT,myStats,totalTasks,MPI_INT,ROOT,MPI_COMM_WORLD);
	if(taskId == ROOT){
		FILE *fp = fopen("matrix.data","w");
		for(i=0;i<totalTasks;i++){
			for(j=0;j<totalTasks;j++){
				fprintf(fp,"%d ",allStats[i*totalTasks+j]);
			}
			fprintf(fp,"\n");	
		}
		fclose(fp);
	}

	PMPI_Finalize();
}

