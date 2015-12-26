#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

struct tree{
	int data;
	string dir;
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
		int* heapSort();
		void BuildMaxHeap();
		void print(treePtr ptr);
};

/*constructor*/
MaxHeap::MaxHeap(){
	heap_size = 0;
	direction="-1";
}

/*add an element*/
void MaxHeap::insertKey(int k){
		int i=0;
		treePtr temp = new tree;
		temp = root;
		for(i=0;i<=direction.length()-1 && direction!="-1";i++){
			if(direction[i]=='0'){
					if(temp->leftPtr==NULL)
						temp->leftPtr = new tree;
					temp = temp->leftPtr;
				}
				if(direction[i]=='1'){
					if(temp->rightPtr==NULL)
						temp->rightPtr = new tree;
					temp = temp->rightPtr;
				}
		}
		temp->data = k;
		temp->dir = direction;
		heap_size++;
		order_max(root,direction,0);
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
		string s = ptr->dir;
		int i = s.length()-1;
		ptr->data = new_value;
		order_max(root,s,0);
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
		print(ptr->leftPtr);
		cout<<ptr->data<<",";
		print(ptr->rightPtr);
	}

}

/*sorting the heap*/
int* MaxHeap::heapSort(){

	if(heap_size==0){
		cout<<"Nothing to print"<<endl;
	}
	else{
		int n = heap_size;
		int* sorted = new int;
		int i=0;
		while(heap_size>0){
			sorted[i] = extractMax();
			i++;
		}
		/*heap does not exist after this*/
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
	int* temp;
	temp = maxHeap.heapSort();
	int i=0;
	while((temp+i)!=NULL && i<7){
		cout<<*(temp+i)<<endl;
		i++;
	}
	maxHeap.print(maxHeap.getRootPtr());
	return 0;
}
