package at.htldornbirn.nwes.controller;

import java.util.Arrays;

public class DryRunWindowController extends AbstractWindowController {

	@Override
	protected void beforeWindowCreationHook() {
		// empty method body
	}

	@Override
	protected void afterWindowCreationHook() {
		// empty method body
	}

	@Override
	protected void modelChangedHook() {
		System.out.print("[");
		for(byte b : model.get()) {
			System.out.print(String.format("0x%02X", b));
			System.out.print(", ");
		}
		System.out.print("]" + System.lineSeparator());
	}

	@Override
	protected void onWindowCloseHook() {
		// empty method body
	}
}
