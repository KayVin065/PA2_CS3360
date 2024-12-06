#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <queue>
#include <iomanip>
#include <vector>

#define ARR 0
#define DEP 1

using namespace std;

// definition for process structure
struct Process {
    int id;
    double arrivalTime;
    double serviceTime;
};

// definition for event structure
struct Event {
    int type; // ARR or DEP
    double time;
    Process* process; // Pointer to the associated process

    // Comparator for the priority queue
    bool operator<(const Event& other) const {
        return time > other.time; // Min-heap behavior
    }
};

// global variables
int lambdaRate;
double avgServiceTime;
double simClock = 0.0;
double totalTurnaroundTime = 0.0;
double totalBusyTime = 0.0; // for calculating CPU utilization
double totalQueueTime = 0.0; // for calculating ready queue data
double lastQueueTime = 0.0; // for calculating ready queue data
int readyQueueCount = 0;
int processCount = 0;
bool serverIdle = true;

// create a priority queue for the events
priority_queue<Event> eventQueue;

// function prototypes
double genExpDistr(double mean);
void init();
void run();
void schedEvent(int eventType, double eventTime, Process* p);
void arrHandler(Event& e);
void depHandler(Event& e);
void outputMetrics();

int main() {
    srand(time(0));
    avgServiceTime = 0.04; // Set average service time

    int simNumber = 1;

    for (int i = 10; i <= 30; i++) { // Varying lambdaRate
        lambdaRate = i;
        init();
        run();

        // output the data to the screen, includes which number
        // trial the program is currently on
        cout << "Trial Number " << simNumber << ":\n";
        simNumber++;
        outputMetrics();
        cout << endl;
    }

    return 0;
}

// generate exponentially distributed value using uniform distribution
double genExpDistr(double t) {
    double z = ((double)rand()/(double)RAND_MAX);
    double x = (-1 * t) * (log(z));
    return x;
}

// initialize each variable and create the first event
void init() {
    simClock = 0.0;
    totalTurnaroundTime = 0.0;
    totalBusyTime = 0.0;
    totalQueueTime = 0.0;
    lastQueueTime = 0.0;
    readyQueueCount = 0;
    processCount = 0;
    serverIdle = true;

    // schedule first event
    double firstArrivalTime = genExpDistr(1.0 / lambdaRate);
    Process* firstProcess = new Process{0, firstArrivalTime, genExpDistr(avgServiceTime)};
    schedEvent(ARR, firstArrivalTime, firstProcess);
}

// schedule new event, pushes into queue based on priority
void schedEvent(int eventType, double eventTime, Process* p) {
    Event newEvent{eventType, eventTime, p};
    eventQueue.push(newEvent);
}

// handles arrival events
void arrHandler(Event& e) {
    Process* p = e.process;
    processCount++;

    // record time spent in queue since last event
    totalQueueTime += readyQueueCount * (simClock - lastQueueTime);
    lastQueueTime = simClock;

    if (serverIdle) {
        serverIdle = false;
        double departureTime = simClock + p->serviceTime;
        schedEvent(DEP, departureTime, p);
    } else {
        readyQueueCount++;
    }

    // Schedule the next arrival
    double interarrivalTime = genExpDistr(1.0 / lambdaRate);
    double nextArrivalTime = simClock + interarrivalTime;
    Process* nextProcess = new Process{processCount, nextArrivalTime, genExpDistr(avgServiceTime)};
    schedEvent(ARR, nextArrivalTime, nextProcess);
}

// handles departure events
void depHandler(Event& e) {
    Process* p = e.process;
    double turnaroundTime = simClock - p->arrivalTime;
    totalTurnaroundTime += turnaroundTime;
    totalBusyTime += p->serviceTime;

    delete p;

    // record time spent in the queue since last event
    totalQueueTime += readyQueueCount * (simClock - lastQueueTime);
    lastQueueTime = simClock;

    if (readyQueueCount > 0) {
        readyQueueCount--;
        double nextServiceTime = genExpDistr(avgServiceTime);
        double departureTime = simClock + nextServiceTime;
        schedEvent(DEP, departureTime, new Process{processCount + 1, simClock, nextServiceTime});
    } else {
        serverIdle = true;
    }
}

// generates one run of a simulation with 10,000 processes
// properly handles arriving and departing events
void run() {
    while (processCount < 10000 && !eventQueue.empty()) {
        Event e = eventQueue.top();
        eventQueue.pop();
        simClock = e.time;

        switch (e.type) {
            case ARR:
                arrHandler(e);
                break;
            case DEP:
                depHandler(e);
                break;
        }
    }
}

// function to output the final calculated metrics for the run
void outputMetrics() {
    double avgTurnaroundTime = totalTurnaroundTime / processCount;
    double totalThroughput = processCount / simClock;
    double avgCpuUtilization = totalBusyTime / simClock;
    double avgReadyQueueCount = totalQueueTime / simClock;

    cout << fixed << setprecision(2);
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
    cout << "Total Throughput: " << totalThroughput << endl;
    cout << "Average CPU Utilization: " << avgCpuUtilization << endl;
    cout << "Average Number of Processes in Ready Queue: " << avgReadyQueueCount << endl;
}
