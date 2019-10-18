package roomba;
import roombacomm.*;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        RoombaComm roomba = new RoombaCommSerial();
        boolean connected = false;
        String[] ports = roomba.listPorts();
        do {
            System.out.println("Puertos:");
            for (int i = 0; i < ports.length; i++) {
                System.out.println((i + 1) + " - " + ports[i]);
            }
            System.out.print("> ");
            int port = sc.nextInt();
            connected = roomba.connect(ports[port - 1]);
            if (!connected) {
                System.out.println("Puerto inválido.");
            }
        } while(!connected);
        roomba.startup();
        roomba.goForward();
        Thread.sleep(1000);
        roomba.stop();
        roomba.disconnect();
    }

}
