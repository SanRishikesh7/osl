import java.util.*;

public class sstf {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the initial head position: ");
        int initialHead = sc.nextInt();

        System.out.print("Enter the number of disk requests: ");
        int n = sc.nextInt();
        int[] diskRequests = new int[n];
        System.out.println("Enter the disk requests:");
        for (int i = 0; i < n; i++) {
            diskRequests[i] = sc.nextInt();
        }

        int totalSeekTime = calculateSeekTime(initialHead, diskRequests);
        System.out.println("Total seek time: " + totalSeekTime);

        System.out.println("Seek Sequence:");
        printSeekSequence(initialHead, diskRequests);
    }

    private static int calculateSeekTime(int initialHead, int[] diskRequests) {
        int seekTime = 0;
        int currentPosition = initialHead;
        int totalRequests = diskRequests.length;
        boolean[] visited = new boolean[totalRequests];

        for (int i = 0; i < totalRequests; i++) {
            int minDistance = Integer.MAX_VALUE;
            int minIndex = -1;
            for (int j = 0; j < totalRequests; j++) {
                if (!visited[j]) {
                    int distance = Math.abs(diskRequests[j] - currentPosition);
                    if (distance < minDistance) {
                        minDistance = distance;
                        minIndex = j;
                    }
                }
            }
            seekTime += minDistance;
            currentPosition = diskRequests[minIndex];
            visited[minIndex] = true;
        }
        return seekTime;
    }

    private static void printSeekSequence(int initialHead, int[] diskRequests) {
        StringBuilder sequence = new StringBuilder();
        sequence.append(initialHead);
        int currentPosition = initialHead;
        int totalRequests = diskRequests.length;
        boolean[] visited = new boolean[totalRequests];

        for (int i = 0; i < totalRequests; i++) {
            int minDistance = Integer.MAX_VALUE;
            int minIndex = -1;
            for (int j = 0; j < totalRequests; j++) {
                if (!visited[j]) {
                    int distance = Math.abs(diskRequests[j] - currentPosition);
                    if (distance < minDistance) {
                        minDistance = distance;
                        minIndex = j;
                    }
                }
            }
            sequence.append(" -> ").append(diskRequests[minIndex]);
            currentPosition = diskRequests[minIndex];
            visited[minIndex] = true;
        }
        System.out.println(sequence.toString());
    }
}
