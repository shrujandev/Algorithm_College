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

static void dfsQ3(int src, int *visited, int n, const connection_t graph[n][n], int dest, int *ans){
    visited[src] = 1;
    for(int i = src;i < n;i++){
        for(int j = 0;j < n;j++){
            if(graph[i][j].distance != __INT_MAX__ &&  j == src){
                *ans = 1;
            }
            if(graph[i][j].distance != __INT_MAX__ &&  visited[j] != 1){
                dfsQ3(j, visited, n, graph, dest, ans);
            }
            
        }
    }
}

static void swap(airport_t *x, airport_t *y){
    airport_t t = *x;
    *x = *y;
    *y = t;
}

static int partition(airport_t list[], int start, int end, int (*predicate_func)(const airport_t *, const airport_t *)){
    int pIndex = start;
    airport_t pivot = list[end];
    
    for(int i = start;i < end;i++){
        if(predicate_func(&list[i], &pivot)){
            swap(&list[i], &list[pIndex]);
            pIndex++;
        }
    }

    swap(&list[end], &list[pIndex]);
    return pIndex;
}

static void quickSort(airport_t list[], int start, int end, int (*predicate_func)(const airport_t *,const airport_t *)){
    if(start < end){
        int pIndex = partition(list, start, end, predicate_func);
        quickSort(list, start, pIndex-1, predicate_func);
        quickSort(list, pIndex+1, end, predicate_func);
    }
}

static int longestPrefix(airport_t fir, airport_t sec){
    int i = 0;
    while(fir.airport_name[i] != '\0' && sec.airport_name[i] != '\0' && fir.airport_name[i] == sec.airport_name[i] ){
        i++;
    }
    return i;
}

static void shiftTable(const char p[],int t[]){
    int i,j,m=0;
    for(int x =0; p[x] != '\0';x++)
        m++;
    for( i = 0;i < 500;i++)
        t[i] = m;
    for(j = 0;j < m-1; j++)
        t[p[j]-'0'] = m-1-j;
}

static int horspool(const char src[],const char p[],int t[]){
    int i,k,m=0,n=0;
    for(int x = 0 ; p[x] != '\0';x++)
        m++;
    for(int x = 0 ; src[x] != '\0';x++)
        n++;
    i=m-1;
    while(i<n)
    {
        k=0;
        while((k<m)&&(p[m-1-k]==src[i-k]))
        k++;
        if(k==m)
        return(i-m+1);
        else
        i+=t[src[i]-'0'];
    }
    return -1;
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

    return ans;
}

int q3(const airport_t *src, int n, const connection_t connections[n][n]){
    int srcVal = src->num_id;
    int *visited;
    visited  = (int*)calloc(n,sizeof(int));
    int ans = 0;

    dfsQ3(srcVal, visited, n, connections, srcVal, &ans);
    return ans;
}

void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),airport_t airport_list[n]){
    quickSort(airport_list, 0, n-1,predicate_func);

}

pair_t q5(int n, airport_t airports[n])
{
    pair_t ans = {-1, -1};
    int max = 0;
    int len;

    for(int i = 0;i < n;i++){
        for(int j = i+1;j < n;j++){
            len = longestPrefix(airports[i],airports[j]);
            if(max < len){
                max = len;
                ans.first = airports[i].num_id;
                ans.second = airports[j].num_id;
            }
        }
    }

    return ans;
}

int q6(int n, int amount, const int entry_fee[n]){
    int low=0, high=n-1;
    int mid;
        while(low <= high) {

            mid = (low +high)/2; 


            if(entry_fee[mid] == amount) {
                return mid+1;
            } 
            else if(entry_fee[mid] < amount) {
                low = mid+1;
            } 
            else { 
                high = mid-1;
            }
        }

        return low;
    
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
