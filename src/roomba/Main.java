package roomba;
import roombacomm.*;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        RoombaComm roomba = new RoombaCommSerial();
        boolean 
        while()
        System.out.print("Puerto: ");
        String port = sc.next();
        roomba.connect(port);
    }

}
