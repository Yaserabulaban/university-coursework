import java.util.*;

class NonPrePriority extends SchedulingAlgorithm {

    /**
     * Constructor for Non-Preemptive Priority scheduling algorithm.
     *
     * @param processList List of processes to be scheduled.
     */
    public NonPrePriority(ArrayList<Process> processList) {
        super(processList);
    }

    /**
     * Executes the Non-Preemptive Priority scheduling simulation.
     */
    @Override
    public void executeSimulation() {
        Queue<Process> readyQueue = new PriorityQueue<>(
                Comparator.comparingInt(Process::getPriority).thenComparingInt(Process::getArrivalTime));

        processList.sort(Comparator.comparingInt(Process::getArrivalTime));

        int currentTime = 0; // Tracks the current time in the simulation
        int completedProcesses = 0; // Counter for completed processes
        int processCount = processList.size(); // Total number of processes
        List<String> executionOrder = new ArrayList<>(); // Stores the execution order for Gantt chart
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
                currentTime = processList.get(index).getArrivalTime(); // Jump to next process arrival
                continue;
            }

            // Fetch and execute the highest priority process in the ready queue
            Process currentProcess = readyQueue.poll();
            executionOrder.add(currentProcess.getProcessID()); // Store process execution order
            timeStamps.add(currentTime); // Store timestamp of execution start

            // Process execution: move forward by burst time
            currentTime += currentProcess.getBurstTime();
            currentProcess.setFinishTime(currentTime); // Set finishing time
            completedProcesses++; // Increment completed process count

            // Add newly arrived processes to the ready queue
            while (index < processCount && processList.get(index).getArrivalTime() <= currentTime) {
                readyQueue.add(processList.get(index));
                index++;
            }
        }

        // Add the final timestamp for Gantt chart
        timeStamps.add(currentTime);

        // Print the Gantt chart visualization
        printGanttChart(executionOrder, timeStamps);

        // Calculate and print waiting and turnaround times
        printWaitingAndTurnaroundTimes();
    }
}
