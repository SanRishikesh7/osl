import java.util.*;

public class lru {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the reference string: ");
        String refString = sc.nextLine();
        System.out.print("Enter the memory size: ");
        int memSize = sc.nextInt();

        int pageFaults = 0;
        int pageHits = 0;
        List<Character> memory = new ArrayList<>();
        LinkedHashMap<Character, Integer> pageMap = new LinkedHashMap<>();

        System.out.println("\nPage replacement process:");
        for (char page : refString.toCharArray()) {
            System.out.println("Page: " + page);
            if (memory.contains(page)) {
                pageHits++;
                pageMap.remove(page);
                pageMap.put(page, pageMap.size());
            } else {
                pageFaults++;
                if (memory.size() < memSize) {
                    memory.add(page);
                    pageMap.put(page, pageMap.size());
                } else {
                    char leastRecentlyUsed = pageMap.entrySet().iterator().next().getKey();
                    pageMap.remove(leastRecentlyUsed);
                    memory.remove(Character.valueOf(leastRecentlyUsed));
                    memory.add(page);
                    pageMap.put(page, pageMap.size());
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
