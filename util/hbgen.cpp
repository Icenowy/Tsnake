#include <cstdio>

int main ()
{
	char c;

	int count = 0;

	std::printf ("extern \"C\" const char handbook_txt[]=\n\"");
	while ( (c = getchar()) != EOF) {
		std::printf ("\\x%x",c);
		count++;
		if (! (count % 10)) std::printf("\"\n\"");
	}
	std::printf("\";\n");
}
