import java.util.*;

public class Priority_Preemptive {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int n = scanner.nextInt();

        String[] processNames = new String[n];
        int[][] processes = new int[n][7]; // Adding more columns for additional details

        System.out.println("Enter details for each process:");
        System.out.println("ProcessName\tArrival Time\tBurst Time\tPriority (Low numbers indicate high priority)");
        for (int i = 0; i < n; i++) {
            processNames[i] = scanner.next();
            processes[i][0] = scanner.nextInt(); // Arrival Time
            processes[i][1] = scanner.nextInt(); // Burst Time
            processes[i][2] = scanner.nextInt(); // Priority
            processes[i][3] = processes[i][1]; // Remaining Burst Time
            processes[i][4] = -1; // Finish Time
            processes[i][5] = -1; // Turnaround Time
            processes[i][6] = -1; // Waiting Time
        }

        int currentTime = 0;
        int completedProcesses = 0;
        int[] waitingTime = new int[n];
        int[] turnaroundTime = new int[n];
        int totalTurnaroundTime = 0;
        int totalWaitingTime = 0;

        while (completedProcesses < n) {
            int minPriority = Integer.MAX_VALUE;
            int selectedProcess = -1;
            for (int i = 0; i < n; i++) {
                if (processes[i][0] <= currentTime && processes[i][3] > 0 && processes[i][2] < minPriority) {
                    minPriority = processes[i][2];
                    selectedProcess = i;
                }
            }

            if (selectedProcess == -1) {
                currentTime++;
                continue;
            }

            processes[selectedProcess][3]--;
            currentTime++;

            if (processes[selectedProcess][3] == 0) {
                int completionTime = currentTime;
                int arrivalTime = processes[selectedProcess][0];
                int burstTime = processes[selectedProcess][1];

                turnaroundTime[selectedProcess] = completionTime - arrivalTime;
                waitingTime[selectedProcess] = turnaroundTime[selectedProcess] - burstTime;
                processes[selectedProcess][4] = completionTime; // Finish Time
                processes[selectedProcess][5] = turnaroundTime[selectedProcess]; // Turnaround Time
                processes[selectedProcess][6] = waitingTime[selectedProcess]; // Waiting Time

                totalTurnaroundTime += turnaroundTime[selectedProcess];
                totalWaitingTime += waitingTime[selectedProcess];

                completedProcesses++;
            }
        }

        // Display the details
        System.out.println("\nProcessName\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time");
        for (int i = 0; i < n; i++) {
            System.out.println(processNames[i] + "\t\t" + processes[i][0] + "\t\t" + processes[i][1] +
                    "\t\t" + processes[i][4] + "\t\t" + processes[i][5] + "\t\t" + processes[i][6]);
        }

        double avgTurnaroundTime = (double) totalTurnaroundTime / n;
        double avgWaitingTime = (double) totalWaitingTime / n;
        System.out.println("\nAverage Turnaround Time: " + avgTurnaroundTime);
        System.out.println("Average Waiting Time: " + avgWaitingTime);

        scanner.close();
    }
}

