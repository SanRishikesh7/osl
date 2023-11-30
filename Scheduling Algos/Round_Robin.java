import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

class Helper {
    

    public void printTable(Table table) {
        //printing the table with borders
        // System.out.println("PID\tAT\tBT\tCT\tTAT\tWT\tRT\tPR");
        //print the values with the border around it
        System.out.println(table.pid + "\t" + table.arrivalTime + "\t" + table.burstTime + "\t" + table.completionTime + "\t" + table.turnAroundTime + "\t" + table.waitingTime + "\t" + table.responseTime + "\t" + table.priority);
    }
}



class Table {
    public int pid;
    public int arrivalTime;
    public int burstTime;
    public int completionTime;
    public int turnAroundTime;
    public int waitingTime;
    public int responseTime;
    public int priority;

    //creating constructor for setting the pid and arrivaletime and burst time
    public Table(int pid, int arrivalTime, int burstTime) {
        this.pid = pid;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }

    //creating the setter and getter for each variable

    public void setPid(int pid) {
        this.pid = pid;
    }

    public int getPid() {
        return pid;
    }

    public void setArrivalTime(int arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public void setBurstTime(int burstTime) {
        this.burstTime = burstTime;
    }


    public int getBurstTime() {
        return burstTime;
    }


    public void setCompletionTime(int completionTime) {
        this.completionTime = completionTime;
    }



    public int getCompletionTime() {
        return completionTime;
    }


    public void setTurnAroundTime(int turnAroundTime) {
        this.turnAroundTime = turnAroundTime;
    }

    public  int getTurnAroundTime() {
        return turnAroundTime;
    }

    public void setWaitingTime(int waitingTime) {
        this.waitingTime = waitingTime;
    }

    public int getWaitingTime() {
        return waitingTime;
    }

    public void setResponseTime(int responseTime) {
        this.responseTime = responseTime;
    }

    public int getResponseTime() {
        return responseTime;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public int getPriority() {
        return priority;
    }
}




public class Round_Robin {

     private static Table table = null;
     static int bt[]; //burst time array
     private static Helper h =null;

    //creating the arraylist for storing the process
    private static ArrayList<Table> process = new ArrayList<Table>();
    private static ArrayList<Table> completedProcess = new ArrayList<Table>();
    public static void main(String[] args) {

        //Reading from the process and adding it to the table class
        try(BufferedReader br = new BufferedReader(new FileReader("RR.txt"))) {
            String line;
            
            while((line = br.readLine()) != null) {
                
                String[] parts = line.split(",");
                if(parts.length == 3) {
                    int processName = Integer.parseInt(parts[0]);
                    
                    int arrivalTime = Integer.parseInt(parts[1]);
                    
                    int burstTime = Integer.parseInt(parts[2]);
                    

                    table = new Table(processName, arrivalTime, burstTime);
                    process.add(table);
                }
            }
        }catch(Exception e) {
            e.printStackTrace();
        }


        //assigning the burst time to bt array
        //Because while reducing the burst time it will get zero so while displaying 
        //we will require the origianl burst time
        bt = new int[process.size()];
        for(int i=0; i<process.size(); i++) {
            bt[i] = process.get(i).burstTime;
        }

        //Sorting the data according to the arrival time

        Collections.sort(process, new Comparator<Table> () {

            @Override
            public int compare(Table o1, Table o2) {
                // TODO Auto-generated method stub
                return o1.arrivalTime - o2.arrivalTime;
            }

        });


        //calculating the completion time
        System.out.println("process"+process);
        solve(process);
        
    }

    // ///arrived process
    // private static ArrayList<Table> arrivedProcess = new ArrayList<Table>();
    // private static int gant=0;

    // //Time quantum
    // private static int TimeQuantum=2;

    //index for moving through each process
    static int index=0;

    private static void solve(ArrayList<Table> process) {
        System.out.println("the process:"+process.get(0).pid);
        System.out.println("IN solve meth");
        
        int gant = 0; // Initialize gant (assuming it starts at 0)
        System.out.println("gant befor : "+gant);
        ArrayList<Table> arrivedProcess = new ArrayList<>();
    while (!process.isEmpty()) {
        
        
        // Check for processes that have arrived
        for (Table t : process) {
            if(gant == -1) {
                arrivedProcess.add(t);
                System.out.println("process arived:"+t.pid);
                break;
            }
             if (t.arrivalTime == gant && !arrivedProcess.contains(t)) {

                arrivedProcess.add(t);
                System.out.println("process arived:"+t.pid);
            }
        }

        if (arrivedProcess.isEmpty()) {
            gant++;
        } else {
            int TimeQuantum = 4;

            //adding this process at the back of the queue
            //first check if the arrivedProcess queue is empty or not
            
            if(!arrivedProcess.isEmpty()) {
                
                Table t = arrivedProcess.get(0);
                if( t.burstTime != 0) {
                    arrivedProcess.remove(t);
                    arrivedProcess.add(t);
                }
                else{
                    t.completionTime = gant;
                    completedProcess.add(t);
                    process.remove(t);
                    arrivedProcess.remove(t);
                }
            }

            if(arrivedProcess.isEmpty()) {
                
                continue;
            }

            //printing the arrrived process 
                System.out.print("===== Time Quantum for process " + arrivedProcess.get(arrivedProcess.size()-1).pid+" is overed XXXXX :: The QUEUE now is ::");
                for(Table ta: arrivedProcess) {
                    System.out.print(ta.pid+ " ");
                }
                System.out.print("=====");
                System.out.println();


            while (TimeQuantum > 0) {
                Table t = arrivedProcess.get(0);
                

                t.burstTime--;
                gant++;
                TimeQuantum--;
                 System.out.println(" AT GANT ::"+ gant +" process ::"+ t.pid +" with remaining burst ::"+t.burstTime);
                
                 for (Table ta : process) {
                        
                        if (ta.arrivalTime == gant && !arrivedProcess.contains(ta)) {

                            arrivedProcess.add(ta);
                            System.out.println("process arived:"+ta.pid);
                            System.out.print("=====arrived process QUEUE : ");
                            for(Table taa: arrivedProcess) {
                                System.out.print(taa.pid+ " ");
                            }
                            System.out.print("=====");
                            System.out.println();
                        }
                    }
                //printing the arrrived process 
                
                if (t.burstTime == 0) {
                    // t.completionTime = gant;
                    // completedProcess.add(t);
                    // process.remove(t);
                    // arrivedProcess.remove(t);
                    break;
                }
                    
               
                
            }
            
            
        }
    }

    // Calculate turnaround time, waiting time, response time, and print the table for completed processes
        Collections.sort(completedProcess, new Comparator<Table> () {

            @Override
            public int compare(Table o1, Table o2) {
                // TODO Auto-generated method stub
                return o1.arrivalTime - o2.arrivalTime;
            }
            
        });

        //adding the old burst time to the completed process table because it would be 0
        for(Table procs: completedProcess) {
            for(int i=0; i<bt.length; i++) {
              if(procs.pid == i+1) {
                procs.burstTime = bt[i];
                }
             }
        }
        
    //calculating all the other values
    for(Table procs: completedProcess){
        procs.turnAroundTime = procs.completionTime - procs.arrivalTime;

    }

    for(Table procs: completedProcess) {
        procs.waitingTime = procs.turnAroundTime - procs.burstTime;
    }

    for(Table procs: completedProcess) {
        procs.responseTime = procs.turnAroundTime - procs.burstTime;
    }

    //printing the table
    h = new Helper();
    System.out.println("PID\tAT\tBT\tCT\tTAT\tWT\tRT\tPR");
   
    for(Table table: completedProcess) {
        
        h.printTable(table);
    }

    double totalTurnaroundTime = 0;
double totalWaitingTime = 0;

for (Table procs : completedProcess) {
    totalTurnaroundTime += procs.turnAroundTime;
    totalWaitingTime += procs.waitingTime;
}

double avgTurnaroundTime = totalTurnaroundTime / completedProcess.size();
double avgWaitingTime = totalWaitingTime / completedProcess.size();

System.out.println("Average Turnaround Time: " + avgTurnaroundTime);
System.out.println("Average Waiting Time: " + avgWaitingTime);

    return;

    }
 }
