#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/algorithm/string.hpp>



using namespace std;

void writeToFile(string temp);
void* dna(void* rank);
long ready(long start, long fin);
//using std::cout;
//using std::cerr;
//using std::endl;


long length, thread_count, counter;
string mouse, file3;
unordered_map <string, int> myMap;
pthread_mutex_t mymutex;
ofstream of;



string upper(string& str) {

	transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}


int main(int argc, char** argv) {

	pthread_t* thread_handles;
	//ifstream fileStream("hashed_reads_file",ifstream::in);
	//fileStream("hashed_reads_file",std::ifstream::in);
	
	//myMap["Testing"] = 23;
	//cout<<myMap["Testing"]<<endl;





	string file1 = argv[1];
	string file2 = argv[2];
	thread_count = atol(argv[3]);
	file3 = argv[4];



	of.open (file3);
  	of << "";
  	of.close();




	ifstream fs;
	fs.open(file1);
	while(fs.good()) {
		string line;
		//getline(fs, line);
		//cout<<line<<endl;
		if(getline(fs, line)) {
			int value = line.find(",");
			string key = line.substr(0,value); 
			string temp = line.substr(value+1,line.length());
			int count = stoi(temp);
			myMap[key] = count;
			//cout<< "Key: " << key << " = " << "Value: " << count << endl;		
		}
		
	}
	fs.close();
	
	
	fs.open(file2);
	counter = 0;
	mouse = "";
	while(fs.good()) {
		string line;
		if(getline(fs,line)) {
			counter+= line.length();
			mouse.append(upper(line));
			//mouse.append(line);
		}
		
	
	}
	length = counter;
	//cout << myMap["Gfdgsdfg456346346345CTCTGGCCTGAAA"] << endl;
	thread_handles = new pthread_t[thread_count];
	 pthread_mutex_init(&mymutex, NULL);
	 of.open(file3,ios_base::app | ios_base::out);
   long thread;
   for (thread = 0; thread < thread_count; thread++) {
       pthread_create(&thread_handles[thread], NULL, dna, (void*)thread);
   }

//   cout << "Hello from the main thread" << endl;
    

	

   for (thread = 0; thread < thread_count; thread++) {
       pthread_join(thread_handles[thread], NULL);
   }
	//approximation = h * approximation;
   free(thread_handles);
   of.close();
   printf("Done\n");
    return 0;
	
}


void* dna(void* rank) {
	long my_rank = (long)rank;
	long start = (counter*my_rank)/thread_count;
	long fin = ((counter*(my_rank+1))/thread_count)-1;
	long mid = (fin+start)/2;




	
	int counter = 0;
	//ifstream fs;
	//fs.open("hashed_reads_file");
	/**while(fs.good()) {
		string line;
		//getline(fs, line);
		//cout<<line<<endl;

		if(getline(fs, line)) {
			int value = line.find(",");
			string key = line.substr(0,value); 
			string temp = line.substr(value+1,line.length());
			int count = stoi(temp);
			myMap[key] = count;
			/**if(my_rank==1) {
				cout<< "Key: " << counter << endl;		
				counter++;
			}
		}
		
	}
	fs.close();
	**/
	
	long matches = 0;
	matches = ready(start, mid);
	matches += ready(mid+1, fin);






	printf("Thread #%ld has found %ld matches!\n",my_rank,matches);
	/**string temp;
	counter = 0;
	for(int i=start;i<mid-1;i++) {
		string nuc = mouse.substr(i,40);
		
		
		//pthread_mutex_lock(&mymutex);
		if(myMap[nuc]!=0) {
		 	// tamp(string(i) + string(", ") + string(myMap[nuc]) + string("\n")); 
  			string start ("");
  			ostringstream convert;
  			convert << i;
  			string tamp = convert.str();

  			ostringstream convort;
  			convort << myMap[nuc];
  			string tramp = convort.str();

  			temp += start + tamp+ ", " + tramp + "\n";
  			
  			

  			counter++;
  			if(my_rank==1){
  				printf("Start: %ld\n",i);
				printf("Finish: %ld\n",fin);
  			}

  			if(counter==10000) {
  				writeToFile(temp);
  				string temp = "";
  				counter=0;
  			}
			//std::string s(std::string(i) + std::string("example"));
    		//std::cout << s << '\n'; // "C++ by example"
		}
		//pthread_mutex_unlock(&mymutex);
	}

	for(int i=mid;i<fin;i++) {
		string nuc = mouse.substr(i,40);
		
		
		//pthread_mutex_lock(&mymutex);
		if(myMap[nuc]!=0) {
		 	// tamp(string(i) + string(", ") + string(myMap[nuc]) + string("\n")); 
  			string start ("");
  			ostringstream convert;
  			convert << i;
  			string tamp = convert.str();

  			ostringstream convort;
  			convort << myMap[nuc];
  			string tramp = convort.str();

  			temp += start + tamp+ ", " + tramp + "\n";
  			
  			

  			counter++;
  			if(my_rank==1){
  				printf("Start: %ld\n",i);
				printf("Finish: %ld\n",fin);
  			}

  			if(counter==10000) {
  				writeToFile(temp);
  				string temp = "";
  				counter=0;
  			}
			//std::string s(std::string(i) + std::string("example"));
    		//std::cout << s << '\n'; // "C++ by example"
		}
		//pthread_mutex_unlock(&mymutex);
	}**/

	//pthread_mutex_lock(&mymutex);12377579
	//of << temp << endl; 	
	//pthread_mutex_unlock(&mymutex);
	//printf("Start: %ld\n",start);
	//printf("Finish: %ld\n",fin);
	//printf("Finish: %ld\n",counter);
	return NULL;
}

long ready(long start, long fin) {
	string temp;
	long counter = 0;
	
	for(int i=start;i<fin;i++) {
		string nuc = mouse.substr(i,40);
		
		
		//pthread_mutex_lock(&mymutex);
		if(myMap.count(nuc)>0) {
		 	// tamp(string(i) + string(", ") + string(myMap[nuc]) + string("\n")); 
  			string start ("");
  			ostringstream convert;
  			convert << i;
  			string tamp = convert.str();

  			ostringstream convort;
  			convort << myMap[nuc];
  			string tramp = convort.str();

  			temp += start + tamp+ ", " + tramp + "\n";
  			
  			

  			counter++;
  			/**if(my_rank==1){
  				printf("Start: %ld\n",i);
				printf("Finish: %ld\n",fin);
  			}**/

  			/**if(counter==10000) {
  				writeToFile(temp);
  				string temp = "";
  				counter=0;
  			}**/
			//std::string s(std::string(i) + std::string("example"));
    		//std::cout << s << '\n'; // "C++ by example"
		}
		//pthread_mutex_unlock(&mymutex);
	}
	if(counter>0) { 
		writeToFile(temp);
	}
	return counter;
}


void writeToFile(string temp) {
	pthread_mutex_lock(&mymutex);
	of << temp; 	
	pthread_mutex_unlock(&mymutex);
	
}