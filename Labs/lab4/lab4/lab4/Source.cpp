#include "Secret.h"
using namespace std;

int main(void)
{
	Secret secret_message = Secret{ "encoded.ppm", 0 };

	//cout << secret_message.getMessage();

	Secret message_to_hide = Secret{ "encoded1.ppm", 1 };
	message_to_hide.setMessage("secret message");
}