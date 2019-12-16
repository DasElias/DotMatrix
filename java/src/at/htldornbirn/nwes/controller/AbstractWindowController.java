package at.htldornbirn.nwes.controller;

import at.htldornbirn.nwes.model.MatrixModel;
import at.htldornbirn.nwes.view.MatrixGridPane;

import javax.swing.*;
import java.awt.event.WindowEvent;
import java.util.Arrays;

public abstract class AbstractWindowController {
	private JFrame frame;
	private MatrixGridPane gridPane;
	protected MatrixModel model;

	public AbstractWindowController() {
		this.beforeWindowCreationHook();

		frame = new JFrame();
		frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
		frame.addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent winEvt) {
				AbstractWindowController.this.onWindowCloseHook();
			}
		});
		model = new MatrixModel();
		model.addListener(model -> {
			modelChangedHook();
		});
		gridPane = new MatrixGridPane(model);
		frame.getContentPane().add(gridPane);


		this.afterWindowCreationHook();

		frame.setTitle("DotMatrix-Steuerung");
		frame.setSize(500, 500);
		frame.setVisible(true);
	}

	protected abstract void modelChangedHook();
	protected abstract void beforeWindowCreationHook();
	protected abstract void afterWindowCreationHook();
	protected abstract void onWindowCloseHook();

}
