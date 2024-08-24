#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
#include <windows.h>
#include <compressapi.h>
static char* charToHex(unsigned char c) {
    char* s = (char*)malloc(3);
    if (s == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf_s(s, 3, "%02x", c);
    return s;
}

static void dump(unsigned char* buffer, size_t BYTES_PER_LINE, size_t SIZE, DWORD64 startAddress) {
    size_t byteIndex = 0;
    size_t NUMBER_OF_LINES = (SIZE + BYTES_PER_LINE - 1) / BYTES_PER_LINE; // Ensure all bytes are processed
    char* text = (char*)malloc(BYTES_PER_LINE * 6 + 18); // Allocate once for the entire line
    if (text == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < NUMBER_OF_LINES; i++) {
        sprintf_s(text, BYTES_PER_LINE * 6 + 18, "\n%16llx ", BYTES_PER_LINE * i + startAddress);
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (byteIndex < SIZE) {
                char* ch = charToHex(buffer[byteIndex++]);
                sprintf_s(text + strlen(text), BYTES_PER_LINE * 6 + 18 - strlen(text), "%s ", ch);
                free(ch);
            }
            else {
                sprintf_s(text + strlen(text), BYTES_PER_LINE * 6 + 18 - strlen(text), "   "); // Fill in the gap for incomplete lines
            }
        }

        sprintf_s(text + strlen(text), BYTES_PER_LINE * 6 + 18 - strlen(text), " ");
        for (size_t j = 0; j < BYTES_PER_LINE; j++) {
            if (i * BYTES_PER_LINE + j < SIZE) {
                unsigned char c = buffer[i * BYTES_PER_LINE + j];
                sprintf_s(text + strlen(text), BYTES_PER_LINE * 6 + 18 - strlen(text), "%c", isprint(c) ? c : '.');
            }
            else {
                sprintf_s(text + strlen(text), BYTES_PER_LINE * 6 + 18 - strlen(text), " ");
            }
        }
        fwrite(text, strlen(text), 1, stdout);
    }
    free(text);
    putchar('\n');
}
int main()
{
#pragma comment(lib, "Cabinet.lib")
    COMPRESSOR_HANDLE handle=0;
    cout << "data: ";
    string data;
    getline(cin, data);
    cout << "one of [\"MSZIP\",\"XPRESS\",\"XPRESS+Huffman\",\"LZMS\",\"Maximum\",\"RAW\"]" << endl;
    DWORD alg = 0;
    string type;
    cin >> type;
    if (type == "MSZIP") alg = COMPRESS_ALGORITHM_MSZIP;
    else if (type == "XPRESS") alg = COMPRESS_ALGORITHM_XPRESS;
    else if (type == "XPRESS+Huffman") alg = COMPRESS_ALGORITHM_XPRESS_HUFF;
    else if (type == "LZMS") alg = COMPRESS_ALGORITHM_LZMS;
    else if (type == "Maximum") alg = COMPRESS_ALGORITHM_MAX;
    else if (type == "RAW") alg = COMPRESS_RAW;
    else return ERROR_INVALID_PARAMETER;
    CreateCompressor(alg, NULL, &handle);
    LPVOID buffer = malloc(1);
    size_t size=0;
    Compress(handle, data.c_str(), data.size() + 1, buffer, 0, &size);
    buffer = malloc(size);
    Compress(handle, data.c_str(), data.size() + 1, buffer, size, &size);
    cout << "original" << endl;
    dump((BYTE*)data.c_str(), 16, data.size() + 1, (DWORD64)data.c_str());
    cout << "compressed" << endl;
    dump((BYTE*)buffer, 16, size, (DWORD64)buffer);
    CloseCompressor(handle);
    cout << "Difference: +\\-" << max(size,data.size())-min(size,data.size());
    return 0;
}
