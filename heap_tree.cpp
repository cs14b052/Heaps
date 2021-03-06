#include<iostream>
#include<string>
#include<cstdlib>
#include<queue>
#include<vector>
using namespace std;
// g++ -std=c++11 file.cpp
struct tree{
	int data;
	struct tree *parent = NULL;
	struct tree *leftPtr = NULL;
	struct tree *rightPtr = NULL;
};

typedef tree tree;
typedef tree *treePtr;

void swap(treePtr x,treePtr y){

	treePtr temp = new tree;
	temp->data = x->data;
	x->data = y->data;
	y->data = temp->data;
	
}

string getDirection(int n){
	
	if(n==0)
		return "-1";

	string s = "";
	while(n>0){
		int x = n%2;
		n = n/2;
		string a = to_string(x) + s;
		if(n!=0)
			s = a;
	}
	return s;
}

void order_max(treePtr root,string s,int i){
	if(root!=NULL && i<s.length()){
		if(s[i]=='1'){i=i+1;
			order_max(root->rightPtr,s,i);
			if(root->rightPtr!=NULL && root->rightPtr->data > root->data){
				swap(root,root->rightPtr);}
		}
		else if(s[i]=='0'){i=i+1;
			order_max(root->leftPtr,s,i);
			if(root->leftPtr!=NULL && root->leftPtr->data>root->data)
				swap(root,root->leftPtr);
		}
	}
}


class MaxHeap{

	treePtr root = new tree;
	treePtr prevPtr;
	string direction;
	int heap_size;
	public:
		MaxHeap();
		
		void MaxHeapify(treePtr ptr);
		treePtr parent(treePtr ptr);
		treePtr left(treePtr ptr){
			return ptr->leftPtr;
		}
		treePtr right(treePtr ptr){
			return ptr->rightPtr;
		}
		
		int extractMax();
		
		void increaseKey(treePtr ptr,int new_value);
		
		int getMax(){
			return (root)->data;
		}
		treePtr getRootPtr(){
			return root;
		}
		void deleteKey(treePtr ptr);
		void insertKey(int k);
		vector<int> heapSort();
		void BuildMaxHeap(int *a);// creates a max-heap for given array
		void BuildMaxHeap(vector<int> a);// creates a max-heap for given vector of integers
		void build_heap_property(treePtr root);
		void print(treePtr ptr);
};

/*constructor*/
MaxHeap::MaxHeap(){
	heap_size = 0;
	direction="-1";
}


void MaxHeap::BuildMaxHeap(int *a){
	/* accessing every element once,so it should be O(n)*/
	root = new tree;
	root->data = a[0];
	heap_size++;
	int n = sizeof(a)/sizeof(*a);cout<<sizeof(a);
	queue<treePtr> Queue;
	Queue.push(root);
	int i=1;
	while(i<7){
		treePtr temp = Queue.front();
		Queue.pop();
		treePtr Left = new tree;
		Left->data = a[i];
		Queue.push(Left);
		temp->leftPtr = Left;
		heap_size++;i++;
		if(i<n){
			treePtr Right = new tree;
			Right->data = a[i];
			Queue.push(Right);			
			heap_size++;i++;
			temp->rightPtr = Right;
		}
	}
	/* T(n) = 2T(n/2) + O(logn)*/
	build_heap_property(root);
}
void MaxHeap::BuildMaxHeap(vector<int> a){

	root = new tree;
	vector<int>:: iterator i=a.begin();
	root->data = *i;
	heap_size++;
	queue<treePtr> Queue;
	Queue.push(root);
	i++;
	while(i<a.end()){
		treePtr temp = Queue.front();
		Queue.pop();
		treePtr Left = new tree;
		Left->data = *i;
		Left->parent = temp;
		Queue.push(Left);
		temp->leftPtr = Left;
		heap_size++;i++;
		if(i<a.end()){
			treePtr Right = new tree;
			Right->data = *i;
			Right->parent = temp;
			Queue.push(Right);			
			heap_size++;i++;
			temp->rightPtr = Right;
		}
	}
	build_heap_property(root);
}
/*add an element*/
void MaxHeap::insertKey(int k){
		int i=0;
		treePtr temp = new tree;
		treePtr Parent = new tree;
		Parent = root;
		temp = root;
		for(i=0;i<=direction.length()-1 && direction!="-1";i++){
			if(direction[i]=='0'){
					if(temp->leftPtr==NULL){
						Parent = temp;
						temp->leftPtr = new tree;
					}
					temp = temp->leftPtr;
				}
				if(direction[i]=='1'){
					if(temp->rightPtr==NULL){
						Parent  = temp;
						temp->rightPtr = new tree;
					}
					temp = temp->rightPtr;
				}
		}
		temp->data = k;
		temp->parent = Parent;
		treePtr ptr = new tree;
		ptr = temp;
		heap_size++;
		while(ptr->parent!=root || ptr->parent->data < ptr->data){
			swap(ptr->parent,ptr);
			ptr = ptr->parent;
		}
		direction = getDirection(heap_size+1);
}

