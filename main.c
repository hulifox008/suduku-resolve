#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
struct state
{
    unsigned char sudoku[9][9];
    struct state *pchild;
}__attribute__((packed));

int search_child(struct state *s)
{
}

struct state init_state = 
{
    .sudoku={
    { 8, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 3, 6, 0, 0, 0, 0, 0},
    { 0, 7, 0, 0, 9, 0, 2, 0, 0},
    { 0, 5, 0, 0, 0, 7, 0, 0, 0},
    { 0, 0, 0, 0, 4, 5, 7, 0, 0},
    { 0, 0, 0, 1, 0, 0, 0, 3, 0},
    { 0, 0, 1, 0, 0, 0, 0, 6, 8},
    { 0, 0, 8, 5, 0, 0, 0, 1, 0},
    { 0, 9, 0, 0, 0, 0, 4, 0, 0}
    }
};
#endif
#if 0 
const unsigned char sudoku[9][9] =
{
    { 8, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 3, 6, 0, 0, 0, 0, 0},
    { 0, 7, 0, 0, 9, 0, 2, 0, 0},
    { 0, 5, 0, 0, 0, 7, 0, 0, 0},
    { 0, 0, 0, 0, 4, 5, 7, 0, 0},
    { 0, 0, 0, 1, 0, 0, 0, 3, 0},
    { 0, 0, 1, 0, 0, 0, 0, 6, 8},
    { 0, 0, 8, 5, 0, 0, 0, 1, 0},
    { 0, 9, 0, 0, 0, 0, 4, 0, 0}
};
#else
const unsigned char sudoku[9][9] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0
};
#endif

void show_sudoku(unsigned char s[9][9])
{
    int y, x;
    printf("\n");
    for(y=0;y<9;y++)
    {
        for(x=0;x<9;x++)
            printf("%d ", s[y][x]);
        printf("\n");
    }
}

int sudoku_completed(unsigned char s[9][9])
{
    int x, y;
    for(y=0;y<9;y++)
        for(x=0;x<9;x++)
            if(s[y][x]==0) return 0;
    return 1;
}

int search_child_pos(const unsigned char s[9][9], int x, int y)
{
    static c = 0;
    /*
    show_sudoku(s);
    printf("--> %d,%d  ", x, y);
    */

    unsigned char ns[9][9];
    unsigned char possible_v[10]; /* index as vaule, 0 is not used. */
    memcpy(ns, s, sizeof(ns));
    memset(possible_v, 1, sizeof(possible_v));

    unsigned int j;
    for(j=0;j<9;j++)
    {
        possible_v[ns[j][x]] = 0;
        possible_v[ns[y][j]] = 0;
        possible_v[ns[y/3*3+j/3][x/3*3+j%3]] = 0;
    }

/*
    for(j=1;j<=9;j++)
    {
        if(possible_v[j])
            printf("%d ", j);
    }
    printf("\n");
*/

    for(j=1;j<=9;j++)
    {
        if(possible_v[j])
        {
            int i;
            ns[y][x] = j;
            if(0==(c++%500000))
                show_sudoku(s);

            for(i=0;i<81;i++)
            {
                if(0==ns[i/9][i%9])
                        break;
            }

            if(81==i)
            {
                printf("!!!!!!!!!!!!!!!!!\n");
                show_sudoku(ns);
                exit(0);
            }
            else
                search_child_pos(ns, i%9, i/9);
        }
    }
}


int search_child(const unsigned char s[9][9])
{
    int x, y;
    for(y=0;y<9;y++)
    {
        for(x=0;x<9;x++)
        {
            if(0==s[y][x])
            {
                printf("%x, %d\n", x, y);
                search_child_pos(s, x, y);
            }
        }
    }
    return 0;
}


int main()
{
    search_child(sudoku);
    return 0;
}
