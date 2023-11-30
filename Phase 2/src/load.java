import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.AbstractMap;
import java.util.Arrays;
import java.util.Map;

class MainMemory {
    // Main memory
    private char[][] M;

    // Constructor
    public MainMemory() {
        // this is the main memory
        this.M = new char[300][4];
    }

    // getter for the main memory
    public char[][] getMemory() {
        return this.M;
    }

    // setter for the main memory
    public void setMemory(char[][] M) {
        this.M = M;
    }
}

public class load {

    // Memory
    private MainMemory M;

    // Declare the input file and the output file
    private FileReader input;
    private FileWriter output;

    // Declare the input and output reader
    private BufferedReader inputReader;
    private BufferedWriter outputReader;

    // The buffer to store the data
    private char[] buffer = new char[40];

    // used_memory to store the used memory
    private int used_memory = 0;

    // Page Table Register
    private int pageTableRegister;
    // generated random numbers
    public int generated[] = new int[30];

    public load(String input, String output) {
        // Initializing the input and output file
        try {
            this.input = new FileReader(input);
            this.output = new FileWriter(output);
            this.inputReader = new BufferedReader(this.input);
            this.outputReader = new BufferedWriter(this.output);
        } catch (Exception e) {
            System.out.println("Error in initializing the input and output file");
        }
    }

    // init Method to initialize everything to zero
    public void init() {
        Arrays.fill(this.generated, 0);
        // Inititalizing the main memory
        System.out.println("Initializing the main memory\n");
        used_memory = 0;
        // Initializing the main memory
        this.M = new MainMemory();
        // Initializing the page table register
        this.pageTableRegister = 0;
    }

    protected Map.Entry<Integer, int[]> allocate(int[] arr) {

        // generating a random value from 0-29
        int value = (int) (Math.random() * 30);
        System.out.println("The value is : " + value + "\n");

        // check wheather it is generated if it is then again generate new value
        while (true) {
            if (arr[value] == 0) {
                arr[value] = 1;
                break;
            } else {
                value = (int) (Math.random() * 30);
            }
        }

        // returning the value and the arr
        // creating a map entry
        Map.Entry<Integer, int[]> pair = new AbstractMap.SimpleEntry<Integer, int[]>(value, arr);

        return pair;
    }

    public void printMemory() {
        char m[][] = M.getMemory();
        System.out.println("Printing the memory...\n");
        // print memory in form of boxes
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 4; j++) {
                if (m[i][j] == 0) {
                    System.out.print(" - ");
                } else {
                    System.out.print(" " + m[i][j] + " ");
                }
                if (j == 3) {
                    System.out.println();
                } else {
                    System.out.print("|");
                }
            }
            System.out.println();
        }
    }

    // loadProgram method to load the program to the memory
    private void loadProgram(char[][] memory, char[] buffer) {
        if (used_memory >= (pageTableRegister + 10)) {
            System.out.println("Memory is full");
        }

        // getting the frame number for storing the porgram card
        Map.Entry<Integer, int[]> pair = allocate(generated);

        // getting the frame number
        int frameNumber = pair.getKey();
        System.out.println("The page table register is : " + pageTableRegister + "\n");
        System.out.println("the current pointer is : " + used_memory + "\n");
        System.out.println("The frame number is : " + frameNumber * 10 + "\n");

        // getting the generated array
        generated = pair.getValue();
        System.out.println("With the addition The Generated array is : ");
        for (int i = 0; i < 30; i++)
            System.out.print(generated[i] + " ");
        System.out.println("\n");

        // storing the frame number into the page table register
        memory[used_memory][2] = (char) (frameNumber / 10 + '0');
        memory[used_memory][3] = (char) (frameNumber % 10 + '0');
        // printMemory();

        // storing the data into the frame
        int framePtr = frameNumber * 10;
        System.out.println("The frame pointer is :: " + framePtr);
        // for (int i = 0; i < buffer.length;) {
        // memory[framePtr][i % 4] = buffer[i];
        // if(buffer[i] == 'H' || buffer[i] == '\0')
        // framePtr += 10 - (framePtr%10);

        // i++;
        // if (i % 4 == 0) {
        // framePtr++;
        // }

        // }
        int k = 0;
        for (int i = framePtr; i < (framePtr + 10) && k < buffer.length; i++) {
            for (int j = 0; j < 4 && k < buffer.length; j++) {
                memory[i][j] = buffer[k++];
            }
        }

        // printing the memory
        System.out.println("The memory after loading the program card is : \n");
        // printMemory();

        M.setMemory(memory);
        used_memory++;
        System.out.println("The  used memory Now is : " + used_memory + "\n");

    }

    // LOAD method to load the data from the input file to the main memory
    public void LOAD() {
        String line = "";

        try {
            while ((line = inputReader.readLine()) != null) {
                buffer = line.toCharArray();
                System.out.println("The buffer is : " + String.valueOf(buffer) + "\n");

                if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J') {
                    System.out.println("Program card detected " + buffer[4] + buffer[5] + buffer[6] + buffer[7]);

                    init();

                    // Now calling the allocate method to allocate the memory
                    // Creating the pageTableRegister
                    // assiging a random value from 0-29 to the pageTableRegister variable
                    Map.Entry<Integer, int[]> pair = allocate(generated);
                    pageTableRegister = pair.getKey() * 10; // Page table register
                    used_memory = pageTableRegister;
                    generated = pair.getValue();
                    // Printing the pageTableRegister
                    System.out.println("\n The pageTableRegister is : " + this.pageTableRegister + "\n");

                    // Initializing the PTR block with special characters
                    char[][] memory = M.getMemory();

                    for (int i = pageTableRegister; i < (pageTableRegister + 10); i++) {
                        System.out.println("The value of i is : " + i + "\n");
                        for (int j = 0; j < 4; j++) {
                            memory[i][j] = '*';
                        }
                    }
                    M.setMemory(memory);

                    continue;

                } else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A') {
                    System.out.println("Data card detected");
                    continue;
                } else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D') {
                    System.out.println("End card detected\n");
                    continue;
                } else {
                    System.out.println("Loading the instructions to memory");
                    char memory[][] = M.getMemory();

                    loadProgram(memory, buffer);
                }

                // for (int i = 0; i < line.length();) {
                // memory[used_memory][i % 4] = buffer[i];
                // if(buffer[i] == 'H' || buffer[i] == '\0')
                // used_memory += 10 - (used_memory%10);

                // i++;
                // if (i % 4 == 0) {
                // used_memory++;
                // }

                // }
                // if(used_memory%10==9)
                // used_memory += 10 - (used_memory%10);
                printMemory();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        load l  = new load("ip.txt", "output.txt");
        l.init();
        l.LOAD();   
    }
}
