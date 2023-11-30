import java.util.*;

public class SJF_Preemptive {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter no of process:");
        int totalProcesses = sc.nextInt();
        int pid[] = new int[totalProcesses];
        int arrivalTime[] = new int[totalProcesses];
        int burstTime[] = new int[totalProcesses];
        int completionTime[] = new int[totalProcesses];
        int turnaroundTime[] = new int[totalProcesses];
        int waitingTime[] = new int[totalProcesses];
        int flag[] = new int[totalProcesses];
        int TempBurst[] = new int[totalProcesses];
        int i, executedTime = 0, executedProcesses = 0;
        float averageWaitingTime = 0, averageTurnaroundTime = 0;

        
        System.out.println("ProcessName\tArrival Time\tBurst Time");
        for (i = 0; i < totalProcesses; i++) {
            pid[i] = i + 1;
            System.out.print(i + 1);
            arrivalTime[i] = sc.nextInt();
            burstTime[i] = sc.nextInt();
            TempBurst[i] = burstTime[i];
            flag[i] = 0;
        }

        while (true) {
            int min = 99, c = totalProcesses;
            if (executedProcesses == totalProcesses)
                break;

            for (i = 0; i < totalProcesses; i++) {
                if ((arrivalTime[i] <= executedTime) && (flag[i] == 0) && (burstTime[i] < min)) {
                    min = burstTime[i];
                    c = i;
                }
            }

            if (c == totalProcesses)
                executedTime++;
            else {
                burstTime[c]--;
                executedTime++;
                if (burstTime[c] == 0) {
                    completionTime[c] = executedTime;
                    flag[c] = 1;
                    executedProcesses++;
                }
            }
        }

        for (i = 0; i < totalProcesses; i++) {
            turnaroundTime[i] = completionTime[i] - arrivalTime[i];
            waitingTime[i] = turnaroundTime[i] - TempBurst[i];
            averageWaitingTime += waitingTime[i];
            averageTurnaroundTime += turnaroundTime[i];
        }

        System.out.println("pid  arrival  burst  complete turn waiting");
        for (i = 0; i < totalProcesses; i++) {
            System.out
                    .println(pid[i] + "\t" + arrivalTime[i] + "\t" + TempBurst[i] + "\t" + completionTime[i] + "\t" + turnaroundTime[i] + "\t" + waitingTime[i]);
        }

        System.out.println("\nAverage Turnaround Time is " + (float) (averageTurnaroundTime / totalProcesses));
        System.out.println("Average Waiting Time is " + (float) (averageWaitingTime / totalProcesses));
        sc.close();
    }
}



