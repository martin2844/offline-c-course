// Chapter 12: Algorithms and Problem Solving - Dynamic Programming
// Solution to Exercise 12.3: Solve the knapsack problem using dynamic programming

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

typedef struct {
    int weight;
    int value;
    char name[20];
} Item;

// Dynamic programming solution for 0/1 knapsack
int knapsack_01_dp(Item items[], int n, int capacity, int* selected_items) {
    // dp[i][w] represents maximum value using first i items with capacity w
    int dp[MAX_ITEMS + 1][MAX_CAPACITY + 1];

    // Initialize dp table
    memset(dp, 0, sizeof(dp));

    // Fill the dp table
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight > w) {
                // Item i is too heavy, cannot include it
                dp[i][w] = dp[i - 1][w];
            } else {
                // Choose the maximum between including and excluding item i
                int include_value = items[i - 1].value + dp[i - 1][w - items[i - 1].weight];
                int exclude_value = dp[i - 1][w];
                dp[i][w] = (include_value > exclude_value) ? include_value : exclude_value;
            }
        }
    }

    // Backtrack to find which items were selected
    int w = capacity;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            // Item i was included
            selected_items[i - 1] = 1;
            w -= items[i - 1].weight;
        } else {
            selected_items[i - 1] = 0;
        }
    }

    return dp[n][capacity];
}

// Memory-optimized version using only 1D array
int knapsack_01_optimized(Item items[], int n, int capacity, int* selected_items) {
    int dp[MAX_CAPACITY + 1] = {0};
    int choice[MAX_ITEMS + 1][MAX_CAPACITY + 1] = {0};

    // Fill dp table
    for (int i = 1; i <= n; i++) {
        for (int w = capacity; w >= items[i - 1].weight; w--) {
            int include_value = items[i - 1].value + dp[w - items[i - 1].weight];
            int exclude_value = dp[w];

            if (include_value > exclude_value) {
                dp[w] = include_value;
                choice[i][w] = 1;
            } else {
                dp[w] = exclude_value;
                choice[i][w] = 0;
            }
        }
    }

    // Backtrack to find selected items
    int w = capacity;
    for (int i = n; i > 0 && w > 0; i--) {
        selected_items[i - 1] = choice[i][w];
        if (choice[i][w]) {
            w -= items[i - 1].weight;
        }
    }

    return dp[capacity];
}

// Unbounded knapsack (items can be selected multiple times)
int knapsack_unbounded(Item items[], int n, int capacity) {
    int dp[MAX_CAPACITY + 1] = {0};

    // For each capacity, find the best item(s) to use
    for (int w = 1; w <= capacity; w++) {
        int max_value = 0;

        for (int i = 0; i < n; i++) {
            if (items[i].weight <= w) {
                int value = items[i].value + dp[w - items[i].weight];
                if (value > max_value) {
                    max_value = value;
                }
            }
        }

        dp[w] = max_value;
    }

    return dp[capacity];
}

// Fractional knapsack (greedy approach)
int knapsack_fractional(Item items[], int n, int capacity) {
    // Sort items by value/weight ratio in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            double ratio1 = (double)items[j].value / items[j].weight;
            double ratio2 = (double)items[j + 1].value / items[j + 1].weight;
            if (ratio1 < ratio2) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    double total_value = 0;
    int current_weight = 0;

    for (int i = 0; i < n && current_weight < capacity; i++) {
        if (current_weight + items[i].weight <= capacity) {
            // Take the entire item
            current_weight += items[i].weight;
            total_value += items[i].value;
            printf("  Taking whole item: %s (weight: %d, value: %d)\n",
                   items[i].name, items[i].weight, items[i].value);
        } else {
            // Take fraction of the item
            int remaining_capacity = capacity - current_weight;
            double fraction = (double)remaining_capacity / items[i].weight;
            total_value += items[i].value * fraction;
            printf("  Taking %.2f of item: %s (weight: %d, value: %d)\n",
                   fraction, items[i].name, items[i].weight, items[i].value);
            break;
        }
    }

    return (int)total_value;
}

void print_knapsack_solution(Item items[], int n, int selected_items[], int total_value) {
    printf("Selected items:\n");
    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        if (selected_items[i]) {
            printf("  %s (weight: %d, value: %d)\n",
                   items[i].name, items[i].weight, items[i].value);
            total_weight += items[i].weight;
        }
    }

    printf("Total weight: %d\n", total_weight);
    printf("Total value: %d\n", total_value);
}

int main() {
    printf("Knapsack Problem Dynamic Programming Solutions\n");
    printf("==============================================\n");

    // Test case 1: Standard 0/1 knapsack
    Item items1[] = {
        {10, 60, "Laptop"},
        {20, 100, "Camera"},
        {30, 120, "Tablet"}
    };
    int n1 = sizeof(items1) / sizeof(items1[0]);
    int capacity1 = 50;
    int selected1[MAX_ITEMS] = {0};

    printf("\n1. 0/1 Knapsack Problem:\n");
    printf("Items:\n");
    for (int i = 0; i < n1; i++) {
        printf("  %s - Weight: %d, Value: %d\n",
               items1[i].name, items1[i].weight, items1[i].value);
    }
    printf("Capacity: %d\n\n", capacity1);

    int max_value1 = knapsack_01_dp(items1, n1, capacity1, selected1);
    printf("Maximum value: %d\n", max_value1);
    print_knapsack_solution(items1, n1, selected1, max_value1);

    // Test case 2: Larger knapsack problem
    Item items2[] = {
        {2, 3, "Book"},
        {3, 4, "Phone"},
        {4, 5, "Headphones"},
        {5, 8, "Watch"},
        {9, 10, "Camera"}
    };
    int n2 = sizeof(items2) / sizeof(items2[0]);
    int capacity2 = 20;
    int selected2[MAX_ITEMS] = {0};

    printf("\n2. Optimized 0/1 Knapsack:\n");
    int max_value2 = knapsack_01_optimized(items2, n2, capacity2, selected2);
    printf("Maximum value: %d\n", max_value2);
    print_knapsack_solution(items2, n2, selected2, max_value2);

    // Test case 3: Unbounded knapsack
    printf("\n3. Unbounded Knapsack (items can repeat):\n");
    int max_value3 = knapsack_unbounded(items2, n2, capacity2);
    printf("Maximum value (unbounded): %d\n", max_value3);

    // Test case 4: Fractional knapsack
    printf("\n4. Fractional Knapsack (greedy approach):\n");
    Item items3[] = {
        {10, 60, "Gold"},
        {20, 100, "Silver"},
        {30, 120, "Bronze"}
    };
    int n3 = sizeof(items3) / sizeof(items3[0]);
    int capacity3 = 50;

    printf("Maximum value (fractional): %d\n",
           knapsack_fractional(items3, n3, capacity3));

    printf("\nKnapsack Problem Solutions Completed!\n");
    return 0;
}