   # Truck-Delivery-Company-Simulation

## Intro:

This is a Truck-Delivery-Company software program in C++. It simulates the process of delivering cargos 
by trucks starting from the cargos arriving at the company until they are delivered safe to their destination.

This project was developed as part of a Data Structures and Algorithms course, associated with *Faculty of Engineering, Cairo University*.

Tha aim of the project is put to knowledge gained through the course in data structures to test, in addition to devising the most efficeint algorithms to use them in satisfying the requirements.
The data structures of use here are: linked lists, stacks, queues, and trees.

The project is also, in large part, an application of OOP (Object-oriented programming).

## Classes and Description:
### Data Structures:
    Node : A basic node containing an item of data and a pointer to another node.
    LinkedList : Singly linked list with the common operations. it is a series of Nodes linked together.
    Queue: The famous queue data structure, implemented using a linked list.
    PriorityQueue: Priority queue data structure in linkedlist implementation.
### Application classes:
*    Company: The master class inside which all company operations are handled, like:
        - Receiving events and arranging them to be handled.
        - handling events.
        - selecting trucks to deliver based on their availability, speed, range, number of deliveries made in the day, maintenance time, etc..
        - assigning cargos to trucks based on the different scenarios mentioned in the project document.
        - stamping cargo information and delivery times.
        - choosing highest priority cargos to be delivered first.
        - keeping track of current status of the many lists involved i.e trucks, cargos.
        - keeping track of the status of cargos: waiting, loading, moving, unloading, delivered.
        - keeping track of the status of trucks: empty, loading, moving, unloading, finished, in maintenance, in checkup.
        - keeping tracks of all the data and statistics necessary to calculate the required info about utilzation.
        - and more....
*    UI: user interface; responsible for any interfacing with the user
*    Event: from which 3 subclasses inherit: PreparationEvent, CancelEvent, PromotionEvent
*    Truck: keeps all info related to a truck: ID, speed, type, etc..
*    Cargo: keeps all cargo info: its waiting time, id, type, expected delivery time
*    Time: An auxiliary class to keep track time. It wasn't necessary for the project, but we figured that creating it
    would make the code more modular.

## Illustration:
This is a brief illustration of a random testcase.
![image](https://github.com/alhusseingamal/Truck-Delivery-Company-Simulation/assets/109280831/64feb7c2-ffa5-4ef5-a6e9-f38b82b6a67b)
1.	The user is prompted to enter the file name, and choose a mode.
![image](https://github.com/alhusseingamal/Truck-Delivery-Company-Simulation/assets/109280831/3675b5be-c51f-46b3-9049-4b6879b4405b)
2.	Cargos are assigned to trucks, loaded, moving, then delivered. Trucks are either empty, loading cargos, moving, or in maintenance.
![image](https://github.com/alhusseingamal/Truck-Delivery-Company-Simulation/assets/109280831/3788ef91-8e91-407a-a6b7-beffba671be5)
3.	Sample output file produced.
***For a full illustration of the program, look into the sample_run file.***

## Notes:

1. Throughout the project, dequeue and queue operations are used to deal with different types of objects
i.e. trucks, cargos, etc... This is for sure not the optimal way to achieve the desired result, 
but it was a project requirement to use queues as they are in their basic structure and not to loop over them.

2. Most of the time the code is simple enough and self-explanatory(owing in part to variable naming), so I omitted
explanations of many parts, to avoid stuffing the code with long unnecessary paragraphs.


For more info, refer to the project description document.

## Contributors:
This project was created by:
*    Alhussein Gamal Hussein 
*    Mohamed Ahmed Ibrahim
