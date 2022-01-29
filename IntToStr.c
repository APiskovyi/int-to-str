#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* IntToText(int _Num);

int main() {
  setlocale(LC_ALL, "Russian");

  int num;
  while (1) {
    scanf_s("%d", &num);
    printf_s("%s\n", IntToText(num));
  }
}

/**
 * @brief Algorythm is similar to string builder.
 * Every representation of numbers collects in string array "wordList",
 * then it assemble in "result".
 * @param _Num number
 * @return string representation of a number in ukrainian.
 */
char* IntToText(int _Num) {
  // Getting string representation of number.
  const int strNumLen = (int)(log10(_Num) + 1);
  const char* strNum = (char*)calloc(strNumLen + 1, sizeof(char));
  if (strNum == NULL) {
    return NULL;
  }
  sprintf_s(strNum, (strNumLen + 1) * sizeof(char), "%d", _Num);

  // To text converting.
  int wordAmount = 0;
  char** wordList = (char**)calloc(14, sizeof(char**));
  if (wordList == NULL) {
    return NULL;
  }

  int digitCounter = 1;
  int thousandCounter = 1;

  for (int i = strNumLen - 1; i >= 0; i--) {
    if (digitCounter == 1) {
      if (i - 1 >= 0 && strNum[i - 1] == '1') {  // Units & tens (10-19).
        digitCounter++;                          // To remove next tens check.
        if (strNum[i] == '0') {
          wordList[wordAmount] = "десять";
        } else if (strNum[i] == '1') {
          wordList[wordAmount] = "одинадцять";
        } else if (strNum[i] == '2') {
          wordList[wordAmount] = "дванадцять";
        } else if (strNum[i] == '3') {
          wordList[wordAmount] = "тринадцять";
        } else if (strNum[i] == '4') {
          wordList[wordAmount] = "чотирнадцять";
        } else if (strNum[i] == '5') {
          wordList[wordAmount] = "петнадцять";
        } else if (strNum[i] == '6') {
          wordList[wordAmount] = "шiстнадцять";
        } else if (strNum[i] == '7') {
          wordList[wordAmount] = "сiмнадцять";
        } else if (strNum[i] == '8') {
          wordList[wordAmount] = "вiсiмнадцять";
        } else if (strNum[i] == '9') {
          wordList[wordAmount] = "дев'ятнадцять";
        }
        i--;
        wordAmount++;
      } else {  // Units.
        if (strNum[i] != '0') {
          if (strNum[i] == '1') {
            if (strNumLen - 1 - i == 3) {  // Is "одна тисячi" check.
              wordList[wordAmount] = "одна";
            } else {
              wordList[wordAmount] = "один";
            }
          } else if (strNum[i] == '2') {
            if (strNumLen - 1 - i == 3) {  // Is "двi тисячi" check.
              wordList[wordAmount] = "двi";
            } else {
              wordList[wordAmount] = "два";
            }
          } else if (strNum[i] == '3') {
            wordList[wordAmount] = "три";
          } else if (strNum[i] == '4') {
            wordList[wordAmount] = "чотири";
          } else if (strNum[i] == '5') {
            wordList[wordAmount] = "п'ять";
          } else if (strNum[i] == '6') {
            wordList[wordAmount] = "шiсть";
          } else if (strNum[i] == '7') {
            wordList[wordAmount] = "сiм";
          } else if (strNum[i] == '8') {
            wordList[wordAmount] = "вiсiм";
          } else if (strNum[i] == '9') {
            wordList[wordAmount] = "дев'ять";
          }
          wordAmount++;
        }
      }
    } else if (digitCounter == 2) {  // Tens.
      if (strNum[i] != '0') {
        if (strNum[i] == '2') {
          wordList[wordAmount] = "двадцять";
        } else if (strNum[i] == '3') {
          wordList[wordAmount] = "тридцять";
        } else if (strNum[i] == '4') {
          wordList[wordAmount] = "сорок";
        } else if (strNum[i] == '5') {
          wordList[wordAmount] = "п'ятдесят";
        } else if (strNum[i] == '6') {
          wordList[wordAmount] = "шiстдесят";
        } else if (strNum[i] == '7') {
          wordList[wordAmount] = "сiмдесят";
        } else if (strNum[i] == '8') {
          wordList[wordAmount] = "вiсiмдесят";
        } else if (strNum[i] == '9') {
          wordList[wordAmount] = "дев'яносто";
        }
        wordAmount++;
      }
    } else if (digitCounter == 3) {  // Hundreds.
      if (strNum[i] != '0') {
        if (strNum[i] == '1') {
          wordList[wordAmount] = "сто";
        } else if (strNum[i] == '2') {
          wordList[wordAmount] = "двiстi";
        } else if (strNum[i] == '3') {
          wordList[wordAmount] = "триста";
        } else if (strNum[i] == '4') {
          wordList[wordAmount] = "чотириста";
        } else if (strNum[i] == '5') {
          wordList[wordAmount] = "п'ятсот";
        } else if (strNum[i] == '6') {
          wordList[wordAmount] = "шiстсот";
        } else if (strNum[i] == '7') {
          wordList[wordAmount] = "сiмсот";
        } else if (strNum[i] == '8') {
          wordList[wordAmount] = "вiсiмсот";
        } else if (strNum[i] == '9') {
          wordList[wordAmount] = "дев'ятсот";
        }
        wordAmount++;
      }

      if (i - 1 >= 0) {  // Thousands.
        if (thousandCounter == 1) {
          if (strNum[i - 1] == '1' &&
              !(i - 2 >= 0 &&
                strNum[i - 2] == '1')) {  // Prev. number == 1 and != 11
            wordList[wordAmount] = "тисяча";
          } else if (strNum[i - 1] >= '2' && strNum[i - 1] <= '4') {
            wordList[wordAmount] = "тисячi";
          } else {
            wordList[wordAmount] = "тисяч";
          }
        } else if (thousandCounter == 2) {
          if (strNum[i - 1] == '1') {
            wordList[wordAmount] = "мiльйон";
          } else if (strNum[i - 1] >= '2' && strNum[i - 1] <= '4') {
            wordList[wordAmount] = "мiльйони";
          } else {
            wordList[wordAmount] = "мiльйонiв";
          }
        } else if (thousandCounter == 3) {
          if (strNum[i - 1] == '1') {
            wordList[wordAmount] = "мiльярд";
          } else if (strNum[i - 1] >= '2' && strNum[i - 1] <= '4') {
            wordList[wordAmount] = "мiльярди";
          } else {
            wordList[wordAmount] = "мiльярдiв";
          }
        }
        thousandCounter++;
        wordAmount++;
      }

      digitCounter = 0;  // New digits cycle.
    }
    digitCounter++;
  }

  if (_Num < 0) {  // Negative check.
    wordList[wordAmount] = "мiнус";
    wordAmount++;
  }

  // "wordList" array join to "result" by " ".
  char* result;
  int allWordsLen = 0;
  for (int i = 0; i < wordAmount; i++) {
    allWordsLen += strlen(wordList[i]);
  }
  int resultLen = (allWordsLen + 1) + (wordAmount - 1);
  result = calloc(resultLen, sizeof(char));
  if (result == NULL) {
    return NULL;
  }

  for (int i = wordAmount - 1; i >= 0; i--) {
    strcat_s(result, resultLen, wordList[i]);
    if (i != 0) {
      strcat_s(result, resultLen, " ");
    }
  }

  free(strNum);
  free(wordList);
  return result;
}