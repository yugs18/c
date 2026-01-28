/* for.c */
#include <stdio.h>
#include <assert.h>
#define F fflush(stdout) // Macro to flush output buffer

void multi(int t, int v) {
    int result;

    result = t * v;
    printf("%d x %d = %d\n", t, v, result);

    return;
}

int main() {
    int x, table;

    printf("Select a multiplication table: "); F; // Prompt user for multiplication table
    scanf("%d", &table);
    assert( (table < 13) && (table > 0) ); // Ensure table is between 1 and 12

    for (x = 0; x < 13; x++)
        multi(table, x);

    return 0;
}