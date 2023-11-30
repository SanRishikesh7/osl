import java.util.*;

public class Priority_NP_HIGH {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        String[] processNames = new String[n]; // Array to store process names
        int[][] processes = new int[n][4]; // Matrix to store process details

        System.out.println("Enter details for each process:");

        // Input for process details in a table format
        System.out.println("ProcessName\tArrival Time\tBurst Time\tPriority");
        for (int i = 0; i < n; i++) {
            processNames[i] = scanner.next(); // Process Name
            processes[i][0] = scanner.nextInt(); // Arrival Time
            processes[i][1] = scanner.nextInt(); // Burst Time
            processes[i][2] = scanner.nextInt(); // Priority
            processes[i][3] = i + 1; // Process ID
        }

        // Sort processes based on arrival time
        Arrays.sort(processes, Comparator.comparingInt(arr -> arr[0]));

        int currentTime = 0;
        int totalTurnaroundTime = 0;
        int totalWaitingTime = 0;

        ArrayList<Integer> executedProcesses = new ArrayList<>();

        while (executedProcesses.size() < n) {
            int maxPriorityIndex = -1;
            int maxPriority = Integer.MIN_VALUE;

            for (int i = 0; i < n; i++) {
                if (!executedProcesses.contains(i) && processes[i][0] <= currentTime && processes[i][2] > maxPriority) {
                    maxPriorityIndex = i;
                    maxPriority = processes[i][2];
                }
            }

            if (maxPriorityIndex != -1) {
                executedProcesses.add(maxPriorityIndex);
                int burstTime = processes[maxPriorityIndex][1];
                processes[maxPriorityIndex][3] = currentTime + burstTime; // Completion Time
                totalTurnaroundTime += processes[maxPriorityIndex][3] - processes[maxPriorityIndex][0]; // Turnaround Time
                totalWaitingTime += processes[maxPriorityIndex][3] - processes[maxPriorityIndex][0] - burstTime; // Waiting Time
                currentTime += burstTime; // Move time forward by the burst time
            } else {
                currentTime++;
            }
        }

        // Display the sorted details according to execution order
        System.out.println("\nExecution Order:\nProcessName\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < n; i++) {
            System.out.println(processNames[i] + "\t\t" + processes[i][0] + "\t\t" + processes[i][1] +
                    "\t\t" + processes[i][2] + "\t\t" + processes[i][3] +
                    "\t\t" + (processes[i][3] - processes[i][0]) + "\t\t" +
                    (processes[i][3] - processes[i][0] - processes[i][1]));
        }

        // Calculate and display average turnaround time and average waiting time
        double avgTurnaroundTime = (double) totalTurnaroundTime / n;
        double avgWaitingTime = (double) totalWaitingTime / n;
        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);

        scanner.close();
    }
}
