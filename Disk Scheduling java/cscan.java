import java.util.*;

class cscan8{

	static int disk_size;

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the number of requests: ");
		int size = sc.nextInt();
		int[] arr = new int[size];
		System.out.println("Enter the requests:");
		for (int i = 0; i < size; i++) {
			arr[i] = sc.nextInt();
		}

		System.out.print("Enter the initial head position: ");
		int head = sc.nextInt();

		System.out.print("Enter the disk size: ");
		disk_size = sc.nextInt();

		System.out.print("Enter the direction of head movement (left or right): ");
		String direction = sc.next();
		sc.close();

		System.out.println("Initial position of head: " + head);

		CSCAN(arr, head, direction);
	}

	public static void CSCAN(int arr[], int head, String direction) {
		int seek_count = 0;
		int distance, cur_track;
		Vector<Integer> left = new Vector<Integer>();
		Vector<Integer> right = new Vector<Integer>();
		Vector<Integer> seek_sequence = new Vector<Integer>();

		left.add(0);
		right.add(disk_size - 1);

		for (int i = 0; i < arr.length; i++) {
			if (arr[i] < head)
				left.add(arr[i]);
			if (arr[i] > head)
				right.add(arr[i]);
		}

		Collections.sort(left);
		Collections.sort(right);

		if (direction.equals("right")) {
			for (int i = 0; i < right.size(); i++) {
				cur_track = right.get(i);
				seek_sequence.add(cur_track);
				distance = Math.abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}

			head = 0;
			seek_count += (disk_size - 1);

			for (int i = 0; i < left.size(); i++) {
				cur_track = left.get(i);
				seek_sequence.add(cur_track);
				distance = Math.abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}
		} else if (direction.equals("left")) {
			for (int i = 0; i < left.size(); i++) {
				cur_track = left.get(i);
				seek_sequence.add(cur_track);
				distance = Math.abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}

			head = disk_size - 1;
			seek_count += (disk_size - 1);

			for (int i = 0; i < right.size(); i++) {
				cur_track = right.get(i);
				seek_sequence.add(cur_track);
				distance = Math.abs(cur_track - head);
				seek_count += distance;
				head = cur_track;
			}
		} else {
			System.out.println("Invalid direction! Please specify either 'left' or 'right'.");
			return;
		}

		System.out.println("Total number of seek operations = " + seek_count);

		System.out.println("Seek Sequence is");

		for (int i = 0; i < seek_sequence.size(); i++) {
			System.out.print(seek_sequence.get(i));
			if (i != seek_sequence.size() - 1) {
				System.out.print(" -> ");
			}
		}
	}
}
