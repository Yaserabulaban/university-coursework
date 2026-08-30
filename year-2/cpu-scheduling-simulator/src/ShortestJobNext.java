import java.util.*;

/**
 * Implements the Shortest Job Next (SJN) scheduling algorithm.
 * This is a non-preemptive scheduling algorithm that selects the process
 * with the shortest burst time that has arrived in the system.
 */
class ShortestJobNext extends SchedulingAlgorithm {

    /**
     * Constructor for the Shortest Job Next scheduling algorithm.
     *
     * @param processList List of processes to be scheduled.
     */
    public ShortestJobNext(ArrayList<Process> processList) {
        super(processList);
    }

    /**
     * Executes the Shortest Job Next scheduling simulation.
     */
    @Override
    public void executeSimulation() {
        Queue<Process> readyQueue = new ArrayDeque<>();

        // Sort processes by Arrival Time first, then by Burst Time (shortest job first)
        processList.sort(Comparator.comparingInt(Process::getArrivalTime)
                .thenComparingInt(Process::getBurstTime));

        int currentTime = 0; // Tracks the current time in the simulation
        int completedProcesses = 0; // Counter for completed processes
        int processCount = processList.size(); // Total number of processes
        List<String> executionOrder = new ArrayList<>(); // Stores execution sequence for Gantt chart
        List<Integer> timeStamps = new ArrayList<>(); // Stores timestamps for Gantt chart

        int index = 0;
        // Add processes that have arrived initially to the ready queue
        while (index < processCount && processList.get(index).getArrivalTime() <= currentTime) {
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

            // Fetch and execute the shortest job (smallest burst time)
            Process currentProcess = readyQueue.poll();
            executionOrder.add(currentProcess.getProcessID()); // Store execution order for Gantt chart
            timeStamps.add(currentTime); // Store timestamp of execution start

            // Process execution: move forward by burst time
            currentTime += currentProcess.getBurstTime();
            currentProcess.setFinishTime(currentTime); // Set finishing time

            // Add newly arrived processes to the ready queue
            while (index < processCount && processList.get(index).getArrivalTime() <= currentTime) {
                readyQueue.add(processList.get(index));
                index++;
            }
            completedProcesses++; // Increment completed process count
        }

        // Add the final timestamp for Gantt chart visualization
        timeStamps.add(currentTime);

        // Print the Gantt chart for execution order
        printGanttChart(executionOrder, timeStamps);

        // Calculate and print waiting and turnaround times for all processes
        printWaitingAndTurnaroundTimes();
    }
}
