#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Process {
    int id, arrival, burst, remaining, completion, turnaround, waiting;
};

void sort(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival > p[j].arrival) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int findMinProcess(struct Process p[], int n, int time) {
    int min = 99999, index = -1;
    for (int i = 0; i < n; i++) {
        if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min) {
            min = p[i].remaining;
            index = i;
        }
    }
    return index;
}

void calculateTimes(struct Process p[], int n) {
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = findMinProcess(p, n, time);
        if (idx == -1) {
            time++;
            continue;
        }
        p[idx].remaining--;
        time++;
        if (p[idx].remaining == 0) {
            p[idx].completion = time;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }
    }
}

void display(struct Process p[], int n) {
    float avgWait = 0, avgTurnaround = 0;
    printf("\nID | Arrival | Burst | Completion | Turnaround | Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("%2d | %7d | %5d | %10d | %10d | %7d\n", p[i].id, p[i].arrival, p[i].burst, p[i].completion, p[i].turnaround, p[i].waiting);
        avgWait += p[i].waiting;
        avgTurnaround += p[i].turnaround;
    }
    printf("\nAvg Waiting: %.2f\nAvg Turnaround: %.2f\n", avgWait / n, avgTurnaround / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    sort(p, n);
    calculateTimes(p, n);
    display(p, n);

    return 0;
}

