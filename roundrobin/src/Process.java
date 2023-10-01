public class Process {
   int id;
   int burstTime;
   double arrivalTime;
   int waitingTime;
   int returnTime;
   int originalBurstTime;

    public Process(int id, int burstTime, double arrivalTime, int waitingTime, int returnTime, int originalBurstTime) {
        this.id = id;
        this.burstTime = burstTime;
        this.arrivalTime = arrivalTime;
        this.waitingTime = waitingTime;
        this.returnTime = returnTime;
        this.originalBurstTime = originalBurstTime;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getBurstTime() {
        return burstTime;
    }

    public void setBurstTime(int burstTime) {
        this.burstTime = burstTime;
    }

    public double getArrivalTime() {
        return arrivalTime;
    }

    public void setArrivalTime(double arrivalTime) {
        this.arrivalTime = arrivalTime;
    }

    public int getWaitingTime() {
        return waitingTime;
    }

    public void setWaitingTime(int waitingTime) {
        this.waitingTime = waitingTime;
    }

    public int getReturnTime() {
        return returnTime;
    }

    public void setReturnTime(int returnTime) {
        this.returnTime = returnTime;
    }

    public int getOriginalBurstTime() {
        return originalBurstTime;
    }

    public void setOriginalBurstTime(int originalBurstTime) {
        this.originalBurstTime = originalBurstTime;
    }

    @Override
    public String toString() {
        return "Process - #" + getId();
    }
}
