import java.util.Scanner;

public class BankersAlgo {
    private int[][] need;
    private int[][] allocation;
    private int[][] max;
    private int[] available;
    private int numOfProcesses;
    private int numOfResources;

    public void initializeData() {
        Scanner scanner = new Scanner(System.in);

        // Taking inputs for the number of processes and resources
        System.out.print("Enter number of processes: ");
        numOfProcesses = scanner.nextInt();
        System.out.print("Enter number of resources: ");
        numOfResources = scanner.nextInt();

        // Initializing matrices
        allocation = new int[numOfProcesses][numOfResources];
        max = new int[numOfProcesses][numOfResources];
        need = new int[numOfProcesses][numOfResources];
        available = new int[numOfResources];

        // Taking allocation matrix input
        System.out.println("Enter allocation matrix:");
        for (int i = 0; i < numOfProcesses; i++) {
            for (int j = 0; j < numOfResources; j++) {
                allocation[i][j] = scanner.nextInt();
            }
        }

        // Taking max matrix input
        System.out.println("Enter max matrix:");
        for (int i = 0; i < numOfProcesses; i++) {
            for (int j = 0; j < numOfResources; j++) {
                max[i][j] = scanner.nextInt();
                // Calculating the need matrix
                need[i][j] = max[i][j] - allocation[i][j];
            }
        }

        // Calculate available resources based on allocation
        int[] totalResources = new int[numOfResources];
        System.out.println("Enter total resources:");
        for (int i = 0; i < numOfResources; i++) {
            totalResources[i] = scanner.nextInt();
        }

        for (int j = 0; j < numOfResources; j++) {
            int allocatedResources = 0;
            for (int i = 0; i < numOfProcesses; i++) {
                allocatedResources += allocation[i][j];
            }
            available[j] = totalResources[j] - allocatedResources;
        }
    }

    public boolean isSafe() {
        boolean[] finish = new boolean[numOfProcesses];
        int[] work = new int[numOfResources];
        System.arraycopy(available, 0, work, 0, numOfResources);

        StringBuilder safeSequence = new StringBuilder();
        int count = 0;
        while (count < numOfProcesses) {
            boolean found = false;
            for (int i = 0; i < numOfProcesses; i++) {
                if (!finish[i]) {
                    int j;
                    for (j = 0; j < numOfResources; j++) {
                        if (need[i][j] > work[j]) {
                            break;
                        }
                    }
                    if (j == numOfResources) {
                        for (int k = 0; k < numOfResources; k++) {
                            work[k] += allocation[i][k];
                        }
                        finish[i] = true;
                        found = true;
                        count++;
                        safeSequence.append("P").append(i).append(" ");
                    }
                }
            }
            if (!found) {
                break;
            }
        }

        if (count == numOfProcesses) {
            System.out.println("The system is in a safe state.");
            System.out.println("Safe Sequence: " + safeSequence.toString());
            return true;
        } else {
            System.out.println("Deadlock Detected!! \nThe system is in an unsafe state.");
            return false;
        }
    }

    public static void main(String[] args) {
        BankersAlgo BankersAlgo = new BankersAlgo();
        BankersAlgo.initializeData();
        BankersAlgo.isSafe();
    }
}
