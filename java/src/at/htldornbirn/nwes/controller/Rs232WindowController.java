package at.htldornbirn.nwes.controller;

import at.htldornbirn.nwes.model.MatrixModel;

import javax.swing.*;

public class Rs232WindowController extends AbstractWindowController {
	private Rs232Transmitter transmitter;
	private String chosenPort = null;

	@Override
	protected void beforeWindowCreationHook() {
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
	}

	@Override
	protected void afterWindowCreationHook() {
		transmitter = new Rs232Transmitter(chosenPort);
		try {
			transmitter.open();
		} catch(Exception ex) {
			showErrorMsgAndExit(ex.getStackTrace());
		}

		transmitToRs232();
	}

	@Override
	protected void modelChangedHook() {
		transmitToRs232();
	}

	private void transmitToRs232() {
		try {
			transmitter.transmit(model);
		} catch (Exception ex) {
			showErrorMsgAndExit(ex.getStackTrace());
		}
	}

	private void showErrorMsgAndExit(StackTraceElement[] stackTrace) {
		JOptionPane.showConfirmDialog(null, "Ein Fehler ist aufgetreten. Operation konnte nicht durchgeführt werden.");
		System.exit(-1);
	}

	@Override
	protected void onWindowCloseHook() {
		transmitter.close();
		System.exit(0);
	}
}