/*assumption: left and right satisfy property
 and ith element is made to satisfy property*/ 
void MaxHeap::MaxHeapify(treePtr ptr){

	if(ptr!=NULL){
		treePtr temp = new tree;
		temp = ptr;
		if(ptr->leftPtr!=NULL && ptr->data < ptr->leftPtr->data)
			temp = ptr->leftPtr;
		if(ptr->rightPtr!=NULL && temp->data < ptr->rightPtr->data)
			temp = ptr->rightPtr;

		if(temp!=ptr){
			swap(ptr,temp);
			MaxHeapify(temp);}
	}
}

void MaxHeap::build_heap_property(treePtr root){
	if(root!=NULL){
		build_heap_property(root->leftPtr);
		build_heap_property(root->rightPtr);
		MaxHeapify(root);
	}
}

/*extract the largest element and arrange the elements to satisfy the property*/ 
int MaxHeap::extractMax(){

	if(heap_size==0){
		printf("Empty!!!");
		return 0;
	}
	else if(heap_size==1){
		heap_size--;
		int var = root->data;
		direction = "-1";
		root = NULL;
		return var;
	}
	else{
			heap_size--;
			direction = getDirection(heap_size+1);
			int num = direction.length();
			treePtr temp = new tree;
			treePtr prev = new tree;
			temp = root;
			int i=0,t;
			while(i!=num){
				prev = temp;
				t = 1;
				if(direction[i]=='0'){
					t = 0;
					temp = temp->leftPtr;}
				else
					temp = temp->rightPtr;
				i++;
			}

			swap(root,temp);		
			int var = temp->data;
			if(t == 0)
				prev->leftPtr = NULL;
			else
				prev->rightPtr = NULL;
			
			MaxHeapify(root);
			return var;	
		
	}

}

/*if a value is changed to higher value*/
void MaxHeap::increaseKey(treePtr ptr,int new_value){

	if(new_value<=ptr->data)
		cout<<"ERROR!"<<endl;
	else{
		ptr->data = new_value;
		while(ptr->parent!=root || ptr->parent->data<ptr->data){
			swap(ptr,ptr->parent);
			ptr=ptr->parent;
		}
	}
}

/*delete an element*/
void MaxHeap::deleteKey(treePtr ptr){
	
	if(heap_size==0 || ptr==NULL){
		cout<<"EMPTY!"<<endl;
	}
	else{
		increaseKey(ptr,getMax()+1);
		extractMax();
		direction = getDirection(heap_size+1);
	}

}
void MaxHeap::print(treePtr ptr){

	if(ptr!=NULL){
		cout<<ptr->data<<" ";
		print(ptr->leftPtr);
		print(ptr->rightPtr);
	}

}

/*sorting the heap*/
vector<int> MaxHeap::heapSort(){

	if(heap_size==0){
		cout<<"Nothing to print"<<endl;
	}
	else{
		int n = heap_size;
		vector<int> sorted;
		while(heap_size>0){
			sorted.push_back(extractMax());
		}
		/*heap does not exist after this*/
		BuildMaxHeap(sorted);
		return sorted;
	}

}
int main(){

	MaxHeap maxHeap;
	maxHeap.insertKey(23);
	maxHeap.insertKey(5);
	maxHeap.insertKey(56);
	maxHeap.insertKey(16);
	maxHeap.insertKey(79);
	maxHeap.insertKey(132);
	maxHeap.insertKey(569);
	cout<<"PreOrder traversal of tree: ";
	maxHeap.print(maxHeap.getRootPtr());
	cout<<endl;
	cout<<"Maximum element deleted: "<<maxHeap.extractMax()<<endl;
	cout<<"PreOrder traversal of tree: ";
	maxHeap.print(maxHeap.getRootPtr());
	cout<<endl;
	maxHeap.insertKey(80);
	cout<<"inserted element: 80"<<endl;
	cout<<"PreOrder traversal of tree after inserting 80: ";
	maxHeap.print(maxHeap.getRootPtr());
	cout<<endl;
	vector<int> temp;
	temp = maxHeap.heapSort();
	vector<int>::iterator i=temp.begin();
	cout<<"Sorted heap: ";
	while(i<temp.end()){
		cout<<*i<<" ";
		i++;
	}
	cout<<endl;
	cout<<"Preorder traversal of heap: ";
	maxHeap.print(maxHeap.getRootPtr());
	cout<<endl;
	return 0;
}
