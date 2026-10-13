#include <stdio.h>

#define MAX 10

void firstFit(int jobs[], int m, int blocks[], int n) {
    int allocated[MAX];
    int rem[MAX];

    for (int i=0; i<m; i++)
        allocated[i] = -1;

    for (int i=0; i<n; i++)
        rem[i] = blocks[i];

    for (int i=0; i<m; i++) { // each job i
        for (int j=0; j<n; j++) { // each block j
            if (rem[j] >= jobs[i]) {
                allocated[i] = j;
                rem[j] -= jobs[i];
                break;
            }
        }
    }

    printf("\n---- FIRST FIT ----\n");

    for (int i=0; i<m; i++) {
        if (allocated[i] != -1) {
            printf("Job %i (size %i) allocated -> Block %i\n", i+1, jobs[i], allocated[i]+1);
        }
        else {
            printf("Job %i (size %i) -> DENIED\n", i+1, jobs[i]);
        }
    }
}


void bestFit(int jobs[], int m, int blocks[], int n) {
    int allocated[MAX];
    int rem[MAX];

    for (int i=0; i<m; i++)
        allocated[i] = -1;

    for (int i=0; i<n; i++)
        rem[i] = blocks[i];

    for (int i=0; i<m; i++) { // each job i
        int best = -1;

        for (int j=0; j<n; j++) { // each block j
            if (rem[j] >= jobs[i]) {
                if (best == -1 || rem[j] < rem[best]) {
                    best = j;
                }
            }
        }

        if (best != -1) {
            allocated[i] = best;
            rem[best] -= jobs[i];
        }
    }

    printf("\n---- BEST FIT ----\n");

    for (int i=0; i<m; i++) {
        if (allocated[i] != -1) {
            printf("Job %i (size %i) allocated -> Block %i\n", i+1, jobs[i], allocated[i]+1);
        }
        else {
            printf("Job %i (size %i) -> DENIED\n", i+1, jobs[i]);
        }
    }
}


void worstFit(int jobs[], int m, int blocks[], int n) {
    int allocated[MAX];
    int rem[MAX];

    for (int i=0; i<m; i++)
        allocated[i] = -1;

    for (int i=0; i<n; i++)
        rem[i] = blocks[i];

    for (int i=0; i<m; i++) { // each job i
        int worst = -1;

        for (int j=0; j<n; j++) { // each block j
            if (rem[j] >= jobs[i]) {
                if (worst == -1 || rem[j] > rem[worst]) {
                    worst = j;
                }
            }
        }

        if (worst != -1) {
            allocated[i] = worst;
            rem[worst] -= jobs[i];
        }
    }

    printf("\n---- WORST FIT ----\n");

    for (int i=0; i<m; i++) {
        if (allocated[i] != -1) {
            printf("Job %i (size %i) allocated -> Block %i\n", i+1, jobs[i], allocated[i]+1);
        }
        else {
            printf("Job %i (size %i) -> DENIED\n", i+1, jobs[i]);
        }
    }

}


int main() {
    int m, n;

    printf("Enter number of jobs: ");
    scanf("%i", &m);

    printf("Enter number of blocks: ");
    scanf("%i", &n);

    int jobs[MAX];
    int blocks[MAX];

    printf("Enter required memory for each job: ");
    for (int i=0; i<m; i++) {
        scanf("%i", &jobs[i]);
    }

    printf("Enter available memory blocks: ");
    for (int i=0; i<n; i++) {
        scanf("%i", &blocks[i]);
    }

    firstFit(jobs, m, blocks, n);
    bestFit(jobs, m, blocks, n);
    worstFit(jobs, m, blocks, n);
}
