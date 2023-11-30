import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;

public class FCFS {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        String[] processNames = new String[n]; // Array to store process names
        int[][] processes = new int[n][6]; // Matrix to store process details

        System.out.println("Enter details for each process:");

        // Input for process details in a table format
        System.out.println("ProcessName\tArrival Time\tBurst Time");
        for (int i = 0; i < n; i++) {
            processNames[i] = scanner.next(); // Process Name
            processes[i][0] = scanner.nextInt(); // Arrival Time
            processes[i][1] = scanner.nextInt(); // Burst Time
        }

        // Sort processes based on arrival time while maintaining process IDs order
        Arrays.sort(processes, Comparator.comparingInt(o -> o[0]));

        // Calculate completion, turnaround, waiting, and response times
        int currentTime = 0;
        int totalTurnaroundTime = 0;
        int totalWaitingTime = 0;

        System.out.println("\nGantt Chart:");
        System.out.print(" ");
        for (int i = 0; i < n; i++) {
            System.out.print("---------");
        }
        System.out.println();

        for (int i = 0; i < n; i++) {
            int processID = i;
            currentTime = Math.max(currentTime, processes[processID][0]);

            // Display the Gantt Chart
            for (int j = 0; j < currentTime; j++) {
                System.out.print(" ");
            }
            for (int j = 0; j < processes[processID][1]; j++) {
                System.out.print("|" + processNames[processID]);
            }
            currentTime += processes[processID][1];

            processes[processID][2] = currentTime; // Completion Time
            processes[processID][3] = processes[processID][2] - processes[processID][0]; // Turnaround Time
            processes[processID][4] = processes[processID][3] - processes[processID][1]; // Waiting Time
            processes[processID][5] = processes[processID][4]; // Response Time

            totalTurnaroundTime += processes[processID][3];
            totalWaitingTime += processes[processID][4];
        }

        System.out.println();
        System.out.print(" ");
        for (int i = 0; i < n; i++) {
            System.out.print("---------");
        }
        System.out.println();

        // Display the sorted details according to execution order
        System.out.println("\nExecution Order:\nProcessName\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time");
        for (int i = 0; i < n; i++) {
            System.out.println(processNames[i] + "\t\t" + processes[i][0] + "\t\t" + processes[i][1] +
                    "\t\t" + processes[i][2] + "\t\t" + processes[i][3] + "\t\t" + processes[i][4] +
                    "\t\t" + processes[i][5]);
        }

        // Calculate and display average turnaround time and average waiting time
        double avgTurnaroundTime = (double) totalTurnaroundTime / n;
        double avgWaitingTime = (double) totalWaitingTime / n;
        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);

        scanner.close();
    }
}
