#include "string.hpp"
#include <iosfwd>
#include <iostream>

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

String::String(String &&s){

	buf = s.buf;
	s.buf = nullptr;

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
	in >> std::ws;

	int maxima= 16;
	int len = 0;
	char *temp = new char[maxima];

	char c;

	for (int i =0; in.get(c); ++i){
	
	 if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f') {
        in.unget();
        break;
    }


	if (len + 1 >= maxima){
		int newmaxima = maxima * 2;
		char *templarge = new char[newmaxima];

		for (int i = 0; i < len; ++i){

			templarge[i] = temp[i];

		}

			delete[] temp;
			temp = templarge;
			maxima = newmaxima;

		}

		temp[len++] = c;
		
	}

	temp[len] = '\0';
	char *newbuf = strdup(temp);

	delete[] temp;
	delete[] buf;

	buf = newbuf;


}

String String::reverse() const{
	String result(size());
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
		
int String::indexOf(const String &s) const{

	const char *cha = strstr(buf, s.buf);

	if (cha != nullptr){
		return cha - buf;
	}else{
	std::cerr << "Error, Index out of bound" << std::endl;
	return -1;
	}
}		
	

String &String::operator +=(const String &s){

	
	int addedlen = size() + s.size();
	char *newBuf = new char[addedlen+1];

	strcpy(newBuf, buf);
	strcat(newBuf, s.buf);

	delete[] buf;
	buf = newBuf;
	

    return *this;

}


String String::operator+(const String &s) const{
	int len = size() + s.size();

	String newstr(len);

	strcpy(newstr.buf, buf);
	strcat(newstr.buf, s.buf);

	return newstr;
}


bool String::operator ==(const String &s) const{

	return strcmp(buf, s.buf) == 0;

}

bool String::operator !=(const String &s) const{

	return strcmp(buf, s.buf) != 0;
}

bool String::operator >(const String &s) const {

	return strcmp(buf, s.buf) > 0;
}

bool String::operator <(const String &s) const{

	return strcmp(buf, s.buf) < 0;

}

bool String::operator <=(const String &s) const{

	return strcmp(buf, s.buf) <= 0;
}

bool String::operator >=(const String &s) const{

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


	for (int i = 0; ; ++i){

		if (str[i] == c){
			return &str[i];
		}

		if (str[i] == '\0') {
            return nullptr;
        }

	}
	return nullptr;
}


const char* String::strstr(const char *haystack, const char *needle){
	if (needle[0] == '\0') {
        return haystack;
    }


	for(int i =0; haystack[i] != '\0'; ++i){
		if (strncmp(&haystack[i], needle, strlen(needle)) ==0){
			return &haystack[i];
		}
	
	}
	return nullptr;

}

std::ostream &operator<<(std::ostream &out, const String &s){

	s.print(out);
	return out;

}

std::istream &operator>>(std::istream &in, String &s){
	s.read(in);
	return in;

}
