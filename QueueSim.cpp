#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Customer.h"

using namespace std;
vector<Customer*> vectorsOfCustomers;
vector<Customer*> vectorsOfPrimaryServerQueue;
vector<Customer*> vectorsOfSecondaryServerQueue;
vector<Customer*> PrimaryServers;
vector<Customer*> SecondaryServers;
int numOfPrimaryServers;

int numOfSecondaryServers;
Customer* customer;
Customer* currentCustomer;


int main(){
    int totalServiceTime=0;
    int instPriQueue=0;
    int lengthPriQueue=0;
    int maxlengthPriQueue=0;
    int totalPriQueueTime=0;
    int instSecQueue=0;
    int totalSecQueueTime=0;
    int lengthSecQueue=0;
    int maxlengthSecQueue=0;

    int charToInt1;
    int charToInt2;
    int charToInt3;
    int firstNum;
    int secondNum;
    int thirdNum;

    int generateNameCustomer = 1; //The names of my customer are 1,2,3...
    
    //Part A: get all the customers data and store it into our vector
    fstream newfile;
    newfile.open("A2data6.txt",ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            int sizeOfLine = tp.size();
           
            //cout << tp << ", size of line: "<< sizeOfLine<< "\n"; //print the data of the string

            //getting the number of primary and secondary servers from the file and using to create arrays of primary and secondary servers
            if(sizeOfLine==4){
                //cout << tp << ", size of line: "<< sizeOfLine<< "\n";
                //get the number of primary servers(from line where there's only 2 numbers) which isthe first char at position 0 index
                char firstChar = tp[0];
                cout << "numOfPrimaryServers: " << firstChar << endl;
                int charToInt = firstChar - '0'; //convert the char to an int , the char was the data type i got while extracting the first nummber at position 0 index
                numOfPrimaryServers = charToInt; //assign the converted char to int to the primary server variable
                cout << "numOfPrimaryServers: " << to_string(numOfPrimaryServers) << endl;


                //get the number of secondary servers(from line where there's only 2 numbers) which is the first char at position 2 index
                char secondChar = tp[2];
                cout << "numOfSecondaryServers: " << secondChar << endl;
                charToInt = secondChar - '0'; //convert the char to an int , the char was the data type i got while extracting the first nummber at position 0 index
                numOfSecondaryServers = charToInt; //assign the converted char to int to the secondary server variable
                cout << "numOfSecondaryServers: " << to_string(numOfSecondaryServers) << endl;
            }

            else if (sizeOfLine>4){
                string space_delimiter = "	";
                vector<string> vectorLine{};

                size_t pos = 0;
                //cout << "Customer:" <<   generateNameCustomer;
                while ((pos = tp.find(space_delimiter)) != string::npos) {
                //    cout << " pos:" << pos ;
                    vectorLine.push_back(tp.substr(0, pos));
                    tp.erase(0, pos + space_delimiter.length());
                }
                vectorLine.push_back(tp);
                //cout <<" tp:" << tp << endl;
                //cout << "vectorLine{}size" << vectorLine.size() << " firstNum:" << vectorLine.at(0) << " secondNum:"<< vectorLine.at(1)<< " thirdNum:"<< vectorLine.at(2) << endl;
                
                firstNum = stoi(vectorLine.at(0));
                secondNum = stoi(vectorLine.at(1));
                thirdNum = stoi(vectorLine.at(2));

                if (firstNum!=0 && secondNum!=0 && thirdNum!=0){ //if it's not the end '0 0 0' customer
                    customer = new Customer(generateNameCustomer, firstNum, secondNum , thirdNum);
                    vectorsOfCustomers.push_back(customer);
                }

                //customer = new Customer(generateNameCustomer, firstNum, secondNum , thirdNum);
                //cout << "Customer:" <<   generateNameCustomer << " arrivalTime:"<< vectorLine.at(0)<< " primaryServerTime:"<<  vectorLine.at(1) << "  secondaryServerTime:"<< vectorLine.at(2) <<endl; 
                //vectorsOfCustomers.push_back(customer);
                vectorLine.clear();
                generateNameCustomer ++;
            }
        }
        newfile.close(); //close the file object.
    }

    //cout << "Starting PrimaryServers.size():"<< PrimaryServers.size()<< endl;
    cout << "-----------In vectorsOfCustomers----------" << endl;
    for(int i = 0; i < vectorsOfCustomers.size(); i++){
		cout << "Customer [" << vectorsOfCustomers[i]->getName() << "]" << " arrivalTime:"<< vectorsOfCustomers[i]->getarrivalTime() << " primaryServerTime:"<<  vectorsOfCustomers[i]->getprimaryServerTime() << "  secondaryServerTime:"<< vectorsOfCustomers[i]->getsecondaryServerTime() <<endl; 
	}

    //cout << "Ending PrimaryServers.size():"<< PrimaryServers.size()<< endl;
    cout << "--------------" << endl;

    //Part B: iterating through every minute
    //iterating though every minute
    bool notFinished = true;
    int currentTime = 1;

    while(notFinished==true){

        //if both primary/secondary queue/servers are empty get out of the while loop
        if((PrimaryServers.empty()==true) && (SecondaryServers.empty()==true) && (vectorsOfCustomers.empty()==true) &&(vectorsOfPrimaryServerQueue.empty()==true) && ( vectorsOfSecondaryServerQueue.empty()==true)){
            cout << "if both primary/secondary servers/queue and vector of customers are empty" << endl;
            notFinished=false;
            break;

        }

        cout << "--------------------" << endl;
        cout << "Current Time: " << currentTime <<endl;

        //Part C: Decrement the time values in both servers every minute
        // Decrement all the curstomer's in primary server times in the primary server array
        //process the primary array, means we decrement all the curstomer's primary server times in the primary server array
        cout <<"---Part C: process the arrays every minute---"<< endl;
        if(PrimaryServers.empty()==false){
            for (int i = 0; i < PrimaryServers.size(); i++) {
                PrimaryServers[i]->decrementPrimaryServerTime();
            }
            cout <<"---after decrementing from primary server, identify the server time with 0 and remove from primary server--" << endl;
            //after that if any in the PrimaryServers hit 0, and assign it to secondary server/queue next
            for (int i = 0; i < PrimaryServers.size(); i++) {
                if (PrimaryServers[i]->getprimaryServerTime() <=0){
                    customer = PrimaryServers.at(i);
                    //put customer to secondary server queue next
                    vectorsOfSecondaryServerQueue.push_back(customer);
                    customer->setarrivalSecondaryQTime(currentTime);//set the time of arrival to secondary queue

                    //if any of my secondary servers is not occupied put in secondary server
                    if(SecondaryServers.size()<numOfSecondaryServers){ 
                        cout <<"Case2a: if secondary servers are not all busy, push to secondary server "<< endl;
                        SecondaryServers.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                    }
                        
                    //put the customer in Secondary Server queue
                    else{
                        cout <<"Case2b: if secondary servers are all busy, push to secondary queue "<< endl;
                        //put the customer in Secondary Server queue
                        currentCustomer->setarrivalSecondaryQTime(currentTime);//set time when customer arrived at secondary queue;
                        vectorsOfSecondaryServerQueue.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                    }
                    //remove customer from primary server array
                    PrimaryServers.erase(PrimaryServers.cbegin()+i);

                    cout << "Primary server["<< i<<"]: "<< customer->toString() << endl;
                }
            }
        }
        // Decrement all the curstomer's secondary server times in the secondary server array
        cout <<"---after decrement secondary server, identify the server time with 0 and remove from server---" << endl;
        if(SecondaryServers.empty()==false){
            for (int i = 0; i < SecondaryServers.size(); i++) {
                SecondaryServers[i]->decrementSecondaryServerTime();
            }
            //after that if any in the Secondary Servers hit 0, remove from seondary server
            for (int i = 0; i < SecondaryServers.size(); i++) {
                if (SecondaryServers[i]->getsecondaryServerTime() <=0){
                    SecondaryServers.erase(SecondaryServers.cbegin()+i);
                    totalServiceTime = totalServiceTime + (currentTime - SecondaryServers[i]->getarrivalTime()); //total service time of that customer from arrival to finishing secondary queue
                }
                cout << "Secondary server["<<i<<"]: "<< SecondaryServers[i]->toString() << endl;
            }
        }

        
        //Part D: Assign a Customer from queue to the array to any available server after processing both array servers
        //Assign customers from primary queue to primary array if there are any waiting customer in primary queue
        while(PrimaryServers.size() < numOfPrimaryServers && vectorsOfPrimaryServerQueue.empty()==false){//if any of my primary servers is not occupied and queue not empty
            customer = vectorsOfPrimaryServerQueue.at(0);
            totalPriQueueTime = totalPriQueueTime + (currentTime - customer->getarrivalTime());//add the queue time in primary q from arrivaltime to current time
            instPriQueue++;
            PrimaryServers.push_back(customer); // assign the first vectorsOfCustomers
            vectorsOfPrimaryServerQueue.erase(vectorsOfPrimaryServerQueue.begin()); //remove the first Customer in primary queue
        }
        cout << "totalPriQueueTime: "<< totalPriQueueTime << endl;

        //cout <<"---after assigning from primary queue to primary server--" << endl;
        for (int i = 0; i < vectorsOfPrimaryServerQueue.size(); i++) {
            cout <<"PriQ["<<i<<"]->getName():" << vectorsOfPrimaryServerQueue[i]->getName();
            cout <<" getarrivalTime():" << vectorsOfPrimaryServerQueue[i]->getarrivalTime();
            cout <<" getprimaryServerTime()" << vectorsOfPrimaryServerQueue[i]->getprimaryServerTime();
            cout <<" getsecondaryServerTime()"<< vectorsOfPrimaryServerQueue[i]->getsecondaryServerTime() << endl;

            //check all queuing in Primary server, add all the queing time and add queue size for average/max queue later
            if(maxlengthPriQueue < vectorsOfPrimaryServerQueue.size()){
                maxlengthPriQueue = vectorsOfPrimaryServerQueue.size();
            }
         
        }
        lengthPriQueue = lengthPriQueue + vectorsOfPrimaryServerQueue.size();

        //Assign customers from Secondary queue to secondary array if there are any waiting customer in secondary queue
        while(SecondaryServers.size()<numOfSecondaryServers && vectorsOfSecondaryServerQueue.empty()==false){//if any of my primary servers is not occupied and queue not empty
            customer = vectorsOfSecondaryServerQueue.at(0);
            totalSecQueueTime = totalSecQueueTime + (currentTime - customer->getarrivalSecondaryQTime());//add the queue time in primary q from arrivaltime to current time
            instSecQueue++;
            SecondaryServers.push_back(customer);// assign the first vectorsOfCustomers
            vectorsOfSecondaryServerQueue.erase(vectorsOfSecondaryServerQueue.begin()); //remove the first Customer in secondaary queue
        }
        cout << "totalSecQueueTime: "<< totalSecQueueTime << endl;

        //cout <<"---after assigning from secondary queue to secondary server--" << endl;
        for (int i = 0; i < vectorsOfSecondaryServerQueue.size(); i++) {
            cout <<"SecQ["<<i<<"]->getName():" << vectorsOfSecondaryServerQueue[i]->getName();
            cout <<" getarrivalTime():" << vectorsOfSecondaryServerQueue[i]->getarrivalTime();
            cout <<" getprimaryServerTime()" << vectorsOfSecondaryServerQueue[i]->getprimaryServerTime();
            cout <<" getsecondaryServerTime()"<< vectorsOfSecondaryServerQueue[i]->getsecondaryServerTime() << endl;
        
            //check all queuing in Primary server, add all the queing time and add queue size for average/max queue later
           
            if(maxlengthSecQueue < vectorsOfSecondaryServerQueue.size()){
                maxlengthSecQueue = vectorsOfSecondaryServerQueue.size();
            }
        } 
        lengthSecQueue = lengthSecQueue + vectorsOfSecondaryServerQueue.size();



        //Part E: For every new customer coming every min, delegate it to where it should go whether primary/secondary array/quueu, after processing all arrays
        //check for that customer whether it goes to primary/secondary array/queue
        cout << "------Part E:-----------" << endl;
        if(vectorsOfCustomers.empty()==false){ //while vectors of customers is not empty
        
        currentCustomer = vectorsOfCustomers.at(0);
        cout << currentCustomer->toString() << endl;

            // keep looping if the current customer's arrival time is equals to current time
            while(currentCustomer->getarrivalTime()==currentTime){ 
                cout << "------if current time is equals to customer time ------" << endl;
                    
                //if customer's primary server time is more than zero, means still have some processing to do.
                if(currentCustomer->getprimaryServerTime()>0){ 
                    cout <<"Case1: if customer's primary server time is not 0"<< endl;
                    
                    if( PrimaryServers.size()<numOfPrimaryServers){//if any of my primary servers is not occupied put in primary server
                        cout <<"Case1a: if primary servers are not all busy, push to primary server "<< endl;
                        PrimaryServers.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                        cout << "vectorsOfCustomers.size()" << vectorsOfCustomers.size() << endl;
                    }
                    
                    //put the customer in Primary Server queue
                    else{
                        cout <<"Case1b: if primary servers are all busy, push to primary queue "<< endl;
                        vectorsOfPrimaryServerQueue.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                    }
                }
                    
                ///if customer's secondary server time is not <0, but primary is alr 0 and below
                if(currentCustomer->getsecondaryServerTime()>0 && currentCustomer->getprimaryServerTime()<=0){ 
                    cout << "Case2: if customer's secondary server time is not 0, but primary is alr 0"<< endl;  

                    //if any of my secondary servers is not occupied put in secondary server
                    if(SecondaryServers.size()<numOfSecondaryServers){ 
                        cout <<"Case2a: if secondary servers are not all busy, push to secondary server "<< endl;
                        SecondaryServers.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                    }
                        
                    //put the customer in Secondary Server queue
                    else{
                        cout <<"Case2b: if secondary servers are all busy, push to secondary queue "<< endl;
                        //put the customer in Secondary Server queue
                        currentCustomer->setarrivalSecondaryQTime(currentTime);//set time when customer arrived at secondary queue;
                        vectorsOfSecondaryServerQueue.push_back(currentCustomer);
                        vectorsOfCustomers.erase(vectorsOfCustomers.begin());
                    }
                }
                
                //if when getting the next customer it's arrival time is same, still continue to loop
                if(vectorsOfCustomers.empty()!=true){ //while vectors of customers is not empty
                    currentCustomer = vectorsOfCustomers.at(0);
                }
                //else if the vectorsOfCustomers is already empty, break the loop
                else if(vectorsOfCustomers.empty()==true){
                    break;
                }
            }
        }
    currentTime++;
    }
    cout <<"------Part F:-----------" << endl;
    cout <<"------Display all calculations------"<< endl;
    cout << "Number of People served: " << (generateNameCustomer-2) << endl; //minus the first line and last line
    cout << "Time last service is completed: " << currentTime << endl;
    //cout << "totalServiceTime: " << totalServiceTime << endl;
    //cout << "instSecQueue" << instSecQueue << endl;
    //cout << "instPriQueue" << instPriQueue << endl;
    //cout << "totalPriQueueTime: " << totalPriQueueTime << endl;
    //cout << "totalSecQueueTime: " << totalSecQueueTime << endl;
    //cout << "lengthPriQueue: " << lengthPriQueue << endl;
    //cout << "lengthSecQueue: " << lengthSecQueue << endl;


    int avglengthPriQueue = (lengthPriQueue/currentTime); //average the length of primary queue at every minute
    cout << "Average length of Primary Queue: " << avglengthPriQueue << endl;
    int avglengthSecQueue = (lengthSecQueue/currentTime); //average the length of secondary queue at every minute
    cout << "Average length of Secondary Queue: " << avglengthSecQueue << endl;

    int avgBothLengthQueue = ((lengthPriQueue+lengthSecQueue)/(currentTime)); //average the total length of both queues at every minute
    cout << "Average length of Both Queues: " << avgBothLengthQueue << endl;

    int avgTotalInPriQueue = (totalPriQueueTime / instPriQueue);
    cout << "Average total time in Primary Queue: " << avgTotalInPriQueue << endl;

    int avgTotalInSecQueue = (totalSecQueueTime / instSecQueue);
    cout << "Average total time in Secondary Queue: " << avgTotalInSecQueue << endl;

    int avgTotalBothQueue = (totalPriQueueTime+totalSecQueueTime)/(instPriQueue+instSecQueue);
    cout << "Average total time in Both Queues: " << avgTotalBothQueue << endl;

    int avgTotalServiceTime = totalServiceTime/(generateNameCustomer-2);
    cout << "Average Total Service Time: " << avgTotalServiceTime << endl;
    cout << "Maximum length of Primary Queue:" << maxlengthPriQueue << endl;
    cout << "Maximum length of Secondary Queue: " << maxlengthSecQueue << endl;

    if(maxlengthPriQueue > maxlengthSecQueue){
        cout << "Maximum length for overall queue " << maxlengthPriQueue << endl;
    }
    else if(maxlengthPriQueue < maxlengthSecQueue){
        cout << "Maximum length for overall queue " << maxlengthSecQueue << endl;
    }
}

