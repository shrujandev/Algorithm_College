#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


// ANY STATIC FUNCTIONS ARE UP HERE

static void dfsQ1(int x,int *visited,int n,const connection_t graph[n][n]){
    visited[x] = 1;
    for(int i = x;i < n;i++){
        for(int j = 0;j < n;j++){
            if(graph[i][j].distance != __INT_MAX__ && visited[j] != 1){
                dfsQ1(j, visited, n, graph);
            }
        }
    }
}

static int check(int *visited, int n){
    for(int i = 0;i < n; i++){
        if(visited[i] != 1){
            return 0;
        }
        visited[i] = 0;
    }
    return 1;
}

static void dfsQ2(int src, int *visited, int n, const connection_t graph[n][n], int dest, int num, int *ans){
    visited[src] = 1;
    
    if(src == dest){
        int flag = 0;
        for(int i = 0;i < n;i++){
            if(visited[i] == 1){
                flag++;
            }
        }

        if(flag <= num+1){
            *ans = 1;
        }
    }

    for(int i = src;i < n;i++){
        for(int j = 0;j < n; j++){
            if(graph[i][j].distance != __INT_MAX__ && visited[j] != 1){
                dfsQ2(j, visited, n, graph, dest, num, ans);
            }
        }
    }

}

// YOUR SOLUTIONS BELOW

int q1(int n, const connection_t connections[n][n]){
    int ans = 1;
    int *visited;
    visited  = (int*)calloc(n,sizeof(int));

    for(int i = 0;i < n; i++){
        dfsQ1(i, visited, n, connections);
        ans = ans & check(visited, n);
    }
    free(visited);
    return ans;
}

int q2(const airport_t *src, const airport_t *dest, int n, int k,const connection_t connections[n][n]){
    int srcVal = src->num_id;
    int destVal = dest->num_id;
    int ans = 0; 
    int *visited;
    visited  = (int*)calloc(n,sizeof(int));

    dfsQ2(srcVal, visited, n, connections, destVal, k, &ans);

    free(visited);

    if(ans)
        return 1;
    else
        return 0;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n])
{
    return 0;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{

}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
    return 0;
}

void q7(int n, const char *pat, int contains[n], const airport_t airports[n])
{

}

int q8(int n, int trip_order[n - 1], const connection_t connections[n][n])
{
    return 0;
}

int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
    return 0;
}

void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{

}

// END
