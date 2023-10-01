import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

public class Main {
    public static void main(String[] args) {
        List<Process> processList = new LinkedList<>();
        List<Process> finishedProcessList = new LinkedList<>();
        int n = 5;
        long seed = 12345;
        Random rand = new Random(seed);

        for (int i = 1; i <= n; i++) {
            int originalBurstTime = rand.nextInt(30) + 1;
            processList.add(new Process(i, originalBurstTime, rand.nextDouble() * 5 + 1, 0, 0, originalBurstTime));
        }

        Collections.sort(processList, Comparator.comparingDouble(x -> x.getArrivalTime()));

        for (Process p :
                processList) {
            System.out.println(p + " Arrival Time: " + p.getArrivalTime() +" BT: " + p.getBurstTime() + " Waiting time: " + p.getWaitingTime());
        }

        for (int i = 1; i <= 4; i++) {
            List<Process> currentProcessList = new LinkedList<>(processList);
            int time = 0;
            int totalWaitingTime = 0;
            int totalReturnTime = 0;
            int quantum = rand.nextInt(15) + 5;
            System.out.println("Iteration " + i + ": Quantum : " + quantum);

            for (Process p : currentProcessList) {
                p.setWaitingTime(0);
                p.setBurstTime(p.getOriginalBurstTime());
            }

            while (!currentProcessList.isEmpty()) {
                Process p = currentProcessList.remove(0);
                if (p.getBurstTime() > quantum) {
                    time += quantum;
                    p.setBurstTime(p.getBurstTime() - quantum);
                    currentProcessList.forEach(x -> x.setWaitingTime(x.getWaitingTime() + quantum));
                    System.out.println("Time " + time + ": Executing Process " + p.getId() + ", Burst Time Remaining: " + p.getBurstTime() + " Waiting time: " + p.getWaitingTime());
                    currentProcessList.add(p);
                } else {
                    time += p.getBurstTime();
                    currentProcessList.forEach(x -> x.setWaitingTime(x.getWaitingTime() + p.getBurstTime()));
                    p.setReturnTime(p.getBurstTime() + p.getWaitingTime());
                    finishedProcessList.add(p);
                    System.out.println("Process " + p.getId() + " completed. Total time: " + time);
                }
                if (!currentProcessList.isEmpty()) {
                    time += 1;
                }
            }

            for (Process p : finishedProcessList) {
                totalWaitingTime += p.getWaitingTime();
                totalReturnTime += p.getReturnTime();
            }

            System.out.printf("Throughput: %.4f\n", (double) n / (time));
            System.out.println("Average waiting time: " + totalWaitingTime);
            System.out.println("Average return time: " + totalReturnTime);

            finishedProcessList.clear();
        }
    }
}
