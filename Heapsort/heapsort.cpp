//Cagla Midikli 150200011
#include <iostream> //This library is used for receiving data from the terminal or printing something to the terminal
#include <string>// This library allows us to store words as whole entities.Thus, when readingdata from the document, we can read the words as whole entities
#include <fstream>//The fstream library allows opening, closing, and reading files in C++.
#include <vector>//<vector> : To prevent unnecessary memory occupation, we are storing the array as avector.
#include <sstream>//: It enables us to split the strings read from a file under certain conditions
#include <chrono>// It is necessary for calculating the duration between the start and end of aprocess using the chrono librar
#include <cmath> //  It is necessary to use the ceil function to round up a fractional numberobtained from a division to the nearest integer.

using namespace std;
using namespace std::chrono;

struct Data{                                //I declare struct for be able to keep cities and their populations together 
    int population;        
    string city; 
};
vector<Data> cities;     //ı create a vector for to be array because ı dont know array size
void my_swap(Data &a, Data &b) {                 //It exchanges all attributes of the sent elements in the array.
    Data temp = a;
    a = b;
    b = temp;
}
                   
void max_heapify(vector<Data>& arr, int i,int size) {    
    int l =  2 * i;// the indices of the left and right children of the variable sent as anindex parameter are calculated.
    int r = 2 * i + 1;
    int largest = i;
    if(l<=size && (arr[l].population > arr[i].population)){ //If at least one of the left or right children has an indexgreater than the current index, the function swaps the element with the largest child.
            largest= l;}
    else{largest = i;}
    if(r<=size && arr[r].population > arr[largest].population){
            largest= r;}
    if(largest != i){
            my_swap(arr[i],arr[largest]);
            max_heapify(arr,largest,size);//This function ensures the ordered arrangement of items along that line by recursively calling itself.
    }
    
}

void dary_max_heapify(vector<Data>& arr, int i,int size,int d) {    //, given an index as a parameter, identifies the indices of its children
    int child;
     int largest = i;
    for(int j = 0; j < d ; j++){
        child  = d*i +j + 1;                                    //calcuşate child index
        if(child < size && arr[child].population > arr[largest].population){largest = child;} ////If at least one of the left or right children has an indexgreater than the current index, the function swaps the element with the largest child.
    }
    if(largest != i){
            my_swap(arr[i],arr[largest]);
            dary_max_heapify(arr,largest,size,d); // recursively calling itself.
    }
}
void dary_build_max_heap(vector<Data>& arr,int size,int d){  //In the dary max heapify function, the sorting operation obtained for a single branch isapplied to all branches.T
  
    for(int i=(size/d) ; i >= 0; i--){  //call dary_max_heapify for all branch
        
        dary_max_heapify(arr,i,size,d);
    }
}

Data dary_extract_max(vector<Data>& arr, int size,int d){//Time complexity is O(log_d n)
    if (size < 1){
        cout<<"heap is can not build because of size"<<endl;
    }
    Data max = arr[0]; //return max value
    arr[0] = arr[size-1];    //first indexs value equals to last.
    arr.pop_back(); //delete the last element
    size = size -1;//decrease vector size variable
    max_heapify(arr,1,size);    //call max heapify
    return max;
}

Data heap_extract_max(vector<Data>& arr, int size){
    if (size < 1){
        cout<<"heap is can not build because of size"<<endl;
    }
    Data max = arr[0]; //return max value
    arr[0]=arr[size-1]; //first indexs value equals to last.
    arr.pop_back();  //delete the last element
    size = size -1;//decrease vector size variable
    max_heapify(arr,1,size);
    return max;
}
void heap_increase_key(vector<Data>& arr,int i,int key){
    if(key< arr[i].population){
        cout<<"New key value is smaller than current index value."<<endl;
    }
    arr[i].population = key;//change the value in index
    int parent = (i - 1) / 2; //calculate parent index
    while(i>0 && arr[parent].population < arr[i].population){//if parent smaller than index population, exchange their index value
        my_swap(arr[i], arr[parent]);
        i = parent ;
        parent = (i - 1) / 2;  //calculate parent index
    }
    }
