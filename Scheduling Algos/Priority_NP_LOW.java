import java.util.*;

public class Priority_NP_LOW {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        String[] processNames = new String[n];
        int[][] processes = new int[n][4];

        System.out.println("Enter details for each process:");
        System.out.println("ProcessName\tArrival Time\tBurst Time\tPriority");
        for (int i = 0; i < n; i++) {
            processNames[i] = scanner.next();
            processes[i][0] = scanner.nextInt(); // Arrival Time
            processes[i][1] = scanner.nextInt(); // Burst Time
            processes[i][2] = -scanner.nextInt(); // Negative Priority (Higher priority is indicated by lower negative numbers)
            processes[i][3] = i + 1; // Process ID
        }

        // Sort processes based on arrival time and priority (lower numbers indicate higher priority)
        Arrays.sort(processes, Comparator.comparingInt((int[] arr) -> arr[0]).thenComparingInt(arr -> arr[2]));

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
                currentTime += burstTime;
            } else {
                currentTime++;
            }
        }

        System.out.println("\nExecution Order:\nProcessName\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < n; i++) {
            System.out.println(processNames[i] + "\t\t" + processes[i][0] + "\t\t" + processes[i][1] +
                    "\t\t" + (-processes[i][2]) + "\t\t" + processes[i][3] +
                    "\t\t" + (processes[i][3] - processes[i][0]) + "\t\t" +
                    (processes[i][3] - processes[i][0] - processes[i][1]));
        }

        double avgTurnaroundTime = (double) totalTurnaroundTime / n;
        double avgWaitingTime = (double) totalWaitingTime / n;
        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);

        scanner.close();
    }
}
