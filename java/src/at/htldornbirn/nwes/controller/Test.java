package at.htldornbirn.nwes.controller;



public class Test {
	public static void main(String[] args) {
		if(args.length > 0 && args[0].equals("dryRun")) {
			new DryRunWindowController();
		} else {
			new Rs232WindowController();
		}
	}
}
