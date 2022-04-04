#include <iostream>

using namespace std;

int counter = 0;
int times[100];

class Customer{
private:
    int arrival_time;
    int wait_time;
    bool done;
    bool here;
    bool in_queue;

public:
    string name;

    Customer(){
        name = "";
        arrival_time=10000;
        wait_time = 1;
        done = false;
        here = false;
        in_queue = false;
    }

    Customer(string namer, int arrival_timer){
        name = namer;
        arrival_time = arrival_timer;
        wait_time = 0;
        done = false;
        here = false;
        in_queue = false;
    }

    void update(){
        if (arrival_time > 0){
            arrival_time = arrival_time - 1;
            here = false;
        }else{
            here = true;
        }
    }

    void tellerUpdate(){
        if (arrival_time == 0){
            here = true;
            wait_time = wait_time+1;
        }
    }

    void finish(){
        done = true;
    }

    bool isDone(){
        return done;
    }

    bool isHere(){
        return here;
    }

    int get_wait_time(){
        return wait_time;
    }

    int get_arrival_time(){
        return arrival_time;
    }

    void queued(){
        in_queue = true;
    }

    bool isQueued(){
        return in_queue;
    }

    };

class Stack{
private:
    int size;
    int top;
    int count;
    Customer *list[100];

public:
    Stack(){
        size = 100;
        top = -1;
        count = 0;
    }

    bool isEmpty() const{
        return top == -1;
    }

    bool isFull() const{
        return size == (top-1);
    }

    Customer* peek(){
        if (isEmpty()){
            cout << "Stack is empty" << endl;
            Customer* c;
            return c;
        }
        return list[top];
    }

    Customer* pop(){
        if (isEmpty()){
            cout << "Stack is empty" << endl;
            Customer* c;
            return c;
        }
        count = count - 1;
        return list[top--];
    }

    void push(Customer* el){
        if (isFull()){
            cout << "Stack is full" << endl;
            return;
        }
        count = count+1;
        list[++top] = el;
    }

    int getSize(){
        return count;
    }


};


class Queue{
private:
    int size;
    int front;
    int rear;
    int count;
    Customer *list[100];
public:
    Queue(){
        size = 100;
        front = 0;
        rear = size-1;
        count = 0;
    }

//    Queue(int size_in){
//        size = size_in;
//        front = 0;
//        rear = size_in-1;
//        count = 0;
//        list = new Customer[size_in];
//    }

    bool isEmpty() const{
        return count == 0;
    }

    bool isFull() const{
        return count == (size-1);
    }

    Customer* dequeue(){
        if (isEmpty()){
            cout << "Queue is empty" << endl;
            Customer* c;
            return c;

        }
        count--;
        Customer* el = list[front];
        front = (front+1)%size;
//        cout << count << endl;
        return el;
    }

    void enqueue(Customer* el){
        if (isFull()){
            cout << "Queue is full" << endl;
            return;
        }
        count++;
        rear = (rear + 1) % size;
        list[rear] = el;
    }

    int getSize(){
        return count;
    }

    void read(){
        for(int i = 0; i < getSize(); i++){
            cout << list[i]->name << "-------" << endl;
        }
    }


};


class Teller{

private:
    int time;
    Customer *c;
    int rate;
    int number;
    Queue line;
    bool working;

public:

    Teller(){

        time = 0;
        rate = 100000;
        number = -1;
        working = false;

    }

    Teller(int number_in, int rater){
        number = number_in;
        rate = rater;
        time = 0;
    }

    void takeCustomer(Customer* cust_in){
//        cout << "here" << endl;
        cust_in->queued();
        line.enqueue(cust_in);
        working = true;
    }

    void finishCustomer(){
        Customer* c = line.dequeue();
        c->finish();
        cout << c->name << " has been served from teller " << number << ", waited for " << c->get_wait_time() <<"sec" << endl;
        times[counter] = c->get_wait_time();
        counter = counter + 1;
        cout << "Teller " << number << " : " << line.getSize() << " left." << endl;
        if (line.getSize() == 0){
            working = false;
        }
//        cout << c->name << ": " << c->isDone() << endl;
//        c = Customer();
    }

