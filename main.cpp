#include <iostream>
#include <fstream>
#include <bitset>
#include <string>

using namespace std;

string codificar_archivo_1(const string& texto, int n) {
     string encodedText;
     string binaryText;

    for (char character : texto) {
         bitset<8> binary(character);
        binaryText += binary.to_string();
    }

    for (int i = 0; i < binaryText.length(); i += n) {
         bitset<8> block;
        for (int j = 0; j < n; j++) {
            if (i + j < binaryText.length()) {
                block[j] = binaryText[i + j] == '0' ? 1 : 0;
            }
        }

        int countOnes = block.count(); // Contar unos en el bloque
        int countZeros = n - countOnes; // Calcular el número de ceros

        for (int j = 0; j < n; j++) {
            if (i == 0) {
                // Para el primer bloque, simplemente invierte cada bit
                encodedText += block[j] ? '1' : '0';
            } else {
                // Para bloques posteriores, aplica las reglas
                if (countOnes == countZeros) {
                    encodedText += !block[j] ? '1' : '0'; // Invertir cada bit si hay igual cantidad de unos y ceros
                } else if (countZeros > countOnes) {
                    if (j % 2 == 0) {
                        encodedText += !block[j] ? '1' : '0'; // Invertir cada 2 bits si hay más ceros
                    } else {
                        encodedText += block[j] ? '1' : '0';
                    }
                } else {
                    if (j % 3 == 0) {
                        encodedText += !block[j] ? '1' : '0'; // Invertir cada 3 bits si hay más unos
                    } else {
                        encodedText += block[j] ? '1' : '0';
                    }
                }
            }
        }
    }

    return encodedText;
}

 string decodificar_archivo_2(const  string& encodedText, int n) {
     string decodedText;
     string binaryText;

    for (int i = 0; i < encodedText.length(); i += n) {
         bitset<8> block;
        for (int j = 0; j < n; j++) {
            if (i + j < encodedText.length()) {
                block[j] = encodedText[i + j] == '0' ? 1 : 0;
            }
        }

        int countOnes = block.count(); // Contar unos en el bloque
        int countZeros = n - countOnes; // Calcular el número de ceros

        for (int j = 0; j < n; j++) {
            if (i == 0) {
                // Para el primer bloque, simplemente invierte cada bit
                binaryText += block[j] ? '1' : '0';
            } else {
                // Para bloques posteriores, aplica las reglas
                if (countOnes == countZeros) {
                    binaryText += !block[j] ? '1' : '0'; // Invertir cada bit si hay igual cantidad de unos y ceros
                } else if (countZeros > countOnes) {
                    if (j % 2 == 0) {
                        binaryText += !block[j] ? '1' : '0'; // Invertir cada 2 bits si hay más ceros
                    } else {
                        binaryText += block[j] ? '1' : '0';
                    }
                } else {
                    if (j % 3 == 0) {
                        binaryText += !block[j] ? '1' : '0'; // Invertir cada 3 bits si hay más unos
                    } else {
                        binaryText += block[j] ? '1' : '0';
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < binaryText.length(); i += 8) {
        string binaryByte = binaryText.substr(i, 8);
        bitset<8> bits(binaryByte);
        char character = char(bits.to_ulong());
        decodedText += character;
    }

    return decodedText;
}

string encodeMethod2(const string& text, int n) {
    string binaryText;
    string encodedText;

    for (char character : text) {
        bitset<8> binary(character);
        binaryText += binary.to_string();
    }

    for (int i = 0; i < binaryText.length(); i++) {
        int newIndex = (i + 1) % binaryText.length(); // Desplaza 1 posición hacia la derecha
        encodedText += binaryText[newIndex];
    }

    return encodedText;
}

string decodeMethod2(const string& encodedText, int n) {
    string binaryText;
    string decodedText;

    for (int i = 0; i < encodedText.length(); i++) {
        int originalIndex = (i - 1 + encodedText.length()) % encodedText.length(); // Desplaza 1 posición hacia la izquierda
        binaryText += encodedText[originalIndex];
    }

    for (size_t i = 0; i < binaryText.length(); i += 8) {
        string binaryByte = binaryText.substr(i, 8);
        bitset<8> bits(binaryByte);
        char character = char(bits.to_ulong());
        decodedText += character;
    }

    return decodedText;
}

int main() {
    int choice;
    cout << "Elije una opcion:\n";
            cout << "1. Codificar (Metodo 1).\n";
            cout << "2. Decodificar (Metodo 1).\n";
            cout << "3. Codificar (Metodo 2).\n";
            cout << "4. Decodificar (Metodo 2).\n";
            cin >> choice;

    if (choice < 1 || choice > 4) {
        cerr << "Opcion no valida. Debes elegir entre 1 y 4." << endl;
            return 1;
    }

    string inputFileName; // Nombre del archivo de entrada
    string outputFileName; // Nombre del archivo de salida
    int n;

    cout << "Ingresa el valor de n: ";
    cin >> n;

    cout << "Ingresa el nombre del archivo de entrada: ";
    cin >> inputFileName;
    cout << "Ingresa el nombre del archivo de salida (archivo .txt): ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error al abrir los archivos." << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    string result;

    if (choice == 1) {
        result = codificar_archivo_1(text, n);
    } else if (choice == 2) {
        result = decodificar_archivo_1(text, n);
    } else if (choice == 3) {
        result = encodeMethod2(text, n);
    } else {
        result = decodeMethod2(text, n);
    }

    outputFile << result;

    inputFile.close();
    outputFile.close();

    if (choice == 1) {
        cout << "Texto codificado y guardado en " << outputFileName << "." << endl;
    } else if (choice == 2) {
        cout << "Texto decodificado y guardado en " << outputFileName << "." << endl;
    } else if (choice == 3) {
        cout << "Texto codificado y guardado en " << outputFileName << "." << endl;
    } else {
        cout << "Texto decodificado y guardado en " << outputFileName << "." << endl;
    }

    return 0;
}
