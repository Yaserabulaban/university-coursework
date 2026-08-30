import java.util.ArrayList;
import java.util.List;

/**
 * Abstract base class for different CPU scheduling algorithms.
 * Provides common utility methods for displaying scheduling results.
 */
abstract class SchedulingAlgorithm {
    protected ArrayList<Process> processList; // List of processes to be scheduled

    /**
     * Constructor to initialize the process list.
     *
     * @param processList List of processes involved in scheduling.
     */
    public SchedulingAlgorithm(ArrayList<Process> processList) {
        this.processList = new ArrayList<>();
        for (Process p : processList) {
            this.processList.add(new Process(p)); // Assuming Process has a copy constructor
        }
    }

    /**
     * Abstract method to be implemented by subclasses for executing the scheduling
     * simulation.
     */
    public abstract void executeSimulation();

    /**
     * Prints the Gantt chart representation of process execution.
     *
     * @param executionOrder List of process execution order.
     * @param timeStamps     List of timestamps corresponding to execution
     *                       transitions.
     */
    protected void printGanttChart(List<String> executionOrder, List<Integer> timeStamps) {
        System.out.println("\nGantt Chart:");

        // Print process execution sequence
        System.out.print("|");
        for (String process : executionOrder) {
            System.out.print(" " + process + " |");
        }
        System.out.println();

        // Print corresponding timestamps
        for (int i = 0; i < timeStamps.size(); i++) {
            if (timeStamps.get(i) < 10) {
                System.out.print(timeStamps.get(i) + "    "); // Extra spacing for single-digit values
            } else {
                System.out.print(timeStamps.get(i) + "   "); // Standard spacing for better alignment
            }
        }
        System.out.println();
    }

    /**
     * Prints the waiting time and turnaround time for all processes.
     * Ensures a formatted output for better readability.
     */
    protected void printWaitingAndTurnaroundTimes() {
        System.out.println("\n===============================");
        System.out.println(" PROCESS COMPLETION SUMMARY");
        System.out.println("===============================");
        System.out.printf("| %-10s | %-12s | %-12s | %-15s | %-15s |\n",
                "Process", "Arrival", "Finish", "Waiting Time", "Turnaround Time");
        System.out.println("|------------|--------------|--------------|-----------------|-----------------|");

        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        for (Process process : processList) {

            int waitingTime = process.calculateWaitingTime();
            int turnaroundTime = process.calculateTurnaroundTime();

            totalWaitingTime += waitingTime;
            totalTurnaroundTime += turnaroundTime;

            System.out.printf("| %-10s | %-12d | %-12d | %-15d | %-15d |\n",
                    process.getProcessID(),
                    process.getArrivalTime(),
                    process.getFinishTime(),
                    process.calculateWaitingTime(),
                    process.calculateTurnaroundTime());
        }
        System.out.println("|------------|--------------|--------------|-----------------|-----------------|\n");

        // Display totals
        System.out.println("\nTotal Waiting Time: " + totalWaitingTime + " ms");
        System.out.println("Total Turnaround Time: " + totalTurnaroundTime + " ms");

        // Calculate and display averages
        double averageWaitingTime = (double) totalWaitingTime / processList.size();
        double averageTurnaroundTime = (double) totalTurnaroundTime / processList.size();

        System.out.println("Average Waiting Time: " + String.format("%.2f", averageWaitingTime) + " ms");
        System.out.println("Average Turnaround Time: " + String.format("%.2f", averageTurnaroundTime) + " ms");
        System.out.println("===============================\n");
    }
}