/**
 * Represents a process in the CPU scheduling simulation.
 * Stores essential process attributes such as burst time, arrival time,
 * priority,
 * remaining execution time, and finish time.
 */
class Process {
    private String processID; // Unique identifier for the process (e.g., P0, P1)
    private int burstTime; // Total execution time required
    private int arrivalTime; // Time at which the process arrives in the system
    private int priority; // Priority of the process (lower value = higher priority)
    private int remainingTime; // Time remaining for process execution (used in preemptive scheduling)
    private int finishTime; // Time at which the process finishes execution

    /**
     * Constructor to initialize a process with necessary attributes.
     * The remaining time is initially set equal to the burst time.
     *
     * @param processID   Unique identifier for the process.
     * @param burstTime   Execution time required by the process.
     * @param arrivalTime Time when the process enters the system.
     * @param priority    Priority level of the process.
     */
    public Process(String processID, int burstTime, int arrivalTime, int priority) {
        this.processID = processID;
        this.burstTime = burstTime;
        this.arrivalTime = arrivalTime;
        this.priority = priority;
        this.remainingTime = burstTime; // Initially, remaining time is equal to burst time
    }

    /**
     * Copy Constructor - Creates a new Process object as a deep copy of another process.
     *
     * @param other The Process object to copy.
     */
    public Process(Process other) {
        this.processID = other.processID;
        this.burstTime = other.burstTime;
        this.arrivalTime = other.arrivalTime;
        this.priority = other.priority;
        this.remainingTime = other.remainingTime;
        this.finishTime = other.finishTime;
    }

    // Getters for process attributes
    public String getProcessID() {
        return processID;
    }

    public int getBurstTime() {
        return burstTime;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getPriority() {
        return priority;
    }

    public int getRemainingTime() {
        return remainingTime;
    }

    public int getFinishTime() {
        return finishTime;
    }

    // Setters for updating process attributes during execution
    public void setRemainingTime(int remainingTime) {
        this.remainingTime = remainingTime;
    }

    public void setFinishTime(int finishTime) {
        this.finishTime = finishTime;
    }

    /**
     * Calculates the turnaround time for the process.
     * Turnaround Time = Finish Time - Arrival Time
     *
     * @return Turnaround time for the process.
     */
    public int calculateTurnaroundTime() {
        return finishTime - arrivalTime;
    }

    /**
     * Calculates the waiting time for the process.
     * Waiting Time = Turnaround Time - Burst Time
     *
     * @return Waiting time for the process.
     */
    public int calculateWaitingTime() {
        return calculateTurnaroundTime() - burstTime;
    }
}
