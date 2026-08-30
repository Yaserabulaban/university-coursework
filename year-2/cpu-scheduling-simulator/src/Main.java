import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Add a section heading
        System.out.println("\n========================");
        System.out.println(" CPU SCHEDULING SIMULATOR");
        System.out.println("========================\n");

        // Get a valid number of processes (>= 1)
        int input = getValidInteger(scanner, "Enter number of processes:\n", 1);

        // List to store process details
        ArrayList<Process> processList = new ArrayList<>();

        // Loop to collect valid process details from the user
        for (int i = 0; i < input; i++) {
            String str = "P" + i;

            // Get valid Burst Time (> 0)
            int burstTime = getValidInteger(scanner, "Enter burst time for process " + str + " (must be > 0):\n", 1);

            // Get valid Arrival Time (>= 0)
            int arrivalTime = getValidInteger(scanner, "Enter arrival time for process " + str + " (must be >= 0):\n",
                    0);

            // Get valid Priority (>= 0)
            int priority = getValidInteger(scanner, "Enter priority for process " + str + " (must be >= 0):\n", 0);

            // Add the validated process to the list
            processList.add(new Process(str, burstTime, arrivalTime, priority));
        }

        // Display process summary
        printSimulationDetails(processList);

        boolean continueProgram = true;

        while (continueProgram) {
            // Add a heading for scheduling algorithm selection
            System.out.println("\n========================");
            System.out.println(" SELECT SCHEDULING ALGORITHM");
            System.out.println("========================");
            System.out.println("1. Shortest Remaining Time");
            System.out.println("2. Non-Preemptive Priority");
            System.out.println("3. Round Robin");
            System.out.println("4. Shortest Job Next");
            System.out.println("5. Exit Program");

            // Get a valid algorithm choice
            int choice = getValidInteger(scanner, "Enter your choice (1-5):", 1, 5);

            System.out.println(processList.size() + " processes.");
            // Execute the selected scheduling algorithm
            switch (choice) {
                case 1:
                    new ShortestRemainingTime(processList).executeSimulation();
                    break;
                case 2:
                    new NonPrePriority(processList).executeSimulation();
                    break;
                case 3:
                    // Get valid Time Quantum (> 0)
                    int timeQuantum = getValidInteger(scanner, "Enter Time Quantum (must be > 0):\n", 1);
                    new RoundRobin(processList, timeQuantum).executeSimulation();
                    break;
                case 4:
                    new ShortestJobNext(processList).executeSimulation();
                    break;
                default:
                    System.out.println("Invalid Choice. Exiting program.");
            }

            // Prompt user whether to run another algorithm or exit
            System.out.println("\nDo you want to run another scheduling algorithm?");
            System.out.println("1. Yes");
            System.out.println("2. No (Exit)");

            int continueChoice = getValidInteger(scanner, "Enter your choice (1-2):", 1, 2);
            if (continueChoice == 2) {
                System.out.println("\nExiting the program. Goodbye!");
                continueProgram = false;
            }
        }
    }

    /**
     * Ensures the user inputs a valid integer within a specified range.
     *
     * @param scanner Scanner object for input.
     * @param message Prompt message for user input.
     * @param min     Minimum valid value.
     * @return A valid integer input.
     */
    private static int getValidInteger(Scanner scanner, String message, int min) {
        return getValidInteger(scanner, message, min, Integer.MAX_VALUE);
    }

    /**
     * Ensures the user inputs a valid integer within a specific range.
     *
     * @param scanner Scanner object for input.
     * @param message Prompt message for user input.
     * @param min     Minimum valid value.
     * @param max     Maximum valid value.
     * @return A valid integer input within the specified range.
     */
    private static int getValidInteger(Scanner scanner, String message, int min, int max) {
        int value;
        while (true) {
            System.out.print(message);
            if (scanner.hasNextInt()) { // Check if input is an integer
                value = scanner.nextInt();
                if (value >= min && value <= max) { // Ensure value is within range
                    return value;
                } else {
                    System.out.println("Error: Value must be at least " + min + ".");
                }
            } else {
                System.out.println("Error: Invalid input. Please enter an integer.");
                scanner.next(); // Clear invalid input
            }
        }
    }

    /**
     * Prints the details of the entered processes in a formatted manner.
     *
     * @param processList List of process objects
     */
    public static void printSimulationDetails(ArrayList<Process> processList) {
        System.out.println("\n========================");
        System.out.println(" PROCESS SUMMARY");
        System.out.println("========================");
        System.out.printf("| %-10s | %-12s | %-12s | %-10s |\n", "Process", "Burst Time", "Arrival Time", "Priority");
        System.out.println("|------------|--------------|--------------|------------|");

        for (Process currentProcess : processList) {
            System.out.printf("| %-10s | %-12d | %-12d | %-10d |\n",
                    currentProcess.getProcessID(),
                    currentProcess.getBurstTime(),
                    currentProcess.getArrivalTime(),
                    currentProcess.getPriority());
        }
        System.out.println("|------------|--------------|--------------|------------|\n");
    }
}