import java.util.*;

/**
 * Implements the Shortest Remaining Time (SRT) scheduling algorithm.
 * This is a preemptive scheduling algorithm that selects the process
 * with the shortest remaining execution time at each time unit.
 */
class ShortestRemainingTime extends SchedulingAlgorithm {

    /**
     * Constructor for the Shortest Remaining Time scheduling algorithm.
     *
     * @param processList List of processes to be scheduled.
     */
    public ShortestRemainingTime(ArrayList<Process> processList) {
        super(processList);
    }

    /**
     * Executes the Shortest Remaining Time scheduling simulation.
     */
    @Override
    public void executeSimulation() {
        Queue<Process> readyQueue = new ArrayDeque<>();

        // Sort processes by Arrival Time to ensure correct scheduling order
        processList.sort(Comparator.comparingInt(Process::getArrivalTime));

        int currentTime = 0; // Tracks the current time in the simulation
        int completedProcesses = 0; // Counter for completed processes
        int processCount = processList.size(); // Total number of processes
        Process previousProcess = null; // Tracks the last executed process
        List<String> executionOrder = new ArrayList<>(); // Stores execution order for Gantt chart
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

            // Select the process with the shortest remaining execution time
            Process currentProcess = readyQueue.peek();
            for (Process process : readyQueue) {
                if (process.getRemainingTime() < currentProcess.getRemainingTime()) {
                    currentProcess = process;
                }
            }

            // If the process changes, log it in the execution order
            if (previousProcess == null || currentProcess != previousProcess) {
                executionOrder.add(currentProcess.getProcessID());
                timeStamps.add(currentTime);
            }

            // Execute the selected process for 1 time unit
            currentTime++;
            currentProcess.setRemainingTime(currentProcess.getRemainingTime() - 1);

            // Add newly arrived processes to the ready queue
            while (index < processCount && processList.get(index).getArrivalTime() <= currentTime) {
                readyQueue.add(processList.get(index));
                index++;
            }

            // If process completes execution, remove it from the queue and update finish
            // time
            if (currentProcess.getRemainingTime() == 0) {
                completedProcesses++;
                currentProcess.setFinishTime(currentTime);
                readyQueue.remove(currentProcess);
            }

            // Update the previous process tracker
            previousProcess = currentProcess;
        }

        // Add the final timestamp for Gantt chart visualization
        timeStamps.add(currentTime);

        // Print the Gantt chart for execution order
        printGanttChart(executionOrder, timeStamps);

        // Calculate and print waiting and turnaround times for all processes
        printWaitingAndTurnaroundTimes();
    }
}