    void update(){
        cout << "Teller " << number << ": [";
        for (int i = 0; i < line.getSize();i++){
            cout << "|";
        }
        for (int i = 0; i < (15- line.getSize());i++){
            cout << "-";
        }
        cout << "]" << endl;
        time = time + 1;
//        line.read();
        if ((time%rate) == 0 && line.getSize()>0){
            finishCustomer();
//                    cout << c->name << "before: " << c->isDone() << endl;

        }
//        cout << time << ":" << rate << endl;
    }

    int getLine(){
        return line.getSize();
    }

    bool isWorking(){
        return working;
    }


};

int main(){

    int teller_no, customer_no;
    cout << "Enter number of generated customers: " << endl;
    cin >> customer_no;
    cout << "Enter number of tellers: " << endl;
    cin >> teller_no;
    Teller *tellers[teller_no];

    for (int i = 0; i < teller_no; i++){
        int rater;
        cout << "Enter rate for teller " << i << endl;
        cin >> rater;
        tellers[i] = new Teller(i,rater);
    }

    // Randomly generated stack input
    string names[10] = {"John", "Mohamed", "Ahmed", "Jerry", "Yousef", "Kaleb", "Omar", "Abdelrahman"};
    Stack customers_stack;

    for (int i = 0; i < customer_no; i++){
        Customer* c = new Customer(names[rand()%9+1] + " " + names[rand()%9+1], rand()%300+1);
        customers_stack.push(c);
    }

//    cout << customers_stack.getSize() << endl;

//    Customer *customers[10];
//
//    customers[0] = new Customer("John", 7);
//    customers[1] = new Customer("Mohamed", 3);
//    customers[2] = new Customer("Ahmed", 2);
//    customers[3] = new Customer("Jerry", 6);
//    customers[4] = new Customer("Ahmed", 20);
//    customers[5] = new Customer("Yousef", 5);
//    customers[6] = new Customer("Kaleb", 9);
//    customers[7] = new Customer("Omar", 17);
//    customers[8] = new Customer("Sokar", 13);
//    customers[9] = new Customer("Abdelrahman", 4);

//    cout << "here" << endl;
    Customer *customers[customer_no];
    cout << "---------------------------------"<< endl;
    cout << "Customer Name : Arrival Time(in seconds)"<<endl;
    for (int i = 0; i < customer_no; i++){
        customers[i] = customers_stack.pop();
        cout << customers[i]->name << " : " << customers[i]->get_arrival_time()<< "sec" << endl;
    }
    cout << "---------------------------------"<< endl;

    bool all_done = false;
    int t = 0;
    while (true){
        cout << "==================== Time " << t << " ===================="<<endl;
        for (int i = 0; i < customer_no; i++){
//            cout << i << endl;
//            cout << customers[i]->name << " " << customers[i]->isQueued() << customers[i]->isHere() << endl;
            if(!customers[i]->isQueued() && customers[i]->isHere()){
                int shortest = 0;
                int shortest_len = 1000;
                for (int j = 0; j < teller_no; j++){
                    if (tellers[j]->getLine()<shortest_len){
                        shortest = j;
                        shortest_len = tellers[j]->getLine();
                    }
                }
//                cout << "here : " << shortest << endl;
                cout << "Teller " << shortest << " received " << customers[i]->name << endl;
                tellers[shortest]->takeCustomer(customers[i]);
            }
        }
        bool all_done = true;
        for (int i = 0; i< teller_no; i++){
            if (tellers[i]->isWorking()){
                tellers[i]->update();
            }
        }
        for (int i = 0; i < customer_no; i++){
//            cout << i << endl;
            customers[i]->update();
            if (customers[i]->isQueued()){
                customers[i]->tellerUpdate();
            }
            if (!customers[i]->isDone()){
                all_done = false;
//                cout << customers[i]->name << " : " << customers[i]->isDone() << customers[i]->isQueued() << endl;
            }
        }
        t = t + 1;
        if (all_done){
            cout << "Finished" << endl;
            break;
        }
//        if (t.isEmpty() && customer->isHere() && !customer->isDone()) {
//            t.takeCustomer(customer);
//        }
//        t.update();
////        cout << customer->name << "after: " << customer->isDone() << endl;
//        customer->update();
    }
    int sum = 0;
    int maxer = 0;
    for (int i = 0; i < counter; i++){
        sum = sum + times[i];
        if (times[i] > maxer){
            maxer = times[i];
        }
    }
    cout << "Average waiting time: " << sum/customer_no << "sec" << endl;
    cout << "Maximum waiting time: " << maxer << "sec" << endl;

//    cout << customer->get_wait_time()<<endl;

}
