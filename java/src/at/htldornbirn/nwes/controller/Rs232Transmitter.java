package at.htldornbirn.nwes.controller;

import at.htldornbirn.nwes.model.MatrixModel;
import com.fazecast.jSerialComm.SerialPort;

public class Rs232Transmitter {
	private SerialPort port;

	public Rs232Transmitter(String port) {
		this.port = SerialPort.getCommPort("COM4");
	}

	public void open() {
		if(! port.openPort()) System.err.println("Port couldn't be opened.");

		port.setBaudRate(115200);
		port.setNumDataBits(8);
		port.setNumStopBits(1);
		port.setParity(0);
	}

	public void close() {
		port.closePort();
	}

	public void transmit(MatrixModel model) {
		int a = port.writeBytes(model.get(), model.get().length);
		System.out.println("Transmittted");
		//port.writeBytes(model.get());
	}
}
