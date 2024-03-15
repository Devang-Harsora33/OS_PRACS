#include <stdio.h>

int main() {
    int n, m, i, j, k;
    n = 5; // Number of processes
    m = 3; // Number of resources
    int available[1][3] = {{3, 3, 2}};
    int alloc[5][3] = {{0, 1, 0}, // P0 // Allocation Matrix
                       {2, 0, 0}, // P1
                       {3, 0, 2}, // P2
                       {2, 1, 1}, // P3
                       {0, 0, 2}}; // P4
    int max[5][3] = {{7, 5, 3}, // P0 // MAX Matrix
                     {3, 2, 2}, // P1
                     {9, 0, 2}, // P2
                     {2, 2, 2}, // P3
                     {4, 3, 3}}; // P4

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }
    int need[n][m];
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }

    int work[m];
    for (i = 0; i < m; i++) {
        work[i] = available[0][i];
    }

    int finish[n];
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    ans[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("The system is not in a safe state\n");
            return 0;
        }
    }

    printf("Processes\tAllocation Table\t\t"
           "Max Table\t\t"
           "Need Table\t\t"
           "Available Table\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t", ans[i]);
        for (int j = 0; j < m; j++) {
            printf("|%d|  ", alloc[ans[i]][j]);
            printf("    ");
        }
        for (int j = 0; j < m; j++) {
            printf("|%d|  ", max[ans[i]][j]);
            printf("   ");
        }
        for (int j = 0; j < m; j++) {
            printf("|%d|  ", need[ans[i]][j]);
            printf("   ");
        }
        for (int j = 0; j < m; j++) {
            printf("|%d|  ", available[0][j]);
            printf("   ");
        }

        printf("\n");
    }

    printf("Following is the SAFE Sequence\n");
    for (i = 0; i < n - 1; i++)
        printf(" P%d ->", ans[i]);
    printf(" P%d", ans[n - 1]);

    return 0;
}
