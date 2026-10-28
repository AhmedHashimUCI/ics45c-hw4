#include "string.hpp"
#include <iosfwd>
#include <iostream>

constexpr int MAXLEN = 128;
String::String(const char *s){

	if(s == nullptr){
		s = "";
	}
	buf = strdup(s);

}



String::String(const String &s){
	buf = strdup(s.buf);

}


String::String(int length) {
    buf = new char[length + 1];
}


void String::swap(String &s){
	std::swap(buf, s.buf);

}

String &String::operator=(String s){

	swap(s);

	return *this;
}



char &String::operator[](int index){

	if(in_bounds(index)){

		return buf[index];
	}else {
	std::cerr << "ERROR: Index Out Of Bounds" << std::endl;
	return buf[0];

	}
}


const char &String::operator[](int index) const{

	if(in_bounds(index)){

		return buf[index];
	}else {

	std::cerr << "ERROR: Index Out Of Bounds" << std::endl;
	return buf[0];

	}



}

int String::size() const{
	
	return strlen(buf);

}







void String::print(std::ostream & out) const{
	
	out << buf;

}

void String::read(std::istream &in){
	int index = 0;
	char c;
	in >> std::ws;

	for (int i =0; in.get(c); ++i){
	
	 if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f') {
        in.unget();
        break;
    }

	if (i < MAXLEN -1){
	
		buf[index++] = c;

	}

}

buf[index] = '\0';

}

String String::reverse() const{
	String result;
	reverse_cpy(result.buf, buf);
	return result;
}


int String::indexOf(char c) const{


	const char *cha = strchr(buf, c);
	if (cha != nullptr){
		return cha - buf;
	}else{
	std:: cerr << "Error: Character is not found or out of bound" << std::endl;
	return -1;
		}
	}
		
int String::indexOf(String s) const{

	const char *cha = strstr(buf, s.buf);

	if (cha != nullptr){
		return cha - buf;
	}else{
	std::cerr << "Error, Index out of bound" << std::endl;
	return -1;
	}
}		
	

String &String::operator +=(String s){

	
	const int first = size();
	const int incoming = s.size();

	if (incoming > (MAXLEN - 1) - first)
        std::cerr << "ERROR: String Capacity Exceeded" << std::endl;
    strncat(buf, s.buf, (MAXLEN - 1) - first);
    return *this;

}


String String::operator+(String s) const{
	String orignal(*this);
	orignal += s;
	return orignal;
}


bool String::operator ==(String s) const{

	return strcmp(buf, s.buf) == 0;

}

bool String::operator !=(String s) const{

	return strcmp(buf, s.buf) != 0;
}

bool String::operator >(String s) const {

	return strcmp(buf, s.buf) > 0;
}

bool String::operator <(String s) const{

	return strcmp(buf, s.buf) < 0;

}

bool String::operator <=(String s) const{

	return strcmp(buf, s.buf) <= 0;
}

bool String::operator >=(String s) const{

	return strcmp(buf, s.buf) >= 0;
}



String::~String(){
	
	delete[] buf;
	buf = nullptr;

}


//HELPERS


char *String::strdup(const char *s){
	int len = strlen(s);
	char *str = new char[len +1];

	strcpy(str, s);

	return str;


}


int String::strlen(const char *s){
	
	int len = 0;
	for(int i = 0; s[i] != '\0'; ++i){
		++len;
	}

	return len;
}


char * String::strcpy(char *dest, const char *src){
	
	int l = 0;
	for(int i = 0; src[i] != '\0'; ++i){
		
		dest[i] = src[i];
		++l;
	}
	dest[l] = '\0';
	return dest;

}

char * String::strncpy(char * dest, const char* src, int n){
	int i = 0;
	for(;i<n && src[i] !='\0'; ++i ){
		dest[i] = src[i];
	}

	dest[i] = '\0';
	return dest;

}

char * String::strcat(char * dest,const char* src){

	strcpy(dest + strlen(dest), src);
	return dest;

}

char * String::strncat(char *dest, const char * src, int n){

	strncpy(dest + strlen(dest), src, n);
	return dest;

}

int String::strcmp(const char *left, const char * right){
	int num = 0;
	for (int i = 0; left[i] != '\0' && left[i] == right[i]; ++i){
		++num;
	}
	int boolean = left[num] - right[num];
	return boolean;
}

int String::strncmp(const char *left, const char * right, int n){
	
	for (int i = 0; i < n; ++i) {
        if (left[i] != right[i]) {
            return left[i] - right[i];
        }
        if (left[i] == '\0') {
            return 0;
        }
    }
    return 0;
}


void String::reverse_cpy(char * dest, const char *src){

	int len = strlen(src) -1;
    for (int i = 0; i <= len; ++i){
	dest[i] = src[len-i];
	}

    dest[len+1] = '\0';

}

const char * String::strchr(const char *str, char c){
	
	  if (c == '\0') {
        return nullptr;
    }

	for (int i = 0; str[i] != '\0'; ++i){

		if (str[i] == c){
			return &str[i];

		}

	}
	return nullptr;
}


const char* String::strstr(const char *haystack, const char *needle){

	for(int i =0; haystack[i] != '\0'; ++i){
		if (strncmp(&haystack[i], needle, strlen(needle)) ==0){
			return &haystack[i];
		}
	
	}
	return nullptr;

}

std::ostream &operator<<(std::ostream &out, String s){

	s.print(out);
	return out;

}

std::istream &operator>>(std::istream &in, String &s){
	s.read(in);
	return in;

}
