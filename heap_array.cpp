#include<iostream>
using namespace std;
// g++ -std=c++11 file.cpp
void swap(int *x,int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

class MaxHeap{

	int *heap;
	int capacity;
	int heap_size;
	public:
		MaxHeap(int capacity);
		void MaxHeapify(int );
		
		int parent(int i){
			return (i-1)/2;
		}
		int left(int i){
			return 2*i+1;
		}
		int right(int i){
			return 2*(i+1);
		}
		int extractMax();
		
		void increaseKey(int i,int newValue);
		
		int getMax(){
			return heap[0];
		}
		void deleteKey(int i);
		
		void insertKey(int k);
		
		void heapSort();
		
		void BuildMaxHeap();
				
		void print();
};

/*constructor*/
MaxHeap::MaxHeap(int cap){
	heap_size=0;
	capacity = cap;
	heap = new int[cap];
}

// creates a max-heap for the given array

void MaxHeap::BuildMaxHeap(){
	int i;
	for(i=heap_size/2-1;i>=0;i--){
		MaxHeapify(i);
	}

}

/*assumption: left and right satisfy property
 and ith element is made to satisfy property*/ 
void MaxHeap::MaxHeapify(int i){
	int l=left(i);
	int largest;
	if(l<heap_size && heap[l]>heap[i]){
		largest = l;
	}
	else
		largest = i;
	int r = right(i);
	
	if(r<heap_size && heap[r]>heap[largest])
		largest = r;
	if(largest!=i){
		swap(&heap[i],&heap[largest]);
		MaxHeapify(largest);
	}
}

/*extract the largest element and arrange the elements to satisfy the property*/ 
int MaxHeap::extractMax(){

	if (heap_size <= 0){
		cout<<"ERROR"<<endl;
		return 0;
	}
    if (heap_size == 1)
    {
        heap_size--;
        return heap[0];
    }

	swap(&heap[0],&heap[heap_size-1]);
	heap_size--;
	MaxHeapify(0);
	return heap[heap_size];	
}

/*if a value is changed to higher value*/
void MaxHeap::increaseKey(int i,int new_value){
	if(heap[i]>new_value){
		cout<<"ERROR!"<<endl;
	}
	heap[i] = new_value;
	while(i!=0 && heap[parent(i)]<heap[i]){
		swap(&heap[i],&heap[parent(i)]);
		i = parent(i);
	}
}

/*delete an element*/
void MaxHeap::deleteKey(int i){
	
	if(i>=heap_size || i<0){
		cout<<"ERROR!"<<endl;
		return ;
	}
	
	increaseKey(i,getMax()+1);
	extractMax();
}

/*add an element*/
void MaxHeap::insertKey(int k){
	if(heap_size == capacity){
		cout<<"ERROR!\n";
		return ;
	}
	heap_size++;
	heap[heap_size-1] = k;
	int i = heap_size-1;
	while(i!=0 && heap[i]>heap[parent(i)]){
		swap(&heap[parent(i)],&heap[i]);
		i = parent(i);		
	}
}

/*sorting the heap*/
void MaxHeap::heapSort(){
	//BuildMaxHeap();
	int i = heap_size-1;
	int count=heap_size;
	while(i>0){
		swap(&heap[0],&heap[i]);
		heap_size--;
		MaxHeapify(0);
		i--;
	}
	heap_size = count;
	// but the array does not satisfy property now
}

void MaxHeap::print(){
	int i;
	if(heap_size==0)
		cout<<"Nothing to print"<<endl;
	else{
	for(i=0;i<heap_size;i++){
		cout<<heap[i]<<" ";
	}
	cout<<endl;
	}
}

int main(){

	MaxHeap maxHeap(5);
	maxHeap.insertKey(23);
	maxHeap.insertKey(5);
	maxHeap.insertKey(56);
	maxHeap.insertKey(16);
	maxHeap.insertKey(79);
	cout<<"Sorting the heap: ";
	maxHeap.heapSort();
	maxHeap.print();
	maxHeap.BuildMaxHeap();
	cout<<"Maximum element deleted: "<<maxHeap.extractMax()<<endl;
	cout<<"Sorting the heap: ";
	maxHeap.heapSort();
	maxHeap.print();
	maxHeap.BuildMaxHeap();
	maxHeap.insertKey(50);
	cout<<"inserted element: 50"<<endl;
	cout<<"Sorting: ";
	maxHeap.heapSort();
	maxHeap.print();
	maxHeap.BuildMaxHeap();
	maxHeap.print();
	cout<<"Deleted index 2 after Building heap"<<endl;
	maxHeap.deleteKey(2);
	cout<<"Sorting the heap: ";
	maxHeap.heapSort();
	maxHeap.print();
	maxHeap.BuildMaxHeap();
	return 0;
}
