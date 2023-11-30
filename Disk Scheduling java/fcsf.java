import java.util.*;

public class fcsf {

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
        for (int i = 0; i < diskRequests.length; i++) {
            seekTime += Math.abs(diskRequests[i] - currentPosition);
            currentPosition = diskRequests[i];
        }
        return seekTime;
    }

    private static void printSeekSequence(int initialHead, int[] diskRequests) {
        StringBuilder sequence = new StringBuilder();
        sequence.append(initialHead);
        int currentPosition = initialHead;
        for (int i = 0; i < diskRequests.length; i++) {
            sequence.append(" -> ").append(diskRequests[i]);
            currentPosition = diskRequests[i];
        }
        System.out.println(sequence.toString());
    }
}
