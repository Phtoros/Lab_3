#include <UnitTest++/UnitTest++.h>
#include "/home/artem/Lab_1.1/Lab_2/modAlphaCipher.h"
#include "/home/artem/Lab_1.1/Lab_2/modAlphaCipher.cpp"

using namespace std;
SUITE(TestKey) // тесты для ключа
{

    TEST(Letters_Uppercase) {
        modAlphaCipher test(L"УЫПГУЫШАШГА");
        CHECK(true);
    }
    TEST(Letters_Uppercase_and_Written) {
        modAlphaCipher test(L"РЕНаоп");
        CHECK(true);
    }

    TEST(KeyEmpty) {
        CHECK_THROW(modAlphaCipher test(L""), cipher_error);
    }
    TEST(Space) {
        CHECK_THROW(modAlphaCipher test(L"н вксрк"), cipher_error);
    }
    TEST(Number) {
        CHECK_THROW(modAlphaCipher test(L"кпрвп1апыу"), cipher_error);
    }
    TEST(Invalid_Characters) {
        CHECK_THROW(modAlphaCipher test(L"МИР;"), cipher_error);
    }
}

struct KeyAB_fixture { // Для тестов шифрования и расшифрования
    modAlphaCipher * pointer;
    KeyAB_fixture()
    {
        pointer = new modAlphaCipher(L"АВ");
    }
    ~KeyAB_fixture()
    {
        delete pointer;
    }
};

SUITE(TestEncrypt) // Шифрование
{
    TEST_FIXTURE(KeyAB_fixture, Letters_Uppercase) {
        wstring open_text = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Small_Letters) {
        wstring open_text = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
        wstring result_correct = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        CHECK_EQUAL(true, result_correct == pointer->encrypt(open_text));
    }

    TEST_FIXTURE(KeyAB_fixture, Empty) {
        wstring open_text = L"";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture, Invalid_Numbers ) {
        wstring open_text = L"КУЕ43КУЕ";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture, Invalid_Characters ) {
        wstring open_text = L"КУЕ|КУЕ";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture, Space ) {
        wstring open_text = L"КУЕ КУЕ";
        CHECK_THROW(pointer->encrypt(open_text),cipher_error);
    }

}
SUITE(DecryptTest) // расшифрование
{
    TEST_FIXTURE(KeyAB_fixture, Letters_Uppercase) {
        wstring cipher_text = L"АГВЕДЖЁИЗКЙМЛОНРПТСФУЦХШЧЪЩЬЫЮЭАЯ";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Small_Letters) {
        wstring cipher_text = L"агведжёизкймлонрптсфуцхшчъщьыюэая";
        wstring result_correct = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }
    TEST_FIXTURE(KeyAB_fixture, Uppercase_and_Lowercase_Letters) {
        wstring cipher_text = L"ВСЕМпрИВЕТ";
        wstring result_correct = L"ВПЕКПОИАЕР";
        CHECK_EQUAL(true, result_correct == pointer->decrypt(cipher_text));
    }

    TEST_FIXTURE(KeyAB_fixture, Empty) {
        wstring cipher_text = L"";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,Invalid_Number ) {
        wstring cipher_text = L"КУЕ43КУЕ";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,Invalid_Character ) {
        wstring cipher_text = L"КУЕ*КУЕ";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
    TEST_FIXTURE(KeyAB_fixture,Space ) {
        wstring cipher_text = L"АПЫУП ФАПЦ";
        CHECK_THROW(pointer->decrypt(cipher_text),cipher_error);
    }
}
int main()
{
    return UnitTest::RunAllTests();
}
