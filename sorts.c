#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

const int N = 60000;
const int interval = 1000;
int arr[1001000];
int output[100];
int count[100];

void arr_print(int arr[], int len){
    for (int i = 0; i < len; i++){
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void arr_init_rand(int arr[], int len){
    for (int i = 0; i < len; i++){
        arr[i] = rand() % len;
    }
}

void arr_init_const(int arr[], int len){
    for (int i = 0; i < len; i++){
        arr[i] = 0;
    }
}

/*
void arr_init_A(int arr[], int len){
    for (int i = 0; i < len / 2; i++){
        arr[i] = 2 * i + 1;
    }
    for (int i = len / 2; i < len; i++){
        arr[i] = 2 * (len - i - 1);
    }
}
*/
void arr_init_V(int arr[], int len){

    for (int i = 0; i < len / 2; i++){
        arr[i] = len - (len % 2) - 2 * i - 1;
    }
    for (int i = len / 2; i < len; i++){
        arr[i] = 2 * i - len + (len % 2);
    }
}


void arr_init_A(int *arr, int size) {
    int i=0;
    for (int j=1; j <= size; j+=2) {
        arr[i] = j;
        ++i;
    }

    for (int j=arr[i-1] - 1; j>=0; j-=2){
        arr[i] = j;
        i++;
    }
}

/*
void arr_init_V(int *arr, int size) {
    int i=0;
    int j;
    if (size % 2) {
        j = size;
    } else {j = size+1;}

    for (j; j>0; j-=2){
        arr[i] = j;
        i++;
    }

    for (j=arr[i-1] + 1; j <= size; j+=2) {
        arr[i] = j;
        i++;
    }
}
*/

void arr_init_increasing(int arr[], int len){
    for (int i = 0; i < len; i++){
        arr[i] = i;
    }
}

void arr_init_decreasing(int arr[], int len){
    for (int i = 0; i < len; i++){
        arr[i] = len - i;
    }
}

void swap(int *a, int *b){
    int e = *a;
    *a = *b;
    *b = e;
}

void bubbleSort(int arr[], int len){
    for (int i = 0; i < len - 1; i++){
        for (int j = 0; j < len - i - 1; j++){
            if (arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i +2;

    if (left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if (largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int len){
    for (int i = len / 2 - 1; i >= 0; i--){
        heapify(arr, len, i);
    }
    for (int i = len - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int array[], int low, int high) {
    swap(&arr[(low + high + 1) / 2], &arr[high]);
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort_A_V(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort_A_V(array, low, pi - 1);
    quickSort_A_V(array, pi + 1, high);
  }
}

void quickSort(int arr[], int low, int high){
	if(high <= low) return;
	int i = low - 1, j = high + 1, 
	pivot = arr[(low + high) / 2];
	
	while(1){
		while(pivot > arr[++i]);
		while(pivot < arr[--j]);
		if(i <= j)
			swap(&arr[i], &arr[j]);
		else
			break;
	}

	if(j > low)
	    quickSort(arr, low, j);
	if(i < high)
	    quickSort(arr, i, high);
}

void merge(int arr[], int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], M[n2];

    for (int i = 0; i < n1; i++){
        L[i] = arr[p + i];
    }
    for (int j = 0; j < n2; j++){
        M[j] = arr[q + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = p;

    while (i < n1 && j < n2){
        if (L[i] <= M[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void shellSort(int arr[], int len){
    for (int interval = len/2; interval > 0; interval /=2){
        for (int i = interval; i < len; i++){
            int e = arr[i];
            int j;
            for (j = i; j >= interval && arr[j - interval] > e; j -= interval){
                arr[j] = arr[j - interval];
            }
            arr[j] = e;
        }
    }
}

void countSort(int arr[], int count[], int output[], int len){
    int max = arr[0];
    for (int i = 1; i < len; i++){
        if (arr[i] > max){
            max = arr[i];
        }
    }
    for (int i = 0; i < len; i++){
        output[i] = 0;
        count[i] = 0;
    }

    for (int i = 0; i < max; ++i){
        count[i] = 0;
    }

    for (int i = 0; i < len; i++){
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }

    for (int i = len - 1; i >= 0; i--){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < len; i++){
        arr[i] = output[i];
    }
}

void TASK1_BS(){
    float BS_results[(N-10000)/interval];
    clock_t begin, end;

    srand(time(NULL));
    double time_spent;

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        printf("/");
        arr_init_rand(arr, i);
        begin = clock();
        bubbleSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        BS_results[(i-10000)/interval] = time_spent;
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *BS_OUT = fopen("BS_results.txt", "w");
    printf("\n");
	for(int i = 0; i < points; i++){
		fprintf(BS_OUT, "%f\n", BS_results[i]);
	}
    fclose(BS_OUT);
}

void TASK1_HS(){
    float HS_results[(N-10000)/interval];
    clock_t begin, end;
    double time_spent;

    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        printf("/");
        arr_init_rand(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval] = time_spent;
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *HS_OUT = fopen("HS_results.txt", "w");
    printf("\n");
	for(int i = 0; i < points; i++){
		fprintf(HS_OUT, "%f\n", HS_results[i]);
	}
    fclose(HS_OUT);
}

void TASK1_CS(){
    float CS_results[(N-10000)/interval];
    clock_t begin, end;

    srand(time(NULL));
    double time_spent;

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        printf("/");
        arr_init_rand(arr, i);
        begin = clock();
        countSort(arr, count, output, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        CS_results[(i-10000)/interval] = time_spent;
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *CS_OUT = fopen("CS_results.txt", "w");
    printf("\n");
	for(int i = 0; i < points; i++){
		fprintf(CS_OUT, "%f\n", CS_results[i]);
	}
    fclose(CS_OUT);
}

void TASK1_ShS(){
    float ShS_results[(N-10000)/interval];
    clock_t begin, end;

    srand(time(NULL));
    double time_spent;

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        printf("/");
        arr_init_rand(arr, i);
        begin = clock();
        shellSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        ShS_results[(i-10000)/interval] = time_spent;
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *ShS_OUT = fopen("ShS_results.txt", "w");
    printf("\n");
	for(int i = 0; i < points; i++){
		fprintf(ShS_OUT, "%f\n", ShS_results[i]);
	}
    fclose(ShS_OUT);
}

void TASK2_QS(){
    float QS_results[(N-10000)/interval][4];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_");
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_rand(arr, i);
        begin = clock();
        quickSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][0] = time_spent;

        arr_init_const(arr, i);
        begin = clock();
        quickSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][1] = time_spent;

        arr_init_increasing(arr, i);
        begin = clock();
        quickSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][2] = time_spent;

        arr_init_decreasing(arr, i);
        begin = clock();
        quickSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][3] = time_spent;

        printf("/");

    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *QS_OUT = fopen("QS_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 4; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(QS_OUT, "%f\n", QS_results[j][i]);
        }
        fprintf(QS_OUT, "\n");
	}
    fclose(QS_OUT);
}

void TASK2_HS(){
    float HS_results[(N-10000)/interval][4];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_rand(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][0] = time_spent;

        arr_init_const(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][1] = time_spent;

        arr_init_increasing(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][2] = time_spent;

        arr_init_decreasing(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][3] = time_spent;

        printf("/");
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *HS_OUT = fopen("heapS_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 4; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(HS_OUT, "%f\n", HS_results[j][i]);
        }
        fprintf(HS_OUT, "\n");
	}
    fclose(HS_OUT);
}

void TASK2_MS(){
    float MS_results[(N-10000)/interval][4];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_rand(arr, i);
        begin = clock();
        mergeSort(arr, 0, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][0] = time_spent;

        arr_init_const(arr, i);
        begin = clock();
        mergeSort(arr, 0, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][1] = time_spent;

        arr_init_increasing(arr, i);
        begin = clock();
        mergeSort(arr, 0, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][2] = time_spent;

        arr_init_decreasing(arr, i);
        begin = clock();
        mergeSort(arr, 0, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][3] = time_spent;

        printf("/");
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *MS_OUT = fopen("MS_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 4; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(MS_OUT, "%f\n", MS_results[j][i]);
        }
        fprintf(MS_OUT, "\n");
	}
    fclose(MS_OUT);
}

void TASK2_A_V_QS(){
    float QS_results[(N-10000)/interval][2];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_A(arr, i);
        begin = clock();
        quickSort_A_V(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][0] = time_spent;

        arr_init_V(arr, i);
        begin = clock();
        quickSort_A_V(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        QS_results[(i-10000)/interval][1] = time_spent;

        printf("/");
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *QS_A_V_OUT = fopen("QS_A_V_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 2; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(QS_A_V_OUT, "%f\n", QS_results[j][i]);
        }
        fprintf(QS_A_V_OUT, "\n");
	}
    fclose(QS_A_V_OUT);
}

void TASK2_A_V_HS(){
    float HS_results[(N-10000)/interval][2];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_A(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][0] = time_spent;

        arr_init_V(arr, i);
        begin = clock();
        heapSort(arr, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        HS_results[(i-10000)/interval][1] = time_spent;

        printf("/");
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *HS_A_V_OUT = fopen("heapS_A_V_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 2; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(HS_A_V_OUT, "%f\n", HS_results[j][i]);
        }
        fprintf(HS_A_V_OUT, "\n");
	}
    fclose(HS_A_V_OUT);
}

void TASK2_A_V_MS(){
    float MS_results[(N-10000)/interval][2];
    clock_t begin, end;
    double time_spent;
    srand(time(NULL));

    for (int i = 0; i < (N-10000)/interval; i++){
        printf("_" );
    }
    printf("\n");

    for (int i = 10000; i < N; i += interval){
        arr_init_A(arr, i);
        begin = clock();
        mergeSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][0] = time_spent;

        arr_init_V(arr, i);
        begin = clock();
        mergeSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        MS_results[(i-10000)/interval][1] = time_spent;

        printf("/");
    }
    printf("\n");

    int points = (N-10000)/interval;
    FILE *MS_A_V_OUT = fopen("MS_A_V_results.txt", "w");
    printf("\n");
    for (int i = 0; i < 2; i++){
	    for(int j = 0; j < points; j++){
		    fprintf(MS_A_V_OUT, "%f\n", MS_results[j][i]);
        }
        fprintf(MS_A_V_OUT, "\n");
	}
    fclose(MS_A_V_OUT);
}

int main(){
/*
    TASK1_BS();
    TASK1_HS();
    TASK1_CS();
    TASK1_ShS();

    TASK1_HS();
    TASK1_CS();
    TASK1_ShS();

    TASK2_QS();
    TASK2_HS();
    TASK2_MS();

    TASK2_A_V_QS();
    TASK2_A_V_HS();
    TASK2_A_V_MS();
*/


    clock_t begin, end;
    double time_spent;
    int start = 49999;
    int limit = 50001;
    for (int i = start; i <= limit; i++){
        arr_init_A(arr, i);
        begin = clock();
        quickSort(arr, 0, i-1);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
    }

    for (int i = start; i <= limit; i++){
        arr_init_A(arr, i+1);
        begin = clock();
        quickSort(arr, 0, i);
        end = clock();
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("%f\n", time_spent);
    }
    return 0;
}