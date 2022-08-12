#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<math.h>
int dist[100000];

typedef struct nodetype nodetype;

struct nodetype{
	int element;
	nodetype* leftchild;
	nodetype* rightchild;
};

typedef struct nodetype* SET;

bool MEMBER(int x, SET A){
	if (A == NULL){
		return false;
	}
	else if (x == A->element){
		return true;
	}
	else if (x < A->element){
		return (MEMBER(x, A->leftchild));
	}
	else{
		return (MEMBER(x, A->rightchild));
	}
}

SET INSERT(int x, SET A){
	if (A == NULL){
		A = (SET) malloc(sizeof(nodetype));
		A->element = x;
		A->leftchild = NULL;
		A->rightchild = NULL;
		return A;
	}

	else if (x < A->element){
		A->leftchild = INSERT(x, A->leftchild);
	}

	else if (x > A->element){
		A->rightchild = INSERT(x, A->rightchild);
	}
	return A;
}

int DELETEMIN(SET A){
	int minimum;

	if (A->leftchild == NULL){
		minimum = A->element;
		A = A->rightchild;
		return minimum;
	}
	else{
		minimum = DELETEMIN(A->leftchild);
		return minimum;
	}
}

SET DELETE(int x, SET A){
	if (A != NULL){
		if (x < A->element){
			A->leftchild = DELETE(x, A->leftchild);
		}
		else if (x > A->element){
			A->rightchild = DELETE(x, A->rightchild);
		}
		else if ((A->leftchild == NULL) && (A->rightchild == NULL)){
			return NULL;
		}
		else if (A->leftchild == NULL){
			return A->rightchild;
		}
		else if (A->rightchild == NULL){
			return A->leftchild;
		}
		else{
			A->element = DELETEMIN(A->rightchild);
			return A;
		}
	}
}

// this is the dfs fucntion to compute the distance of each node from the root

void dfs(SET A){
    if(A == NULL){
        return;
    }
    if(A->leftchild != NULL){	// leftchid exists
        dist[A->leftchild->element] = dist[A->element] + 1;  
        dfs(A->leftchild);
    }
    if(A->rightchild != NULL){ // right child exists
        dist[A->rightchild->element] = dist[A->element] + 1; // number of nodes from the root
        dfs(A->rightchild);   
    } 
}


int main(){

	int n , x; 
    int first_time = 0  ;
    int sum_distance = 0  ;
    double avg = 0, log_value = 0;
    SET A = NULL;
    scanf("%d" , &n);
    for(int i =1; i <= n ; i++){
        scanf("%d" , &x);
        if(first_time == 0){
            first_time = 1;
            A = INSERT(x ,A); // initiates A when A is empty;
        }
        else{
            INSERT(x, A);
        }
    }

    dfs(A);
    for(int i = 1; i <= n ;i++){
        sum_distance += dist[i];
    }
    avg = (double)((double)sum_distance /(double) n); // average node from root to another node
    log_value = log2((double)n); //log2 function only work if we complie on tux with the gcc -lm option for using the 
    // library math.h
    printf("Number of input nodes : %d \nTotal distance : %d \n", n, sum_distance) ;// this should be around (n log n)
    printf("log2(n) is %.2lf  vs average number of nodes from root to another node : %.2lf\n", log_value, avg);
	printf("4log2(n) + 1 : %.2lf\n", 4*log_value + 1);
	printf("###########################\n");
}
