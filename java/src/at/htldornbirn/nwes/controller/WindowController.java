package at.htldornbirn.nwes.controller;

import at.htldornbirn.nwes.model.MatrixModel;
import at.htldornbirn.nwes.view.MatrixGridPane;

import javax.swing.*;
import java.awt.event.WindowEvent;

public class WindowController {
	private JFrame frame;
	private MatrixGridPane gridPane;
	private MatrixModel model;
	private Rs232Transmitter transmitter;

	public WindowController() {
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
			try {
				transmitter.transmit(model);
			} catch (Exception ex) {
				ex.printStackTrace();
				System.exit(-1);
			}
		});

		frame.setVisible(true);
	}
}
