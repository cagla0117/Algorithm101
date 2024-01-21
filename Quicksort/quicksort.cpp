//Cagla Midikli 150200011
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Data{                                //I declare struct for be able to keep cities and their populations together
    
    int population;        
    string city; 
};
vector<Data> cities;                        //ı create a vector for to be array because ı dont know array size

ofstream outFiletxt("log.txt");             //for the write log.txt, open it

void swap(int &a, int &b) {                 //It exchanges all attributes of the sent elements in the array.
    int temp = a;
    a = b;
    b = temp;
}

void print_array(vector<Data>& arr, int left,int right,int pivot){          //To print each recurrence step one by one in the requested format.
    cout << "Pivot: "<<arr[pivot].population << "   Array: " ;              //print pivot value
    cout<<"[";
        for (int i = left; i < right+1; i++) {                                 //to print all of subarrays element
            cout << arr[i].population;
            if(i < right){
                cout<<", ";
            }
        }
    cout<<"]";
    cout<<endl;
}

void print_array_txt(vector<Data>& arr, int left, int right, int pivot) {       //To print each recurrence step one by one in the requested format to the "log.txt" file
    outFiletxt << "Pivot: " << arr[pivot].population << "   Array: ";           //print pivot value
    outFiletxt << "[";
    for (int i = left; i < right +1; i++) {                                     //to print all of subarrays element
        outFiletxt << arr[i].population ;
        if(i < right){outFiletxt <<  ",";}
    }
    outFiletxt << "]";
    outFiletxt << endl;    
}

int partition(vector<Data>& arr, int left_index, int right_index) {         //It considers the last element of the sent array as the pivot and arranges the elements smaller than the pivot at the beginning of the array and the ones greater than the pivot at the end.
    int i = left_index;
    int pivot = arr[right_index].population;
    for (int j = i ; j < right_index; j++) {
        if (arr[j].population <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right_index]);
    return i;
}

void option(int opt,vector<Data>& arr,int left_index,int right_index ){      //"To determine the pivot, we have three different methods. By default, the last element becomes the pivot. If 'r' is chosen, a random value is selected from the array, and this is swapped with the last element. This way, when entering the partition step, the randomly selected element becomes the pivot."
    int f;
    if(opt == 'r'){ f = (rand() % (right_index - left_index + 1)) + left_index;
        swap(arr[f],arr[right_index]);}                                      //for partition part select the pivot as last element so i exchange the real pivot and last element
    else if(opt == 'm'){
        int t[3];
        int i = (rand() % (right_index - left_index + 1)) + left_index;     //to pick up 3 randomindex value interval boundaries.
        int y = (rand() % (right_index - left_index + 1)) + left_index;
        int z = (rand() % (right_index - left_index + 1)) + left_index;
        t[0] = arr[i].population;                                           //random indexs population value
        t[1] = arr[y].population;
        t[2] = arr[z].population;
        for(int s= 0; s< 3 ; s++){
            for (int k = 0; k < s; k++)                                     //for sorting random values
            {
                if(t[s] <t[k]){
                    swap(t[s],t[k]);
                }
            }            
        }
        
        if(t[1] == arr[i].population){swap(arr[i],arr[right_index]);}
        else if(t[1] == arr[y].population){swap(arr[y],arr[right_index]);}
        else if(t[1] == arr[z].population){swap(arr[z],arr[right_index]); }}
   //if option is not r and m it is last so pivot is last element is default  
    
}
void insertionsort(vector<Data>& arr, int left_index, int right_index) {    //to sorting small value vith O(n^2) complexity ascending order.
    for (int i = left_index + 1; i <= right_index; i++) {
        int j = i;
        while (j > left_index && arr[j].population < arr[j - 1].population) {
            swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}
void quickSort(vector<Data>& arr, int left_index, int right_index, char opt, int k ,bool v) {
    int f;
    if (left_index < right_index) {                                         //check the it is not base case 
        
            option(opt,arr,left_index,right_index);                         //find the pivot
            if(v){print_array_txt(arr,left_index,right_index,right_index);} //if verbose is true go to print_array_txt
            int partitionIndex = partition(arr,left_index,right_index);     //call the partition function.
            quickSort(arr, left_index, partitionIndex-1 ,opt,k, v);         //call hybridsort recursively
            quickSort(arr, partitionIndex + 1, right_index,opt,k ,v);       //call hybridsort recursively

    }}

void hybridSort(vector<Data>& arr, int left_index, int right_index, char opt, int k, bool v) {      // Therefore, in the hybridSort algorithm, when the number of elements in subarrays is ledata_line than or equal to k, insertion sort is utilized.
    if (left_index < right_index) {
        if(right_index - left_index > k ) {
            option(opt,arr,left_index,right_index);       //to chose pivot     
            if(v ){print_array_txt(arr,left_index,right_index,right_index);}    //if verbose is true go to print_array_txt
            int partitionIndex = partition(arr,left_index,right_index);         //call the partition function.
            hybridSort(arr, left_index, partitionIndex-1 ,opt,k ,v);            //call hybridsort recursively
            hybridSort(arr, partitionIndex + 1, right_index,opt,k ,v);          //call hybridsort recursively
}
        else{
            insertionsort(arr,left_index,right_index);                          //if sub arrays small enough call the insertion sort
        }

    }}
int main(int argc, char* argv[]) {                                              //To get arguments from command line
    srand(time(NULL));                                                          //To reset the rand function  
    string file_number = argv[1];    
    string line;
    ifstream csvFile(file_number);
    int size=0;                         //open file for read
    if(!csvFile.is_open()){                                 //if cant open file giv error
        cerr << "File is not open" << endl;
        return 1;
    }
    while(getline(csvFile, line)){                          //to read line by line
        stringstream data_line(line);
        Data datam;
        string city;     
        string population;
        getline(data_line, city, ';');                      //to sepearte until semicolon in line
        datam.city = city;                                  //equal to structs new elements city attribute 
        getline(data_line, population);
        datam.population = stoi(population);                //convert to string to integer 
        cities.push_back(datam);                            //push new element to array
        size++;}  
    if (cities.size() < 1) {
        cout << "Not enough data in the file";}
    csvFile.close();
    int k = stoi(argv[3]);                                     //convert argument(k) to integer 
    char option = argv[2][0];argv[2][0];
    bool verbose = false;
    verbose = (argc > 5 && argv[5][0] == 'v');                  //decide verbose is tru or false if
    auto start_time = high_resolution_clock::now();             //measure time elapsed
    if(k == 1){                                                 //if k=1 naive quicksort will call
        quickSort(cities, 0, size-1,option,k,verbose);
    }
    else{
        hybridSort(cities, 0, size-1,option,k,verbose);
    }
    auto end_time = high_resolution_clock::now();
    ofstream outFile(argv[4]);
    for(int i = 0; i< size ;i++){                               //to write the result to output file
        outFile << cities[i].city <<";"<< cities[i].population<<endl;
    }
    outFile.close();
    outFiletxt.close();
    auto elapsed_time_ns = duration_cast<nanoseconds>(end_time - start_time).count();  // Geçen süreyi nanosaniye cinsinden al
    cout <<"Time taken by Quicksort with pivot strategy '" <<option <<"' and threshold "<< k<<": "  << elapsed_time_ns << " ns" << endl;
    return 0;
}
