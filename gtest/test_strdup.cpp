#include <iostream>
using namespace std;


int strlen(const char *s){
	
	int len = 0;
	for(int i = 0; s[i] != '\0'; ++i){
		++len;
	}

	return len;
}


char * strcpy(char *dest, const char *src){
	
	int l = 0;
	for(int i = 0; src[i] != '\0'; ++i){
		
		dest[i] = src[i];
		++l;
	}
	dest[l] = '\0';
	return dest;

}

char *strdup(const char *s) {
    int len = strlen(s);
    char *str = new char[len + 1];
    strcpy(str, s);
    return str;
}

int main() {
    char *result = strdup("Lana Del Rey");

    cout << result << endl;
    cout << strlen(result) << endl;

    delete[] result;
}
