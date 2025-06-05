#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std::chrono;
using namespace std;

int LinesInFile_Flightdata = 0;

class nodeHash
{
public:
	string airport;
	int GMT;
	nodeHash* next;
	nodeHash() : airport(""), GMT(0), next(NULL) {};
	nodeHash(string a,int b) // parametarized constructor
	{
		this->airport = a;
		this->GMT = b;
		this->next = NULL;
	}
};
class HashTable
{
private:
	int size;
	int count;
	nodeHash** table;
public:
	HashTable(int m) : size(m), count(0)
	{
		table = new nodeHash * [size];
		for (int i = 0; i < size; i++)
			table[i] = NULL;
	}
	int Search(string key)
	{
		int index = hashFunction(key);
		nodeHash* current = table[index];

		while (current != NULL)
		{
			if (current->airport == key)
				return current->GMT;
			current = current->next;
		}
		return -1;
	}
	void Insert(nodeHash data)
	{
		count++;
		if (count > size)
		{
			tableDoubling();
		}

		int index = hashFunction(data.airport);
		nodeHash* newNode = new nodeHash(data);
		if (table[index] == NULL)
		{
			table[index] = newNode;
		}
		else
		{
			nodeHash* next = table[index]->next;
			table[index]->next = newNode;
			newNode->next = next;
		}
	}
	void Delete(string key)
	{
		int index = hashFunction(key);
		nodeHash* current = table[index],
			* previous = NULL;

		while (current != NULL && current->airport != key)
		{
			previous = current;
			current = current->next;
		}

		if (current == NULL)
		{
			cout << "Data not found!\n\n";
			return;
		}
		else
		{
			if (previous == NULL)
			{
				table[index] = current->next;
			}

			else
			{
				previous->next = current->next;
			}
			delete current;
			current = 0;
		}

		count--;
		if (count < size / 4)
		{
			tableShrinking();
		}
	}
	int hashFunction(string key)
	{
		int i = 0;
		int a;
		int sum = 0;
		while (key[i] != NULL) {
			a = int(key[i]);
			sum = sum + a;
			i++;
		}
		return sum % size;
	}
	void tableDoubling()
	{
		int size_orig = size;
		size *= 2;
		reHashing(size_orig);
	}
	void tableShrinking()
	{
		int size_orig = size;
		size /= 2;
		reHashing(size_orig);
	}
	void reHashing(int size_orig)
	{
		nodeHash** newtable = new nodeHash * [size];
		for (int i = 0; i < size; i++)
		{
			newtable[i] = 0;
		}

		for (int i = 0; i < size_orig; i++)
		{

			nodeHash* curr_orig = table[i],
				* prev_orig = NULL;

			while (curr_orig != NULL)
			{
				prev_orig = curr_orig->next;
				int index = hashFunction(curr_orig->airport);

				if (newtable[index] == NULL)
				{
					newtable[index] = curr_orig;
					newtable[index]->next = 0;
				}
				else
				{
					nodeHash* next = newtable[index]->next;
					newtable[index]->next = curr_orig;
					curr_orig->next = next;
				}
				curr_orig = prev_orig;
			}
		}
		delete[] table;
		this->table = newtable;
	}
	void displayTable()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "Slot " << i << ": ";
			nodeHash* temp = NULL;
			temp = table[i];
			while (temp != NULL)
			{
				cout << "(" << temp->airport << "," << temp->GMT << ") ";
				temp = temp->next;
				
			}
			cout << endl;
		}
		cout << endl;
	}
};
class nodeFlight {
public:
	string flight_name;
	char departureAP;
	char arrivalAP;
	int arrival_time;
	int departure_time;
	string destination_airport;
	string source_airport;
	int duration;
	nodeFlight* next;
	nodeFlight* prev;
	nodeFlight(string val1,string val2,int val3,int val4,char val5,char val6,string val7,int val8) {
		destination_airport = val1;
		source_airport = val2;
		departure_time = val3;
		arrival_time = val4;
		arrivalAP = val5;
		departureAP = val6;
		next = NULL;
		prev = NULL;
		flight_name = val7;
		duration = val8;
	}
};
class doubly {
public:
	nodeFlight* head;
	nodeFlight* tail;
	doubly() {
		head = NULL;
		tail = NULL;
	}
	void insertAtEnd(string val1, string val2, int val3, int val4, char val5, char val6 ,string val7,int val8) {
		nodeFlight* newnodeFlight = new nodeFlight(val1,val2,val3,val4,val5,val6,val7,val8);
		if (tail == nullptr) {
			head = newnodeFlight;
			tail = newnodeFlight;
		}
		else {
			tail->next = newnodeFlight;
			newnodeFlight->prev = tail;
			tail = newnodeFlight;
		}
	}
	void insertAtStart(string val1, string val2, int val3, int val4, char val5, char val6, string val7,int val8) {
		nodeFlight* n = new nodeFlight(val1, val2, val3, val4, val5, val6, val7,val8);
		n->next = head;
		head = n;
	}
	void insertAfter(int pos, string val1, string val2, int val3, int val4, char val5, char val6, string val7,int val8) {
		nodeFlight* n = new nodeFlight(val1, val2, val3, val4, val5, val6 ,val7,val8);
		nodeFlight* curr = head;
		nodeFlight* pre = curr;
		for (int i = 0; i < pos; i++) {
			pre = curr;
			curr = curr->next;
		}
		pre->next = n;
		n->next = curr;
	}
	bool Search(string key) {
		nodeFlight* temp = head;
		while (temp != NULL) {
			if (temp->destination_airport == key) {
				cout << "\nFound the data : " << endl;
				cout << temp->destination_airport << endl;
				cout << "------------------------------\n";
				return true;
			}
			temp = temp->next;
		}
		cout << "\nNot found" << endl;
		return false;
	}
	bool SearchPos(int key) {
		nodeFlight* temp = head;
		for (int i = 0; i < key; i++) {
			temp = temp->next;
		}
		cout << temp->destination_airport;
		return true;
	}
	void Display() {
		nodeFlight* temp = head;
		while (temp != NULL) {
			cout << "\n_____________________________________________________\n";
			cout << "Flight name : " << temp->flight_name << endl;
			cout << "Source Airport : " << temp->source_airport << endl;
			cout << "Destination Airport : " << temp->destination_airport << endl;
			cout << "Departure Time : " << temp->departure_time << endl;
			cout << "Departure AM/PM : " << temp->departureAP << endl;
			cout << "Arrival Time : " << temp->arrival_time << endl;
			cout << "Arrival AM/PM : " << temp->arrivalAP << endl;
			cout << "Duration : " << temp->duration << endl;
			cout << "\n_____________________________________________________\n";
			temp = temp->next;
		}
	}
	void set_data_position(int pos, string val1, string val2, int val3, int val4, char val5, char val6 ,string val7 , int val8) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			i++;
		}
		temp->source_airport = val2;
		temp->destination_airport = val1;
		temp->departure_time = val3;
		temp->arrival_time = val4;
		temp->departureAP = val6;
		temp->arrivalAP = val5;
		temp->flight_name = val7;
		temp->duration = val8;
	}
	void display_position(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			i++;
		}
		cout << "\n_____________________________________________________\n";
		cout << "Flight name : " << temp->flight_name << endl;
		cout << "Source Airport : " << temp->source_airport << endl;
		cout << "Destination Airport : " << temp->destination_airport << endl;
		cout << "Departure Time : " << temp->departure_time << endl;
		cout << "Departure AM/PM : " << temp->departureAP << endl;
		cout << "Arrival Time : " << temp->arrival_time << endl;
		cout << "Arrival AM/PM : " << temp->arrivalAP << endl;
		cout << "Duration : " << temp->duration << endl;
		cout << "\n_____________________________________________________\n";
	}
	string getSource(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->source_airport;
	}
	string getFlightName(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->flight_name;
	}
	string getDestination(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->destination_airport;
	}
	int getdeparture(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->departure_time;
	}
	int getDuration(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL) {
				cout << "Value exceeded\n";
				return -1;
			}
			i++;
		}
		return temp->duration;
	}
	char getdepartureAP(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->departureAP;
	}
	char getarrivalAP(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->arrivalAP;
	}
	int getarrival(int pos) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		return temp->arrival_time;
	}
	void setDuration(int pos,int b) {
		int i = 0;
		nodeFlight* temp = head;
		while (i != pos) {
			temp = temp->next;
			if (temp == NULL)
				cout << "Value exceeded\n";
			i++;
		}
		temp->duration = b;
	}
	void deleteAtFront() {
		nodeFlight* temp = head;
		head = head->next;
		head->prev = NULL;
		delete temp;
	}
	void deleteAtEnd() {
		nodeFlight* temp = head;
		nodeFlight* pre = NULL;
		while (temp->next != NULL)
		{
			pre = temp;
			temp = temp->next;
		}
		tail = pre;
		tail->next = NULL;
		delete temp;
	}
	void deleteAfter(int pos) {
		nodeFlight* curr = head;
		nodeFlight* pre = curr;
		for (int i = 1; i < pos; i++) {
			pre = curr;
			curr = curr->next;
		}
		pre->next = curr->next;
		delete curr;
	}
};
class QnodeFlight {
public:
    string source_code;
    QnodeFlight* next;
    QnodeFlight(string a)
    {
        source_code = a;
        next = NULL;
    }
};
class Queue {
public:
    QnodeFlight* front;
    QnodeFlight* rear;
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
	string Top() {
		return front->source_code;   
	}
    void enQueue(string a)
    {
        QnodeFlight* temp = new QnodeFlight(a);
        if (rear == NULL) {
            front = temp;
            rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }
    void deQueue()
    {
        if (front == NULL)
            return;
        QnodeFlight* temp = front;
        front = front->next;
        if (front == NULL)
            rear = NULL;
        delete temp;
    }
    void display() {
        QnodeFlight* temp = front;
        while (temp!=NULL) {
            cout << temp->source_code;
            temp = temp->next;
        }
    }
};
struct Edge {
	int src, dest, weight;
};
struct GraphBellman {
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges.
	struct Edge* edge;
};
struct GraphBellman* createGraph(int V, int E)
{
	struct GraphBellman* graph = new GraphBellman;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}
bool SearchArray(string arr[],string key,int size) {
	int i = 0;
	while (i != size) {
		if (arr[i] == key) {
			return true;
		}
		i++;
	}
	return false;
}
int getVertex(doubly flights_data,string* Vertices) {
	int sizeOfArray = 0;
	nodeFlight* temp = flights_data.head;
	while (temp != NULL) {
		if (!SearchArray(Vertices,temp->destination_airport, sizeOfArray)) {
			Vertices[sizeOfArray] = temp->destination_airport;
			sizeOfArray = sizeOfArray + 1;
		}
		temp = temp->next;
	}
	return sizeOfArray;
}
int ChangeTo24Format(char AP,int time) {
	//Changes the time from 12 hour format to 24 hour format
	int hour_fomat_temp;
	if (AP == 'P') {
		hour_fomat_temp = time % 100;
		time = time / 100;
		time = time + 12;
		if (time >= 24)
			time = 0;
		time = time * 100;
		time = time + hour_fomat_temp;
	}
	return time;
}
doubly FlightDataStorage() {
	doubly flights_data;
	int departure_time;
	int arrival_time;
	char departure_AP;
	char arrival_AP;
	string flight_name;
	string str1;
	string temp1;
	string source_airport;
	string departure_time_string;
	string destination_airport;
	string arrival_time_string;
	int tempint = 0;
	fstream file;
	file.open("full-flight-data.txt", ios::in);    //3876 lines of data
	while (getline(file, str1)) {                  //calculating the lines of data in the file
		LinesInFile_Flightdata++;
	}
	LinesInFile_Flightdata--;
	file.clear();
	file.seekp(0, ios::beg);                       //resetting pointer to start
	file.seekg(0, ios::beg);
	while (getline(file, str1)) {
		for (int i = 0; i < 7; i++) {
			temp1 = str1[i];
			flight_name.append(temp1);
		}
		for (int i = 8; i < 11; i++) {
			temp1 = str1[i];
			source_airport.append(temp1);
		}
		for (int i = 12; i < 16; i++) {
			temp1 = str1[i];
			departure_time_string.append(temp1);
		}
		departure_AP = str1[16];
		departure_time = stoi(departure_time_string);
		departure_time = ChangeTo24Format(departure_AP,departure_time);                                      
		for (int i = 19; i < 22; i++) {
			temp1 = str1[i];
			destination_airport.append(temp1);
		}
		for (int i = 23; i < 27; i++) {
			temp1 = str1[i];
			arrival_time_string.append(temp1);
		}
		arrival_AP = str1[27];
		arrival_time = stoi(arrival_time_string);
		arrival_time = ChangeTo24Format(arrival_AP, arrival_time);
		flights_data.insertAtEnd(destination_airport, source_airport, departure_time, arrival_time, arrival_AP, departure_AP,flight_name,0);
		destination_airport.clear();
		source_airport.clear();
		departure_time_string.clear();
		arrival_time_string.clear();
		flight_name.clear();
		tempint++;
		if (tempint == LinesInFile_Flightdata)
			break;
	}
	flights_data.set_data_position(7, "DEN", "ABQ", 830, 944, 'A', 'A',"CO1594",0);
	file.close();
	return flights_data;
}
void GMTDataStorage(HashTable GMT_data) {
	string str1;
	string temp1;
	fstream file;
	string source_airport;
	string GMT_string;
	int GMT;
	file.open("full-airport-data.txt", ios::in);
	while (getline(file, str1)) {
		for (int i = 0; i < 3; i++) {
			temp1 = str1[i];
			source_airport.append(temp1);
		}
		for (int i = 5; i < 9; i++) {
			temp1 = str1[i];
			GMT_string.append(temp1);
		}
		GMT = stoi(GMT_string);
		nodeHash temp(source_airport, GMT);
		
		GMT_data.Insert(temp);
		source_airport.clear();
		GMT_string.clear();
	}
	file.close();
}
int getDuration(int a, int b) {
	//Finds the duration of the flight(aka distance)
	int hours;
	int minutes;
	hours = (a / 100) - (b / 100);
	if (hours < 0) {
		hours = hours + 24;
	}
	minutes = (a % 100) - (b % 100);
	if (minutes <= 0) {
		hours--;
		minutes = minutes + 60;
	}
	hours = hours * 100;
	return hours + minutes;
}
int getIndex(string arr[], string key,int size) {
	int i = 0;
	while (i != size) {
		if (arr[i] == key) {
			
			return i;
		}
			
		i++;
	}
	return -1;
}
struct AdjListNode
{
	int dest;
	int weight;
	struct AdjListNode* next;
};
struct AdjList
{
	struct AdjListNode* head;
};
struct GraphDijkstra
{
	int V;
	struct AdjList* array;
};
struct AdjListNode* newAdjListNode(int dest, int weight)
{
	struct AdjListNode* newNode = new AdjListNode();
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}
struct GraphDijkstra* createGraph(int V)
{
	struct GraphDijkstra* graph = (struct GraphDijkstra*)malloc(sizeof(struct GraphDijkstra));
	graph->V = V;
	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
	for (int i = 0; i < V; ++i)
		graph->array[i].head = NULL;
	return graph;
}
void addEdgeBellman(struct GraphBellman* graph,int source, int destination, int w,int i)
{
	graph->edge[i].src = source;
	graph->edge[i].dest = destination;
	graph->edge[i].weight = w;
	i = i + 1;
	graph->edge[i].src = destination;
	graph->edge[i].dest = source;
	graph->edge[i].weight = w;
}
void addEdgeDijkstra(struct GraphDijkstra* graph, int src,int dest, int weight) 
{
	struct AdjListNode* newNode = newAdjListNode(dest, weight); 
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
	newNode = newAdjListNode(src, weight); 
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}
void CalculateDuration(doubly flights_data, HashTable GMT_data, struct GraphDijkstra* graph, string* Vertices, int size) {
	int GMT;
	int duration;
	int temp;
	int temp1;
	int iteration = 0;
	while (iteration != LinesInFile_Flightdata) {
		duration = getDuration(flights_data.getarrival(iteration), (flights_data.getdeparture(iteration)));
		GMT = GMT_data.Search(flights_data.getDestination(iteration)) - GMT_data.Search(flights_data.getSource(iteration));
		duration = duration + GMT;
		if (duration >= 2400) {
			temp = duration;
			temp1 = duration % 10;
			temp = temp / 10;
			temp = temp - 24;
			temp = temp * 100;
			temp = temp + temp1;
			duration = temp;
		}
		flights_data.setDuration(iteration, duration);
		addEdgeDijkstra(graph, getIndex(Vertices, flights_data.getSource(iteration), size), getIndex(Vertices, flights_data.getDestination(iteration), size), duration); //
		iteration++;
	}
}
void BellmanLoopAdd(struct GraphBellman* graph, doubly flights_data, string* Vertices, int size) {
	int src;
	int dest;
	int w;
	int i = 0;
	int pos = 0;
	nodeFlight* temp = flights_data.head;
	while (temp != NULL) {
		src = getIndex(Vertices, temp->source_airport, size);
		dest = getIndex(Vertices, temp->destination_airport, size);
		w = flights_data.getDuration(pos);
		pos++;
		temp = temp->next;
		addEdgeBellman(graph,src,dest,w,i);
		i = i + 2;
	}
}
struct MinHeapNode
{
	int  v;
	int dist;
};
struct MinHeap
{
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode** array;
};
struct MinHeapNode* newMinHeapNode(int v,int dist)
{
	MinHeapNode* minHeapNode = new MinHeapNode();
	minHeapNode->v = v;
	minHeapNode->dist = dist;
	return minHeapNode;
}
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap =(struct MinHeap*)malloc(sizeof(struct MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array =(struct MinHeapNode**)malloc(capacity *sizeof(struct MinHeapNode*));
	return minHeap;
}
void swapMinHeapNode(struct MinHeapNode** a,struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}
void minHeapify(struct MinHeap* minHeap,int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;
	if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
		smallest = left;
	if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
		smallest = right;
	if (smallest != idx)
	{
		MinHeapNode* smallestNode =
			minHeap->array[smallest];
		MinHeapNode* idxNode =
			minHeap->array[idx];
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;
		swapMinHeapNode(&minHeap->array[smallest],&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;
	struct MinHeapNode* root = minHeap->array[0];
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;
	--minHeap->size;
	minHeapify(minHeap, 0);
	return root;
}
void decreaseKey(struct MinHeap* minHeap,int v, int dist)
{
	int i = minHeap->pos[v];
	minHeap->array[i]->dist = dist;
	while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
	{
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i],&minHeap->array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}
void printArr(int dist[], int n,string* Vertices)
{
	cout << "Vertex\t\t\tTime Duration\n";
	for (int i = 0; i < n; ++i)
		cout << Vertices[i] << "\t\t\t"<< dist[i]/100 << ":" << dist[i]%100 << endl;
}
void dijkstra(struct GraphDijkstra* graph, int src,string* Vertices)
{
	int temp;
	int V = graph->V;
	int *dist = new int[V];
	struct MinHeap* minHeap = createMinHeap(V);
	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v,dist[v]);
		minHeap->pos[v] = v;
	}
	minHeap->array[src] = newMinHeapNode(src, dist[src]);
	minHeap->pos[src] = src;
	dist[src] = 0;
	decreaseKey(minHeap, src, dist[src]);
	minHeap->size = V;
	while (!isEmpty(minHeap))
	{
		struct MinHeapNode* minHeapNode = extractMin(minHeap);
		int u = minHeapNode->v;
		struct AdjListNode* pCrawl = graph->array[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->dest;
			if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;
				if (dist[v] % 100 > 60) {
					temp = dist[v] % 100;
					dist[v] = dist[v] / 100;
					dist[v]++;
					temp = temp - 60;
					dist[v] = dist[v] * 100;
					dist[v] = dist[v] + temp;
				}
				decreaseKey(minHeap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}
	printArr(dist, V,Vertices);
}
void BellmanFord(struct GraphBellman* graph, int src,string* Vertices)
{
	int V = graph->V;
	int E = graph->E;
	int* dist = new int[V];
	for (int i = 0; i < V; i++)
	dist[i] = INT_MAX;
	dist[src] = 0;
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
			cout << "GraphBellman contains negative weight cycle" << endl;
			return;
		}
	}
	printArr(dist, V, Vertices);
	return;
}
int main() {
	int E = 8;
	fstream file;
	doubly flights_data;
	HashTable GMT_data(50);
	flights_data = FlightDataStorage();
	GMTDataStorage(GMT_data);
	string* Vertices = new string[LinesInFile_Flightdata];
	int Vertex = getVertex(flights_data, Vertices);
	struct GraphBellman* graphB = createGraph(Vertex, E);
	struct GraphDijkstra* graphD = createGraph(Vertex);
	CalculateDuration(flights_data, GMT_data, graphD,Vertices,Vertex);
	//BellmanLoopAdd(graphB,flights_data,Vertices,Vertex);
	//BellmanFord(graphB, 0, Vertices);
    Queue Input;
    int choice;
    string source_code;
    int start_time;
    char APM;
    while (1) {
        cout << "1. Input Route Details : \n";
        cout << "2. Compute Shortest Time to all Airports : \n";
        cout << "3. Exit : \n";
		cout << "Enter Choice : ";
        cin >> choice;
		if (choice == 1) {
			cout << "Source Airport Code : ";
			cin >> source_code;
			Input.enQueue(source_code);
		}
		else if (choice == 2) {
			source_code = Input.Top();
			auto start = high_resolution_clock::now();
			dijkstra(graphD, getIndex(Vertices, source_code, Vertex), Vertices);
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast <milliseconds>(stop - start);
			cout << "Time Taken by Function : " << duration.count() << " milliseconds" << endl;
			Input.deQueue();
		}
		else if (choice == 3) {
			return 0;
		}
    }
}