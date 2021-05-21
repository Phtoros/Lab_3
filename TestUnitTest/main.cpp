#include <UnitTest++/UnitTest++.h>
#include "/home/artem/Lab_1.1/Lab21/PermutationCipher.h"
#include "/home/artem/Lab_1.1/Lab21/PermutationCipher.cpp"

using namespace std;

string t (int k, wstring tt1)
{
    PermutationCipher w(k);
    wstring ws=w.CoderPermutationCipher(w,tt1);
    const string y1(ws.begin(), ws.end());
    return y1;
}

string t1 (int k, wstring tt1)
{
    PermutationCipher w(k);
    wstring ws=w.DecoderPermutationCipher(k, tt1);
    const string y1 (ws.begin(), ws.end() );
    return y1;
}

char k;
wstring test = L"PROCESSING";
SUITE (KeyTest)
{
    TEST (ValidKey) {
        CHECK_EQUAL(t(k=5,test),"PSRSOICNEG");
    }

    TEST(Empty_key) {
        CHECK_THROW(t(k=0,test), cipher_error);
    }
    TEST(the_key_is_less_than_zero) {
        CHECK_THROW(t(k=-2,test), cipher_error);
    }
    TEST(the_key_is_larger_than_the_string) {
        CHECK_THROW(t(k=10,test), cipher_error);
    }

}


SUITE (Encrypt)
{

    TEST (ValidKey) {
        CHECK_EQUAL(t(k=5,test),"PSRSOICNEG");
    }
    TEST (SPACE) {
        CHECK_EQUAL(t(k=5,L"PROCES SING"),"PSRSOICNEG");
    }
    TEST (Low_characters) {
        CHECK_EQUAL(t(k=5,L"processing"),"PSRSOICNEG");
    }
    TEST (Numbers) {
        CHECK_THROW(t(k=5,L"12345"),cipher_error);
    }
    TEST (Empty) {
        CHECK_THROW(t(k=5,L" "),cipher_error);
    }
    TEST (letters_and_numbers) {
        CHECK_THROW(t(k=5,L"123awfawAWF45"),cipher_error);
    }
}

SUITE(DecryptText)
{
    TEST(ValidTEXT) {
        CHECK_EQUAL(t1(5,L"PSRSOICNEG"),"PROCESSING");
    }
    TEST(Low_characters) {
        CHECK_EQUAL(t1(5,L"psrsoicneg"),"PROCESSING");
    }
    TEST(SPACE) {
        CHECK_EQUAL(t1(5,L"PSRSO ICNEG"),"PROCESSING");
    }
    TEST(Empty) {
        CHECK_THROW(t1(5,L" "),cipher_error);
    }
    TEST (Numbers) {
        CHECK_THROW(t1(k=5,L"12345"),cipher_error);
    }
    TEST (letters_and_numbers) {
        CHECK_THROW(t1(k=5,L"123awfawAWF45"),cipher_error);
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