void dary_increase_key(vector<Data>& arr,int i,int key,int d){//Time complexity is O(log_d n)
    if(key< arr[i].population){
        cout<<"New key value is smaller than current index value."<<endl;
        }
    arr[i].population = key;//change the value in index
    int parent = ceil((double)i/d) - 1;//calculate parent index
    while(i>0 && arr[parent].population < arr[i].population){    //if parent smaller than index population, exchange their index value 
        my_swap(arr[i], arr[parent]); 
        i = parent;
        parent = ceil((double)i/d) - 1;   //let's move up one line
    }
}
void max_heap_insert(vector<Data>& arr, int size,int key,string city){
    size = size +1; //increase size value
    arr[size-1].population = -100000; //The new element's population is equals to -100000 to will be that it is less than any existing element in the max-heap. Normally ı should INT MIN but i can not decleare any other libraries
    Data news; //create new data element
    news.population = key; //new elements population equals to key population
    news.city = city;//new elements city name equals to key city name
    arr.push_back(news);//pust the new element to vecrtor
    heap_increase_key(arr,size-1,key);//call heap increase key 
}
void dary_insert_element(vector<Data>& arr, int size,int key, int d,string city){//Time complexity is O(log_d n)
    size = size +1;//increase size value
    arr[size-1].population = -100000;//The new element's population is equals to -100000 to will be that it is less than any existing element in the max-heap.  Normally ı should INT MIN but i can not decleare any other libraries
    Data news; //create new data element
    news.population = key;//new elements population equals to key population
    news.city =city;//new elements city name equals to key city name
    arr.push_back(news);//pust the new element to vecrtor
    dary_increase_key(arr,size-1,key,d);//call heap increase key 
}
Data heap_maximum(vector<Data>& arr){
 
    return arr[0];//return the max element(root)
}
int dary_calculate_height(vector<Data>& arr,int d,int size){
    int height = 0; //root node is 0
    int k= size-1;      //
    int power=1;        //to calculate power of number
    while(k>= power ){
        power = d * power;//for find number of nodes each line
        k = k - power;          //number of remaining node
        height++;
    }
    if(k>0){height++;}          //if k is bigger than 0, ı need 1 row more.
  
    return height;
}

void build_max_heap(vector<Data>& arr,int size){
    for(int i=size/2 -1 ; i >= 0; i--){ //call max_heapify for all branch
        max_heapify(arr,i,size);
    }
}

void heapsort(vector<Data>& arr, int size) {
    build_max_heap(arr, size);      //call build_mac_heap functions
    for (int i = size - 1; i >= 1; i--) { 
        my_swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);//call the max_heapify
    }
}

string dik(int (&arr)[3],string one,string two, string three,string func){//for read d,i and k value
    int pop;
    string city,pops;
    city =" ";
        char d = one[0];        //take the first char of string
        char i = two[0];//take the first char of string
        char l = three[0];//take the first char of string
        one.erase(one.begin());//erase first char in string
        two.erase(two.begin());//erase first char in string
        three.erase(three.begin());//erase first char in string
        if(d == 'd'){//To find out what the first command arguement is
            int k;
            k= stoi(one);//convert string to integer
            arr[0] = k;//Index 1 of the array holds the value of d
        }
        else if(d == 'i'){//To find out what the first command arguement is
            int k;
            k= stoi(one);//convert string to integer
            arr[1] = k ;//Index 1 of the array holds the value of i
        }
        else if(d == 'k'){//To find out what the first command arguement is
            if(func == "dary_insert_element" || func =="max_heap_insert"){
            one.erase(one.begin());//erase first char in string
            stringstream one_line(one);
            getline(one_line, city, '_');                      //to sepearte until _ in line                     
            getline(one_line, pops);
            pop = stoi(pops);//convert string to integer
            arr[2] = pop;//Index 2 of the array holds the value of k
            }      
            else{//for increase key
                int k;//ı read just number valu not name for insertion
                k= stoi(one);//convert string to integer
                arr[2] = k ;//Index 2 of the array holds the value of k
            }
        }
        if(i == 'd'){
            int k;
            k= stoi(two);//convert string to integer
            arr[0] = k;
        }
        else if(i == 'i'){
            int k;
            k= stoi(two);//convert string to integer
            arr[1] = k;
        }
        else if(i == 'k'){
            if(func == "dary_insert_element" || func =="max_heap_insert"){
            two.erase(two.begin());
            stringstream one_line(two);
            getline(one_line, city, '_');                      //to sepearte until semicolon in line                     
            getline(one_line, pops);
            pop = stoi(pops);//convert string to integer
            arr[2] = pop;//Index 2 of the array holds the value of k
            }      
            else{
                int k;
                k= stoi(two);//convert string to integer
                arr[2] = k ;//Index 2 of the array holds the value of k
            }
        }
        if(l == 'd'){
            int k;
            k= stoi(three);//convert string to integer
            arr[0] = k;
        }
        else if(l == 'i'){
            int k;
            k= stoi(three);//convert string to integer
            arr[1] = k;
        }
        else if(l == 'k'){
            if(func == "dary_insert_element" || func =="max_heap_insert"){
            three.erase(three.begin());
            stringstream one_line(three);
            getline(one_line, city, '_');                      //to sepearte until semicolon in line                     
            getline(one_line, pops);
            pop = stoi(pops);//convert string to integer
            arr[2] = pop;//Index 2 of the array holds the value of k
            }      
            else{
                int k;
                k= stoi(three);//convert string to integer
                arr[2] = k ;//Index 2 of the array holds the value of k
            }
        }
    return city; }//return city value for insert function
