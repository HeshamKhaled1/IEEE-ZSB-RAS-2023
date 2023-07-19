bool isNumber(char *s) {
    bool is_number = false, is_rise_to = false, is_sign = false, is_dot = false;

    for (int i = 0; i < strlen(s); i++) {
        char arr = s[i];

        /* is number */
        if (arr >= '0' && arr <= '9') {
            is_number = true;
        /* check for is_rise_to_ten */
        }
        else if (arr == 'e' || arr == 'E') {
            if (is_rise_to || !is_number ) {
                return false;
            } 
            else {
                is_rise_to = true, is_sign = false, is_number = false, is_dot = false;
            }
        /* check for sign */    
        } 
        else if (arr == '+' || arr == '-') {
            if (is_sign || is_number || is_dot) {
                return false;
            } else {
                is_sign = true;
            }
        }
        /* check for dot */
        else if (arr == '.') {
            if (is_dot || is_rise_to) {
                return false;
            }
             else {
                is_dot = true;
            }
        /* something else */ 
        } 
        else {
            return false;
        }
    }

    return is_number;    
}