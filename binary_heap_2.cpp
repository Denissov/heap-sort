#include <iostream>
#include <cmath>
using namespace std;

bool heap_check_up(double *heap, int N, int pos){
        while (pos != 1){
                if (heap[pos] > heap[pos / 2])
                        return false;
                pos = pos / 2;
        }
        return true;
}

bool heap_check_down(double *heap, int N, int pos){
        while (2 * pos <= N || 2 * pos + 1 <= N){
                if (heap[pos] < heap[2 * pos] || (2 * pos + 1 <= N && heap[pos] < heap[2 * pos + 1]))
                        return false;
                if (heap[2 * pos] >= heap[2 * pos + 1] || 2 * pos + 1 > N)
                        pos = 2 * pos;
                else
                        pos = 2 * pos + 1;
        }
        return true;
}

void Sift_Up(double *heap, int N, int ind){
        while (!(heap_check_up(heap, N, ind))){
        	swap(heap[ind], heap[ind / 2]);
                ind = ind / 2;
        }
}

void Sift_Down(double *heap, int N, int ind){
	while (!(heap_check_down(heap, N, ind))){
        	if (heap[2 * ind] >= heap[2 * ind + 1] || 2 * ind + 1 > N){
                	swap(heap[ind], heap[2 * ind]);
                        ind = 2 * ind;
                }
                else{
                	swap(heap[ind], heap[2 * ind + 1]);
                        ind = 2 * ind + 1;
                }
        }
}

void Extract_Max(double *heap, int N){
        int i = 1;
        while (N != 1){
                swap(heap[1], heap[N]);
                N = N - 1;
                while (!(heap_check_down(heap, N, i))){
                        if (heap[2 * i] >= heap[2 * i + 1] || 2 * i + 1 > N){
                                swap(heap[i], heap[2 * i]);
                                i = 2 * i;
                        }
                        else{
                                swap(heap[i], heap[2 * i + 1]);
                                i = 2 * i + 1;
                        }
                }
		for (int pos = 1; pos <= N; pos++)
			cout << heap[pos] << " ";
		cout << "\n";
                i = 1;
        }
}

void Extract_Max(double *heap, int &N, int i){
	if (N == 0){
		cout << "No numbers to extract: " << -1 << "\n";
		return;
	}
	else if (N == 1){
		cout << "Index of sorted element and extracted maximum: " << 0 << " " << heap[N] << "\n";
		N = N - 1;
		return;
	}
        swap(heap[1], heap[N]);
	double max = heap[N];
	N = N - 1;
        while (!(heap_check_down(heap, N, i))){
        	if (heap[2 * i] >= heap[2 * i + 1] || 2 * i + 1 > N){
                	swap(heap[i], heap[2 * i]);
                        i = 2 * i;
                }
                else{
                	swap(heap[i], heap[2 * i + 1]);
                        i = 2 * i + 1;
                }
        }
	cout << "Index of sorted element and the extracted maximum: " << i << ", " << max << '\n';
}

void Insert(double *heap, int &size, int N, double x){
	if (size == N){
		cout << "The queue is full: " << -1 << '\n';
		return;
	} 
	size = size + 1;
	heap[size] = x;
	int ind = size;
	while (!(heap_check_up(heap, size, ind))){
		swap(heap[ind], heap[ind / 2]);
		ind = ind / 2;
	}
	cout << "The index of added element: " << ind << '\n';	
}

void Build_Heap1(double *mas, int N){
	for (int i = 2; i <= N; i++)
		Sift_Up(mas, N, i);
	cout << "heap:\n";
	for (int i = 1; i <= N; i++)
		cout << mas[i] << " ";
	cout << "\n";
}

void Build_Heap2(double *mas, int N){
	for (int i = N / 2; i >= 1; i--)
		Sift_Down(mas, N, i);
	cout << "heap:\n";
	for (int i = 1; i <= N; i++)
		cout << mas[i] << " ";
	cout << "\n";
}

void HeapSort(double *mas, int N){
	Build_Heap2(mas, N);
	Extract_Max(mas, N);
	cout << "ordered set:\n";
	for (int i = 1; i <= N; i++)
		cout << mas[i] << " ";
	cout << "\n";
	
}

void Priority_Queue(){
	int N, M, size = 0;
	cout << "Enter the max size of Priority Queue:\n";
	cin >> N;
	cout << "Enter the number of requests:\n";
	cin >> M;
	double *mas = new double[N + 1];
	bool *type = new bool[M];
	int *num = new int[M];
	cout << "Enter the requests: type (0,1), parameter (number to be added):\n";
	for (int i = 0; i < M; i++){
		cin >> type[i];
		if (type[i])
			cin >> num[i];
		else
			num[i] = 0;
	}
	for (int i = 0; i < M; i++){
		if (!(type[i]))
			Extract_Max(mas, size, 1);
		else
			Insert(mas, size, N, num[i]);
	}
	cout << "The queue itself: ";
	for (int i = 1; i <= size; i++)
		cout << mas[i] << " ";
	cout << '\n';
	delete [] type;
	delete [] num;
	delete [] mas;
}

int main() {
	int N;
	cout << "Enter the size of array:\n";
	cin >> N;
	double *mas = new double[N + 1];
	cout << "Enter the elements of array:\n";
	for (int i = 1; i <= N; i++)
		cin >> mas[i];
	HeapSort(mas, N);
	Priority_Queue();
	return 0;
}
