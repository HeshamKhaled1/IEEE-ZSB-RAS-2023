char* multiply(char* num1, char* num2) {
    int lenNum1 = strlen(num1);
    int lenNum2 = strlen(num2);
    int lenResult = lenNum1 + lenNum2;

    char* result = (char*)malloc((lenResult + 1) * sizeof(char));
    memset(result, '0', lenResult * sizeof(char));
    result[lenResult] = '\0';

    for (int i = lenNum1 - 1; i >= 0; i--) {
        for (int j = lenNum2 - 1; j >= 0; j--) {
            int digitNum1 = num1[i] - '0';
            int digitNum2 = num2[j] - '0';
            int product = (result[i + j + 1] - '0') + (digitNum1 * digitNum2);

            result[i + j + 1] = (product % 10) + '0';
            result[i + j] += product / 10;
        }
    }

    int i = 0;
    while (result[i] == '0' && result[i + 1] != '\0') {
        i++;
    }

    memmove(result, result + i, (lenResult - i + 1) * sizeof(char));

    return result;
}