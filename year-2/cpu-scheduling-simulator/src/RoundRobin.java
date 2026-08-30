import java.util.*;

class RoundRobin extends SchedulingAlgorithm {
    private  int timeQuantum; // Time quantum for Round Robin scheduling

    /**
     * Constructor for the Round Robin scheduling algorithm.
     *
     * @param processList List of processes to be scheduled.
     * @param timeQuantum Time slice assigned to each process.
     */
    public RoundRobin(ArrayList<Process> processList, int timeQuantum) {
        super(processList);
        this.timeQuantum = timeQuantum;
    }

    /**
     * Executes the Round Robin scheduling simulation.
     */
    @Override
    public void executeSimulation() {
        Queue<Process> readyQueue = new ArrayDeque<>();

        // Sort processes by Arrival Time (ensuring correct processing order)
        processList.sort(Comparator.comparingInt(Process::getArrivalTime));

        int currentTime = 0; // Tracks the current simulation time
        int completedProcesses = 0; // Counter for completed processes
        int processCount = processList.size(); // Total number of processes
        List<String> executionOrder = new ArrayList<>(); // Stores the execution sequence for Gantt chart
        List<Integer> timeStamps = new ArrayList<>(); // Stores the timestamps for the Gantt chart

        int index = 0;
        // Add all processes that arrive at time 0 to the ready queue
        while (index < processCount && processList.get(index).getArrivalTime() == 0) {
            readyQueue.add(processList.get(index));
            index++;
        }

        // Continue scheduling until all processes are completed
        while (completedProcesses < processCount) {
            if (readyQueue.isEmpty()) {
                // If no process is ready, increment time and check again
                currentTime++;
                continue;
            }

            // Fetch the first process from the ready queue
            Process currentProcess = readyQueue.poll();
            executionOrder.add(currentProcess.getProcessID()); // Store execution order for Gantt chart
            timeStamps.add(currentTime); // Store timestamp of execution start

            // Determine execution time (minimum of time quantum or remaining burst time)
            int executionTime = Math.min(timeQuantum, currentProcess.getRemainingTime());
            currentTime += executionTime; // Move forward in time
            currentProcess.setRemainingTime(currentProcess.getRemainingTime() - executionTime);

            // Add any new arriving processes to the ready queue
            while (index < processCount && processList.get(index).getArrivalTime() <= currentTime) {
                readyQueue.add(processList.get(index));
                index++;
            }

            // If process still has remaining execution time, re-add it to the queue
            if (currentProcess.getRemainingTime() > 0) {
                readyQueue.add(currentProcess);
            } else {
                // Process completed execution
                completedProcesses++;
                currentProcess.setFinishTime(currentTime);
            }
        }

        // Add the final timestamp for Gantt chart visualization
        timeStamps.add(currentTime);

        // Print the Gantt chart for execution order
        printGanttChart(executionOrder, timeStamps);

        // Calculate and print waiting and turnaround times for all processes
        printWaitingAndTurnaroundTimes();
    }
}
