#include <future>
#include <iostream>

/*
we have to do 3 tasks A, B, C:
option 1: one after the other. Always complete one thing before starting the next task

          Single Thread Technique


option 2: I will complete all tasks in such a way that I "practically start all of them a the same time"
          but keep juggling them based on some criteria

          Multi-threaded approach


option 3: map number of tasks amongst available number of "workers"

          Parallel Execution


option 4: start a task, either delegate it to another worker OR do it yourself after some time

          If someone else is doing a task, monitor it, wait for their work to be done, take follow-up actions accordingly.

          Asynchronous Execution
*/

/*
    2 tasks: 
    calculate factorial of 5
    calculate square of number given by user
*/

int square(std::future<int>&ft){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Hello from square. I have started my work!\n"<<std::endl;
    int number = ft.get();
    return number*number;
}

int factorial(int number){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    if(number<0){
        throw std::runtime_error("negative number error");
    }
    else if(number==0 || number==1){
        return 1;
    }
    else{
        return number* factorial(number-1);
    }
}
int main(){
    //step 1: make a promise to OS. I will provide a input when I get from
    std::promise<int> pr;

    //step 2: A future linked with the promise
    std::future<int> ft=pr.get_future();

    /*
        OS: launch square(if possible as a new thread)
    */
    std::future<int> result_ft= std::async(std::launch::async, &square, std::ref(ft));

    std::cout<<factorial(5)<<std::endl;

    int val;

    std::cin>>val;
    pr.set_value(val);

    std::cout<<"Result of square is: "<<result_ft.get()<<std::endl;
    
}
/*
    client-server architecture:

    future-promise model

    square calculation:
    Main needs to delegate the task of square calculation

    -----> A new thread for square will be registered with OS


*/