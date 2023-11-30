import java.util.*;
public class SJF_NP {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        String[] processNames = new String[n]; // Array to store process names
        int[][] processes = new int[n][4]; // Matrix to store process details

        System.out.println("Enter details for each process:");

        // Input for process details in a table format
        System.out.println("ProcessName\tArrival Time\tBurst Time");
        for (int i = 0; i < n; i++) {
            processNames[i] = scanner.next(); // Process Name
            processes[i][0] = scanner.nextInt(); // Arrival Time
            processes[i][1] = scanner.nextInt(); // Burst Time
            processes[i][2] = -1; // Completion Time (initialized to -1)
            processes[i][3] = i + 1; // Process ID
        }

        // Sort processes based on arrival time
        Arrays.sort(processes, Comparator.comparingInt(o -> o[0]));

        int currentTime = 0;
        int totalTurnaroundTime = 0;
        int totalWaitingTime = 0;

        ArrayList<Integer> executedProcesses = new ArrayList<>();

        while (executedProcesses.size() < n) {
            int minBurstIndex = -1;
            int minBurst = Integer.MAX_VALUE;

            for (int i = 0; i < n; i++) {
                if (!executedProcesses.contains(i) && processes[i][0] <= currentTime && processes[i][1] < minBurst) {
                    minBurstIndex = i;
                    minBurst = processes[i][1];
                }
            }

            if (minBurstIndex != -1) {
                executedProcesses.add(minBurstIndex);
                processes[minBurstIndex][2] = currentTime + minBurst; // Completion Time
                processes[minBurstIndex][3] = processes[minBurstIndex][2] - processes[minBurstIndex][0]; // Turnaround Time
                totalTurnaroundTime += processes[minBurstIndex][3];
                totalWaitingTime += currentTime - processes[minBurstIndex][0]; // Waiting Time
                currentTime += minBurst;
            } else {
                currentTime++;
            }
        }

        // Display the sorted details according to execution order
        System.out.println("\nExecution Order:\nProcessName\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < n; i++) {
            System.out.println(processNames[i] + "\t\t" + processes[i][0] + "\t\t" + processes[i][1] +
                    "\t\t" + processes[i][2] + "\t\t" + processes[i][3] + "\t\t" +
                    (processes[i][3] - processes[i][1]));
        }

        // Calculate and display average turnaround time and average waiting time
        double avgTurnaroundTime = (double) totalTurnaroundTime / n;
        double avgWaitingTime = (double) totalWaitingTime / n;
        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);

        scanner.close();
    }
}
