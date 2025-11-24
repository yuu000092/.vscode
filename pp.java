public class pp{

public static class Message {
	private String message;

	public void setMessage(String message) {
		this.message = message;
	}

	public void print() {
		System.out.println(message);
	}
}

public static void main(String[] args) {
		String value = "Hello Java";
		Message message = new Message();
		message.setMessage(value);
		message.print();
    }
}
