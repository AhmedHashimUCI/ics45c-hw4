#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>

#include "string.hpp"

using namespace std;

TEST(StringClass, Constructors) {
    String s("hello");
    EXPECT_EQ(s.size(), 5);

    String t(s);
    EXPECT_EQ(t.size(), 5);
    EXPECT_EQ(s.size(), 5);
}

TEST(StringClass, Print) {
    String s("foo");
    stringstream out;
    s.print(out);
    EXPECT_STREQ(out.str().c_str(), "foo");

    stringstream out2;
    String().print(out2);
    EXPECT_STREQ(out2.str().c_str(), "");

    stringstream out3;
    out3 << s << s << String("bar");
    EXPECT_STREQ(out3.str().c_str(), "foofoobar");

	

}

TEST(StringClass, Comparisons) {
    EXPECT_LT(String("aaaa"), String("aaab"));
    EXPECT_LE(String("aaaa"), String("aaab"));
    EXPECT_EQ(String("foo"), String("foo"));
    EXPECT_NE(String("foo"), String("fooo"));
}




TEST(StringClass, Read) {
    istringstream input("LanaDelRey ArcticMonkeys");

    String first;
    String second;

    first.read(input);
    second.read(input);

    EXPECT_EQ(first, String("LanaDelRey"));
    EXPECT_EQ(second, String("ArcticMonkeys"));

    EXPECT_EQ(first.size(), 10);
    EXPECT_EQ(second.size(), 13);
}


TEST(StringClass, Index){

	EXPECT_EQ(String("Lana")[2], 'n');
	EXPECT_EQ(String("vow")[4], 'v');
	EXPECT_EQ(String(" time")[0], ' ');
	EXPECT_EQ(String("Time")[-2], 'T');
}



TEST(StringClass, indexofchar){

	EXPECT_EQ(String("Burn").indexOf('n'), 3);
	EXPECT_EQ(String("Arctic").indexOf('c'), 2);
	EXPECT_EQ(String("Time").indexOf('c'), -1);
	EXPECT_EQ(String("Lana Del Rey").indexOf(' '), 4);


}

TEST(StringClass, indexofstr){

	EXPECT_EQ(String("Who won?").indexOf(String("won?")), 4);
	EXPECT_EQ(String("Lana Del Rey").indexOf(String("Rey")),9 );


}


TEST(StringClass, Assignment) {
    String s("test"), t("foo");

    s = t;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = s;
    EXPECT_EQ(s.size(), t.size());
    EXPECT_EQ(s, t);

    s = String();
    EXPECT_EQ(s, String());
    EXPECT_EQ(s.size(), 0);
}

TEST(StringClass, Addition){

	EXPECT_EQ(String("Arctic") + String(" Monkeys"), String("Arctic Monkeys"));
	EXPECT_EQ(String(" ") + String("String"), String(" String"));
	EXPECT_EQ(String("String")+ String(""), String("String"));
	String s("Time");
	String e("");
	EXPECT_EQ(s += s,String("TimeTime"));
	EXPECT_EQ(s += e, s);
	EXPECT_EQ(e += s, s);
	EXPECT_EQ(e += e, e);
}


TEST(StringClass, Memory) {
    String a("Lana");
    String b(a);

    b[0] = 'B';

    EXPECT_EQ(a, String("Lana"));
    EXPECT_EQ(b, String("Bana"));

    a = b;
    EXPECT_EQ(a, b);

    a += String(" Del Rey");
    EXPECT_EQ(a, String("Bana Del Rey"));
}
