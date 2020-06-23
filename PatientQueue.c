#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "patientqueue.h"
int SIZE;
int lastIndex;
Patient *pointertolast = NULL;

int parentf(int i) {return (i-1)/2;}
int left(int i) {return 2*i+1;}
int right(int i) {return 2*i+2;}


struct q {
	Patient *p;
};

void swap(Patient *q1,Patient *q2){
    int i;
	for(i=0;i<30;i++) q1->name[i] = q2->name[i];
	q1->patientID = q2->patientID;
	q1->severity = q2->severity;
	q1->arrivalTime = q2->arrivalTime;
}

void swap2(PatientQueue *q1,PatientQueue *q2){
    Patient temp;
	swap(&temp,q1->p);
	swap(q1->p,q2->p);
	swap(q2->p,&temp);
}

void percolateUp(PatientQueue *patients,int i){
    int parent = parentf(i);
	if (parent >= 0) { 
        if (patients[i].p->severity > patients[parent].p->severity) { 
            swap2(&patients[i], &patients[parent]);
            percolateUp(patients, parent); 
        } 
    } 
} 

void percolateDown(PatientQueue *patients, int i) 
{ 
    int largest = i; 
    int l = left(i);
    int r = right(i);
  
    if (l < lastIndex && patients[l].p->severity > patients[largest].p->severity) largest = l; 
    if (r < lastIndex && patients[r].p->severity > patients[largest].p->severity) largest = r; 
 
    if (largest != i) { 
        swap2(&patients[i], &patients[largest]); 
        percolateDown(patients,largest); 
    } 
} 

PatientQueue *newPQ(int size){
	SIZE = size;
	lastIndex = -1;
	return NULL;
}

PatientQueue *PQAppend(PatientQueue *q, Patient *p){
	if(q == NULL){
		PatientQueue *new = malloc(SIZE*sizeof(PatientQueue));
		lastIndex = 0;
		new[lastIndex].p = p;
		pointertolast = p;
		return new;
	}
	lastIndex++;
	if(lastIndex==4) {
		lastIndex--;
		return q;
	}
	q[lastIndex].p = p;
	pointertolast = p;
	percolateUp(q,lastIndex);
	return q;
	
}

Patient *PQMaxServe(PatientQueue **q){
	if(PQEmpty(*q)){
		printf("Queue is empty! ");
		return NULL;
	}
	Patient *patient = q[0]->p;
	PatientQueue *patientptr = q[0];
	strcpy(patient->name,patientptr->p->name);
	patient->patientID = patientptr->p->patientID;
	patient->severity = patientptr->p->severity;
	patient->arrivalTime = patientptr->p->arrivalTime;
	if(lastIndex>1) {
		q[0]->p = pointertolast;
		int j = lastIndex-1;
		pointertolast = ((*q)+j)->p;
	}
	else if(lastIndex==1) {
		pointertolast = ((*q)+1)->p;
		q[0]->p = pointertolast;
	}
	percolateDown(*q,0);
	lastIndex--;

	return patient;
}

void printPQ(PatientQueue *q){
	int i;
	if(PQEmpty(q)) printf("* No patients left! Good job! *");
	else for(i=0;i<=lastIndex;i++) printf("+ Patient %s (%d, severity %d)\n", q[i].p->name, q[i].p->patientID, q[i].p->severity);
	
}

int PQEmpty(PatientQueue *q){
	return lastIndex == -1;
}

int PQFull(PatientQueue *q){
	return lastIndex + 1 == SIZE;
}