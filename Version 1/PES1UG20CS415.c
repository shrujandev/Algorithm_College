//PES1UG20CS415   SHRUJAN
#include "header.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct stack{	// stack data strucure used in q8
	int airport;
	struct stack *next;
}Stack;


typedef struct treeNodes{  // node data structure used in q9
	int node;
	int predecessor;
	int weight;
}TreeNode;

typedef struct queue{  //queue data structure used in q9
	TreeNode *queue;
	int size;
}PathQ;


// ANY STATIC FUNCTIONS ARE UP HERE

static void dfsQ1(int x,int *visited,int n,const connection_t graph[n][n]){    //dfs algorithm used in q1
    visited[x] = 1;
    for(int i = x;i < n;i++){
        for(int j = 0;j < n;j++){
            if(graph[i][j].distance != __INT_MAX__ && visited[j] != 1){
                dfsQ1(j, visited, n, graph);
            }
        }
    }
}

static int check(int *visited, int n){    // function to check if the paths are available
    for(int i = 0;i < n; i++){
        if(visited[i] != 1){
            return 0;
        }
        visited[i] = 0;
    }
    return 1;
}

static void dfsQ2(int src, int *visited, int n, const connection_t graph[n][n], int dest, int num, int *ans){      //dfs used in q2
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

static void dfsQ3(int src, int *visited, int n, const connection_t graph[n][n], int dest, int *ans){     // dfs used in q3
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

static void swap(airport_t *x, airport_t *y){    // swap function used in q4
    airport_t t = *x;
    *x = *y;
    *y = t;
}

static int partition(airport_t list[], int start, int end, int (*predicate_func)(const airport_t *, const airport_t *)){   // the partiton function of q4
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

static void quickSort(airport_t list[], int start, int end, int (*predicate_func)(const airport_t *,const airport_t *)){   // quicksort function in q4
    if(start < end){
        int pIndex = partition(list, start, end, predicate_func);
        quickSort(list, start, pIndex-1, predicate_func);
        quickSort(list, pIndex+1, end, predicate_func);
    }
}

static int longestPrefix(airport_t fir, airport_t sec){    //function to find longest prefix in q5
    int i = 0;
    while(fir.airport_name[i] != '\0' && sec.airport_name[i] != '\0' && fir.airport_name[i] == sec.airport_name[i] ){
        i++;
    }
    return i;
}

static void shiftTable(const char p[],int t[]){      // shifttable used in horspool algorithm
    int i,j,m=0;  
    for(int x =0; p[x] != '\0';x++)
        m++;
    for( i = 0;i < 500;i++)
        t[i] = m;
    for(j = 0;j < m-1; j++)
        t[p[j]-'0'] = m-1-j;
}

static int horspool(const char src[],const char p[],int t[]){    // function implementing horsepool algorithm
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



static void push(Stack **top, int airport){         // push function for stack
	Stack *temp = (Stack *)malloc(sizeof(Stack));
	temp -> airport = airport;
	temp -> next = *top;
	*top = temp;
}

static int pop(Stack **top){         //pop function for stack
	Stack *temp = *top;
	int popElement = (*top) -> airport;
	*top = (*top) -> next;
	free(temp);
	return popElement;
}

//dfs used in q8
static void dfsQ8(int n, int curAirport, int *visited, const connection_t connections[n][n], int src, int *currDistance, int *currMinDistance, Stack **tempStack, int *trip_order){
	visited[curAirport] = 1;											
	for(int nextAirport = 0; nextAirport < n; nextAirport++)			
	{
		if(nextAirport != curAirport)
		{
			if(connections[curAirport][nextAirport].distance != INT_MAX && !visited[nextAirport])	
			{
				(*currDistance) += connections[curAirport][nextAirport].distance;							
				push(tempStack, nextAirport);														
				dfsQ8(n, nextAirport, visited, connections, src, currDistance, currMinDistance, tempStack, trip_order); 
				pop(tempStack);																		
				(*currDistance) -= connections[curAirport][nextAirport].distance;							
			}
			else if(nextAirport == src && visited[nextAirport] == 1 && connections[curAirport][nextAirport].distance != INT_MAX)		
			{
				int unvisitedCount = 0;
				for(int i = 0; i < n; i++)					
				{
					if(visited[i] == 0)
					{
						unvisitedCount++;
					}
				}
				if(unvisitedCount == 1)					
				{
					(*currDistance) += connections[curAirport][nextAirport].distance;
					if(*currDistance < *currMinDistance)
					{
						*currMinDistance = *currDistance;

						Stack *temp = *tempStack;
						int i = n - 2;
						while(temp != NULL)
						{
							trip_order[i] = temp -> airport;
							temp = temp -> next;
							i--;
						}
					}
					(*currDistance) -= connections[curAirport][nextAirport].distance;	
				}

			}
		}
	}
	visited[curAirport] = 0;								
}


static int nodeQueue(int n, PathQ *freeNode){
	for(int i = 0; i < freeNode -> size; i++)
	{
		if(freeNode -> queue[i].node == n)
		{
			return i;
		}
	}
	return -1;
}

static TreeNode smallest(PathQ *freeNode){
	int index = 0;
	for(int i = 0; i < freeNode -> size; i++){
		if(freeNode -> queue[i].weight < freeNode -> queue[index].weight){
			index = i;
		}
	}
	TreeNode returnNode = freeNode -> queue[index];
	for(int i = index; i < (freeNode -> size) - 1; i++){
		freeNode -> queue[i] = freeNode -> queue[i + 1];
	}
	(freeNode -> size -= 1);

	return returnNode;
}




static void dijkstra(int n,const connection_t graph[n][n], int start, int *hash){       //dijkstras algorthm used in q10
    int cost[n][n], distance[n], pred[n];
    int visited[n], count, minDistance, nexTreeNodeode, i, j;

    for(i = 0;i < n;i++){
        for(j = 0;j < n;j++){
            if(graph[i][j].time == 0){
                cost[i][j] = INT_MAX;
            }
            else{
                cost[i][j] = graph[i][j].time;
            }
        }
    }

    for(i = 0;i < n; i++){
        distance[i] = cost[start][i];
        pred[i] = start;
        visited[i] = 0;
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while(count < n-1){
        minDistance = INT_MAX;

        for(i = 0;i < n; i++){
            if(distance[i] < minDistance && !visited[i]){
                minDistance = distance[i];
                nexTreeNodeode = i;
            }
        }

        visited[nexTreeNodeode] = 1;
        for(i = 0;i < n;i++){
            if(!visited[i]){
                if(minDistance + cost[nexTreeNodeode][i] < distance[i]){
                    distance[i] = minDistance + cost[nexTreeNodeode][i];
                    pred[i] = nexTreeNodeode;
                }
            }
        }
        count++;
    } 

    for(i = 0;i < n;i++){
        if( i != start){
            hash[i] = distance[i];
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

pair_t q5(int n, airport_t airports[n]){
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

void q7(int n, const char *pat, int contains[n], const airport_t airports[n]){
    for(int i = 0;i < n;i++){
        int t[500] = {0};
        shiftTable(pat,t);
        if(horspool(airports[i].airport_name,pat,t) >= 0){
            contains[i] = 1; 
        }
    }
}



int q8(int n, int trip_order[n - 1], const connection_t connections[n][n]){
	
	int currMinDistance = INT_MAX;				

	for(int i = 0; i < n; i++){
		int currDistance = 0;
		Stack *tempStack = NULL;
		int *visited = (int *)malloc(n * sizeof(int));
		push(&tempStack, i);			
		for(int j = 0; j < n; j++){
			visited[j] = 0;
		}
		dfsQ8(n, i, visited, connections, i, &currDistance, &currMinDistance, &tempStack, trip_order);
		pop(&tempStack);				
		free(visited);
	}		

	if(currMinDistance == INT_MAX){
		return -1;
	}
	else{
		return currMinDistance;
    }			
}



int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n]){
	TreeNode treeNodes[n];
	int tnodeCount = 0;
	PathQ freeNode;
	freeNode.queue = (TreeNode *)malloc(n * sizeof(TreeNode));
	freeNode.size = n;
	for(int i = 0; i < n; i++){
		freeNode.queue[i].node = i;
		freeNode.queue[i].predecessor = -1;
		freeNode.queue[i].weight = INT_MAX;
	}

	freeNode.queue[0].weight = 0;							

	int index;
	while(freeNode.size != 0){
		treeNodes[tnodeCount] = smallest(&freeNode);	
		int cur_node = treeNodes[tnodeCount].node;		

		if(cur_node != 0){
			pair_t edge = {treeNodes[tnodeCount].predecessor, cur_node};	 
			edges[tnodeCount - 1] = edge;									
		}

		for(int i = 0; i != n; i++){
			if(i != cur_node){
				if(connections[cur_node][i].distance != INT_MAX){
					index = nodeQueue(i, &freeNode);						
					if((index != -1) && connections[cur_node][i].time < freeNode.queue[index].weight){	
						freeNode.queue[index].weight = connections[cur_node][i].time;		
						freeNode.queue[index].predecessor = cur_node;						
					}
				}
			}
		}
		
		tnodeCount++;		
	}

	int total_time = 0;
	for(int i = 0; i < n - 1; i++){
		total_time += connections[edges[i].first][edges[i].second].time;
	}
	free(freeNode.queue);
	return total_time;
}

void q10(int n, int k, const airport_t *src,const connection_t connections[n][n], const int destinations[k],int costs[k]){
    int hash[n];
    dijkstra(n, connections,src->num_id, hash);
    int i = 0;
    while( i != k){
        costs[i] = hash[destinations[i]];
        i++;
    }

}

// END
