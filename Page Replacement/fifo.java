import java.util.*;

public class fifo {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the reference string (without space): ");
        String refString = sc.nextLine();
        System.out.print("Enter the Number of frames: ");
        int memSize = sc.nextInt();

        int pageFaults = 0;
        int pageHits = 0;
        List<Character> memory = new ArrayList<>();
        Set<Character> pageSet = new HashSet<>();

        System.out.println("\nPage replacement process:");
        for (char page : refString.toCharArray()) {
            System.out.println("Page: " + page);
            if (pageSet.contains(page)) {
                pageHits++;
            } else {
                pageFaults++;
                if (memory.size() < memSize) {
                    memory.add(page);
                    pageSet.add(page);
                } else {
                    char removedPage = memory.get(0);
                    memory.remove(0);
                    pageSet.remove(removedPage);
                    memory.add(page);
                    pageSet.add(page);

                }
            }
            printMemoryState(memory);
        }

        double pageFaultRate = (double) pageFaults / (pageFaults + pageHits);
        double pageHitRate = (double) pageHits / (pageFaults + pageHits);

        System.out.println("\nNumber of page faults: " + pageFaults);
        System.out.println("Number of page hits: " + pageHits);
        System.out.println("Page fault rate: " + pageFaultRate);
        System.out.println("Page hit rate: " + pageHitRate);
    }

    private static void printMemoryState(List<Character> memory) {
        System.out.print("Memory state: ");
        for (char page : memory) {
            System.out.print(page + " ");
        }
        System.out.println();
    }
}
