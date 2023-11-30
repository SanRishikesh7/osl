import java.util.*;

public class opt {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the reference string: ");
        String refString = sc.nextLine();
        System.out.print("Enter the memory size: ");
        int memSize = sc.nextInt();

        int pageFaults = 0;
        int pageHits = 0;
        List<Character> memory = new ArrayList<>();
        List<Character> reference = new ArrayList<>();
        for (char c : refString.toCharArray()) {
            reference.add(c);
        }

        System.out.println("\nPage replacement process:");
        for (int i = 0; i < reference.size(); i++) {
            char page = reference.get(i);
            System.out.println("Page: " + page);
            if (memory.contains(page)) {
                pageHits++;
            } else {
                pageFaults++;
                if (memory.size() < memSize) {
                    memory.add(page);
                } else {
                    char pageToReplace = findPageToReplace(reference, i + 1, memory);
                    memory.remove(Character.valueOf(pageToReplace));
                    memory.add(page);
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

    private static char findPageToReplace(List<Character> reference, int index, List<Character> memory) {
        int farthest = 0;
        char pageToReplace = memory.get(0);
        for (char page : memory) {
            int currentIndex = reference.subList(index, reference.size()).indexOf(page);
            if (currentIndex == -1) {
                return page;
            }
            if (currentIndex > farthest) {
                farthest = currentIndex;
                pageToReplace = page;
            }
        }
        return pageToReplace;
    }

    private static void printMemoryState(List<Character> memory) {
        System.out.print("Memory state: ");
        for (char page : memory) {
            System.out.print(page + " ");
        }
        System.out.println();
    }
}
