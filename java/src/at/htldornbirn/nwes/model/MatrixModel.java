package at.htldornbirn.nwes.model;

import java.util.ArrayList;

public class MatrixModel {
	private byte[] data = new byte[8];
	private ArrayList<MatrixModelListener> listeners = new ArrayList<>();

	public byte[] get() {
		return data;
	}

	public boolean get(int index) {
		int indexInArray = index / 8;
		int indexInByte = 7 - (index % 8);

		int b = data[indexInArray] & (1 << indexInByte);
		return b != 0;
	}

	public void set(int index) {
		int indexInArray = index / 8;
		int indexInByte = 7 - (index % 8);

		data[indexInArray] |= (1 << indexInByte);
		fireListeners();
	}

	public void clear(int index) {
		int indexInArray = index / 8;
		int indexInByte = 7 - (index % 8);

		data[indexInArray] &= ~(1 << indexInByte);
		fireListeners();
	}

	public void toggle(int index) {
		if(get(index)) clear(index);
		else set(index);
	}

	public void addListener(MatrixModelListener l) {
		this.listeners.add(l);
	}

	private void fireListeners() {
		for(MatrixModelListener l : listeners) {
			l.fire(this);
		}
	}
}