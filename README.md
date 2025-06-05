# Shortest-Path-Finder

# Finding the Shortest Time Between Airports Using Dijkstra’s Algorithm

# Introduction
The aim of this project is to implement a program that can find the shortest time between different airports using Dijkstra’s algorithm. The program reads the data of airports and flights from a file and stores them in various data structures such as linked list, hash table, and array. The program then allows the user to enter the source and destination airports and displays the shortest time and the optimal route between them.
# Real World Application of the Project
This project has a real-world application in the domain of air travel and transportation. It can help travelers, airlines, and travel agencies to plan their trips efficiently and save time and money. It can also help in finding alternative routes in case of delays, cancellations, or emergencies. Moreover, it can be used to analyze the connectivity and accessibility of different airports and regions.
# Functionality of the Project
The program has the following functionality: <br />
•	It reads the data of airports and flights from a file named “full-flight-data.txt”. The file contains the following information for each airport: airline, flight, origin airport, departure time, arrival time, and arrival airport. This data is then read and saved into a linked list.<br />
•	Another file containing the GMT time zone offsets of the respective airports is opened and its data is stored in a hash table.<br />
•	If the user chooses option 1, the program prompts the user to enter the source. This data is stored in a queue.<br />
•	If the user chooses option 2, Then the program uses Dijkstra’s algorithm to find the shortest time between the two airports. The program considers the departure and arrival times and the time zones.<br />
•	If the user chooses option 3, the program exits.<br />
