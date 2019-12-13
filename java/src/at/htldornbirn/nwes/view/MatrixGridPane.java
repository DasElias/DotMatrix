package at.htldornbirn.nwes.view;

import at.htldornbirn.nwes.model.MatrixModel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class MatrixGridPane extends JPanel {
	private static final int MATRIX_WIDTH = 8;
	private static final int MATRIX_HEIGHT = 8;


	private JButton[] ledButtons = new JButton[MATRIX_WIDTH * MATRIX_HEIGHT];
	private MatrixModel model;

	public MatrixGridPane(MatrixModel model) {
		this.model = model;
		GridLayout layout = new GridLayout(MATRIX_WIDTH, MATRIX_HEIGHT);
		this.setLayout(layout);

		JButton[] buttonsInGridPaneOrder = new JButton[MATRIX_WIDTH * MATRIX_HEIGHT];
		for(int x = 0; x < MATRIX_WIDTH; x++) {
			for(int y = 0; y < MATRIX_HEIGHT; y++) {
				int indexInGridPane = y * MATRIX_WIDTH + x;
				int indexInModel = x * MATRIX_HEIGHT + y;

				JButton button = new JButton();
				ledButtons[indexInModel] = button;

				button.addMouseListener(new GridPaneMouseListener(indexInModel));
				button.setText(indexInGridPane + "/" + indexInModel);

				buttonsInGridPaneOrder[indexInGridPane] = button;
			}
		}

		for(JButton b : buttonsInGridPaneOrder) {
			this.add(b);
		}


		/*for(int counter = 0; counter < ledButtons.length; counter++) {
			ledButtons[counter] = new JButton();
			ledButtons[counter].addMouseListener(new GridPaneMouseListener(counter));
			ledButtons[counter].setText(Integer.toString(counter));

			this.add(ledButtons[counter]);
		}*/

		rebuildMatrixColors();
		model.addListener((m) -> {
			rebuildMatrixColors();
		});

	}

	private void rebuildMatrixColors() {
		for(int counter = 0; counter < ledButtons.length; counter++) {
			JButton b = ledButtons[counter];

			if(model.get(counter) == true) {
				b.setBackground(Color.GREEN);
			} else {
				b.setBackground(Color.WHITE);
			}
		}
	}


	private class GridPaneMouseListener extends MouseAdapter {
		private int counter;

		public GridPaneMouseListener(int counter) {
			this.counter = counter;
		}

		@Override
		public void mouseClicked(MouseEvent e) {
			model.toggle(counter);
		}
	}
}
