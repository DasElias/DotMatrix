package at.htldornbirn.nwes.controller;

import at.htldornbirn.nwes.model.MatrixModel;
import at.htldornbirn.nwes.view.MatrixGridPane;

import javax.swing.*;
import java.awt.event.WindowEvent;
import java.util.Arrays;

public class WindowController {
	private JFrame frame;
	private MatrixGridPane gridPane;
	private MatrixModel model;
	private Rs232Transmitter transmitter;

	public WindowController() {
		String chosenPort = null;

		do {
			Object[] ports = Rs232Transmitter.getAvailablePorts();

			if(ports.length == 0) {
				Object[] retryOptions = {"Wiederholen", "Abbrechen"};
				int chosen = JOptionPane.showOptionDialog(null,
						"Kein Port verfügbar.",
						"DotMatrix",
						JOptionPane.DEFAULT_OPTION,
						JOptionPane.WARNING_MESSAGE,
						null,
						retryOptions,
						retryOptions[0]
				);

				if(chosen == 0) continue;
				else System.exit(0);
			}

			int chosenPortIndex = JOptionPane.showOptionDialog(null,
					"Bitte wählen Sie den Port, an dem der Mikrocontroller angeschlossen ist.",
					"DotMatrix",
					JOptionPane.DEFAULT_OPTION,
					JOptionPane.INFORMATION_MESSAGE,
					null,
					ports,
					ports[0]
			);

			if(chosenPortIndex < 0 || chosenPortIndex >= ports.length) System.exit(0);
			else chosenPort = (String) ports[chosenPortIndex];
		} while(chosenPort == null);


		frame = new JFrame();
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent winEvt) {
				transmitter.close();
				System.exit(0);
			}
		});
		model = new MatrixModel();
		gridPane = new MatrixGridPane(model);
		frame.getContentPane().add(gridPane);



		transmitter = new Rs232Transmitter("COM4");
		try {
			transmitter.open();
		} catch(Exception e) {
			e.printStackTrace();
			System.exit(-1);
		}
		model.addListener(model -> {
			transmitToRs232();
			System.out.println(Arrays.toString(model.get()));
		});

		transmitToRs232();
		frame.setTitle("DotMatrix-Steuerung");
		frame.setSize(500, 500);
		frame.setVisible(true);
	}

	private void transmitToRs232() {
		try {
			transmitter.transmit(model);
		} catch (Exception ex) {
			ex.printStackTrace();
			System.exit(-1);
		}
	}
}
