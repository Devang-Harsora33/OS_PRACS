class busTicketSystem {
    private int seatsLeft;

    public busTicketSystem(int seatsLeft) {
        this.seatsLeft = seatsLeft;
    }

    public synchronized void bookSeat() throws InterruptedException {
        if (seatsLeft > 0) {
            Thread.sleep(1000);
            seatsLeft--;
            System.out.println("Seat booked. Remaining seats: " + seatsLeft);
        } else {
            System.out.println("No seats available.");
        }
    }
}

class UserThread extends Thread {
    private busTicketSystem reservationSystem;

    public UserThread(busTicketSystem reservationSystem, String name) {
        super(name);
        this.reservationSystem = reservationSystem;
    }

    public void run() {
        try {
            reservationSystem.bookSeat();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class osprac1 {
    public static void main(String[] args) {
        busTicketSystem reservationSystem = new busTicketSystem(2);

        UserThread user1 = new UserThread(reservationSystem, "User 1");
        UserThread user2 = new UserThread(reservationSystem, "User 2");
        UserThread user3 = new UserThread(reservationSystem, "User 3");

        user1.start();
        user2.start();
        user3.start();
    }
}