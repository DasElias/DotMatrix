package at.htldornbirn.nwes.controller;


import com.fazecast.jSerialComm.SerialPort;

import java.util.Scanner;

public class Test {
	public static void main(String[] args) {
		if(true) {
			new WindowController();
		} else {
			Scanner s = new Scanner(System.in);
			SerialPort port = SerialPort.getCommPort("COM4");
			if(! port.openPort()) {
				System.err.println("Port couldn't be opened.");
				System.exit(-1);
			}

			port.setBaudRate(115200);
			port.setNumDataBits(8);
			port.setNumStopBits(1);
			port.setParity(0);
			while(s.hasNextLine()) {
				String ch = s.nextLine();

				if(ch.equals("transmit")) {
					byte[] b = new byte[] {0x00, (byte) 0x7F, (byte) 0x88, (byte) 0x88, (byte) 0x88, (byte) 0x88, (byte) 0xFB, 0x00};
					int a = port.writeBytes(b, b.length);
					System.out.println("Transmission finished");
				} else if (ch.equals("exit")) {
					break;
				}

			}
			port.closePort();
		}
	}
}