int main(int argc, char* argv[]) { 
    auto start_time = high_resolution_clock::now();//time started
    int arr[3]; 
    arr[0] = -1;        //store d value
    arr[1] = -1;        //store i value
    arr[2] = -1;        //store k value
    string city_name;        
    string temp = "sifir"; 
    if(argv[4]&&argv[5]&&argv[6]){
    city_name = dik(arr,argv[4],argv[5],argv[6],argv[2]);}
    else if(argv[4]&&argv[5]){
    city_name = dik(arr,argv[4],argv[5],temp,argv[2]);}//if command line arguement is smaller than 3 ı send temporary value thats mean nothing to function 
    else if(argv[4]){
    city_name = dik(arr,argv[4],temp,temp,argv[2]);}                                                                               
    string file_number = argv[1];    
    string line;
    ifstream csvFile(file_number);
    int size=0;                         
    if(!csvFile.is_open()){                                 
        cerr << "File is not open" << endl;
        return 1;
    }
    while(getline(csvFile, line)){                         
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
    if (size < 1) {
        cout << "Not enough data in the file for building heapsort";}
    csvFile.close();
    string k = argv[2];
    if( k == "heapsort"){
        heapsort(cities,size);
        ofstream outFile(argv[3]);
        for(int i = 0; i< size ;i++){                               //to write the result to output file
            outFile << cities[i].city <<";"<< cities[i].population<<endl;
        }
        outFile.close();
    } 
    else if( k == "dary_calculate_height"){
        int height = dary_calculate_height(cities,arr[0],size);//find to height
        ofstream outFile(argv[3]);
        outFile << height << endl;       //to write the result to output file
        outFile.close();
    }
    else if( k == "heap_increase_key"){
        build_max_heap(cities,size);//for build max_heap
        heap_increase_key(cities,size-1,arr[2]);
        ofstream outFile(argv[3]);
        for(int i = 0; i< size ;i++){                               //to write the result to output file
            outFile << cities[i].city <<";"<< cities[i].population<<endl;
        }
        outFile.close();
    }
    else if( k == "dary_increase_key"){
        dary_build_max_heap(cities,size,arr[0]);
        dary_increase_key(cities,arr[1]-1,arr[2],arr[0]);
        ofstream outFile(argv[3]);
        for(int i = 0; i< size ;i++){                               //to write the result to output file
            outFile << cities[i].city <<";"<< cities[i].population<<endl;
        }
        outFile.close();
    }
    else if( k == "max_heapify"){
            max_heapify(cities,arr[2],size);
            //max_heapify(cities,arr[2],arr[1]); for index include max_heapify
            ofstream outFile(argv[3]);
            for(int i = 0; i< size ;i++){                               //to write the result to output file
                outFile << cities[i].city <<";"<< cities[i].population<<endl;
            }
            outFile.close();
    }
    else if( k == "build_max_heap"){
            build_max_heap(cities,size);
            ofstream outFile(argv[3]);
            for(int i = 0; i< size ;i++){                               //to write the result to output file
                outFile << cities[i].city <<";"<< cities[i].population<<endl;
            }
            outFile.close();
    }
    else if( k == "heap_extract_max"){
            build_max_heap(cities,size);
            Data k = heap_extract_max(cities,size);
            ofstream outFile(argv[3]);                             //to write the result to output file
            outFile << k.city <<";"<< k.population<<endl;
            outFile.close();
/*           for(int i = 0; i< size ;i++){                               //to write the result to terminal
            cout << cities[i].city <<";"<< cities[i].population<<endl;
        }*/ 
    }
    else if( k == "heap_maximum"){
            build_max_heap(cities,size);
            Data k = heap_maximum(cities);
            ofstream outFile(argv[3]);                             //to write the result to output file
            outFile << k.city <<";"<< k.population<<endl;
            outFile.close();
    }
    else if( k == "max_heap_insert"){
        build_max_heap(cities,size);
        max_heap_insert(cities,size,arr[2],city_name);
        ofstream outFile(argv[3]);
        for(int i = 0; i< size +1 ;i++){                               //to write the result to output file
            outFile << cities[i].city <<";"<< cities[i].population<<endl;
        }
        outFile.close();
    } 
    else if(k == "dary_build_max_heap"){
        ofstream outFile(argv[3]);
        dary_build_max_heap(cities,size,arr[0]);
            for(int i = 0; i< size ;i++){                               //to write the result to output file
                outFile << cities[i].city <<";"<< cities[i].population<<endl;
            }
    }
    else if( k == "dary_extract_max"){          
            dary_build_max_heap(cities,size,arr[0]);
            Data l = dary_extract_max(cities,size,arr[0]);  // to find max value
            ofstream outFile(argv[3]);                             //to write the result to output file
            outFile << l.city <<";"<< l.population<<endl;
            outFile.close();
    }
    else if( k == "dary_insert_element"){
        dary_build_max_heap(cities,size,arr[0]);//build max_heap
        dary_insert_element(cities,size,arr[2],arr[0],city_name);
            ofstream outFile(argv[3]);
            for(int i = 0; i< size+1 ;i++){                               //to write the result to output file
                outFile << cities[i].city <<";"<< cities[i].population<<endl;}
            outFile.close();       
    }
   
   auto end_time = high_resolution_clock::now();
   auto elapsed_time_ns = duration_cast<nanoseconds>(end_time - start_time).count(); //for calculate time
    cout <<"Time taken by Heapsort  '" << elapsed_time_ns << " ns" << endl;
   return 0;
}
