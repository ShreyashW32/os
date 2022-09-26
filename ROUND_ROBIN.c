#include <stdio.h>
#include <stdlib.h>

struct process {
  int arrival, end, start, id, tat, wt, service;
  int started;
};

void Print(struct process pro[], int n, int ST[]) {
  printf("ProcessId \t AT \t ST \t CT \t TAT \t WT");

  for (int i = 0; i < n; i++) {
    printf("\n     %d \t\t %d \t\t %d \t\t %d\t\t %d \t\t %d", pro[i].id,
           pro[i].arrival, ST[i], pro[i].end, pro[i].tat, pro[i].wt);
  }
}

int main(void) {

  // Taking Input the Number of Process and time Quantum
  int n;
  int totalWT = 0, totalTAT = 0;
  printf("Enter the number of processes : ");
  scanf("%d", &n);

  int loopCTR = n;
  struct process pro[n];

  int TQ;
  printf("Enter the time quantum : ");
  scanf("%d", &TQ);

  // Taking an integer array to store the original service times to calculate
  // TAT and WT
  int ST[n];

  // Taking Input for all processes
  for (int i = 0; i < n; i++) {
    printf("\nEnter Arrival and Service time for Process %d --->", i + 1);
    pro[i].id = i + 1;
    printf("\nEnter Arrival Time : ");
    scanf("%d", &pro[i].arrival);

    printf("\nEnter Service Time : ");
    scanf("%d", &pro[i].service);
    ST[i] = pro[i].service;

    pro[i].started = 0;
    pro[i].start = -1;
    pro[i].end = -1;
  }

  // looping while Service Time of all processes become 0
  int procCTR = 0;
  int totalT = 0;

  int time = 0;

  while (loopCTR) {
    if (pro[procCTR % n].started == 0) {
      pro[procCTR % n].start = time;
    }

    if (pro[procCTR % n].service <= TQ && pro[procCTR % n].service > 0) {
      totalT += pro[procCTR % n].service;
      time += pro[procCTR % n].service;
      pro[procCTR % n].service = 0;

      loopCTR--;
      pro[procCTR % n].end = time;
    } // If
    else if (pro[procCTR % n].service > TQ) {
      pro[procCTR % n].service -= TQ;
      totalT += TQ;
      time += TQ;
    } // Else if

    procCTR++;
  } // Loop End

  // TAT and WT
  for (int i = 0; i < n; i++) {
    // if(i==n-1){
    //   pro[i].tat += TQ;
    //   pro[i].wt += TQ;
    //   pro[i].end += TQ;
    // }
    pro[i].tat = pro[i].end - pro[i].arrival;
    pro[i].wt = pro[i].tat - ST[i];

    totalTAT += pro[i].tat;
    totalWT += pro[i].wt;
  }

  Print(pro, n, ST);

  float avgTAT = totalTAT * 1.0 / n;
  float avgWT = (totalWT)*1.0 / n;

  printf("\nAvg TAT : %f", avgTAT);
  printf("\nAvg WT : %f", avgWT);
  return 0;
}
