#include "Secret.h"
using namespace std;

int main(void)
{
	string message = "";

	Secret secret_message_1 = Secret{ "encoded.ppm", 0 };
	Secret secret_message_2 = Secret{ "encoded1.ppm", 0 };

	cout << "First message: " << secret_message_1.getMessage() << endl;
	cout << "Second message: " << secret_message_2.getMessage() << endl << endl;

	cout << "Enter a message to encode: ";
	getline(cin, message);

	Secret message_to_hide = Secret{ "encoded1.ppm", 1 };
	message_to_hide.setMessage(message);
	Secret my_message = Secret{ "output.ppm", 0 };
	cout << "My secret message: " << my_message.getMessage();
}