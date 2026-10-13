#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int temp[frames], count = 0, faults = 0, hits = 0;

    for(int i = 0; i < frames; i++)
        temp[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) {
                found = 1;
                hits++;
                break;
            }
        }

        if(!found) {
            temp[count] = pages[i];
            count = (count + 1) % frames;
            faults++;
        }
    }

    printf("\nFIFO Page Faults: %d", faults);
    printf("\nFIFO Page Hits: %d", hits);
    printf("\nFIFO Hit Ratio: %.2f%%\n", (float)hits / n * 100);
}

void lru(int pages[], int n, int frames) {
    int temp[frames], time[frames], faults = 0, hits = 0;

    for(int i = 0; i < frames; i++)
        temp[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0, pos;

        for(int j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) {
                found = 1;
                hits++;
                time[j] = i;
                break;
            }
        }

        if(!found) {
            if(i < frames)
                pos = i;
            else {
                int min = time[0];
                pos = 0;

                for(int j = 1; j < frames; j++) {
                    if(time[j] < min) {
                        min = time[j];
                        pos = j;
                    }
                }
            }

            temp[pos] = pages[i];
            time[pos] = i;
            faults++;
        }
    }

    printf("\nLRU Page Faults: %d", faults);
    printf("\nLRU Page Hits: %d", hits);
    printf("\nLRU Hit Ratio: %.2f%%\n", (float)hits / n * 100);
}

void optimal(int pages[], int n, int frames) {
    int temp[frames], faults = 0, hits = 0;

    for(int i = 0; i < frames; i++)
        temp[i] = -1;

    for(int i = 0; i < n; i++) {
        int found = 0;

        for(int j = 0; j < frames; j++) {
            if(temp[j] == pages[i]) {
                found = 1;
                hits++;
                break;
            }
        }

        if(!found) {
            int pos = -1;

            if(i < frames)
                pos = i;
            else {
                int farthest = i;

                for(int j = 0; j < frames; j++) {
                    int k;

                    for(k = i + 1; k < n; k++) {
                        if(temp[j] == pages[k])
                            break;
                    }

                    if(k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }

                if(pos == -1)
                    pos = 0;
            }

            temp[pos] = pages[i];
            faults++;
        }
    }

    printf("\nOptimal Page Faults: %d", faults);
    printf("\nOptimal Page Hits: %d", hits);
    printf("\nOptimal Hit Ratio: %.2f%%\n", (float)hits / n * 100);
}

int main() {
    int n, frames;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter reference sequence: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of memory frames: ");
    scanf("%d", &frames);

    printf("\n--- Page Replacement Report ---\n");

    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
