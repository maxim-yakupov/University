package yakupov;

public class Tokeniser {
    private StringBuilder in;
    private int pos;
    private int ind;
    private enum States {BEG_MANT, ONE_DIG_MANT, DOT_OR_E, ONE_DIG_AFTER_DOT, ANY_DIG_MANT, BEG_EXP, ONE_DIG_EXP, ANY_DIG_EXP}

    Tokeniser(String str) {
        in = new StringBuilder(str);
        pos = 0;
    }
    public void append(String str) {
        in.append(str);
    }
    public void clear() {
        in.delete(0, in.length());
        pos = 0;
    }
    private boolean isE(char ch) {
        return ch == 'e' || ch == 'E';
    }
    private boolean isEnd(char ch) {
        return !(isDot(ch) || isDigit(ch) || isSign(ch) || isE(ch));
    }
    private boolean isDot(char ch) {
        return ch == '.' || ch == ',';
    }
    private boolean isSign() {
        return in.charAt(pos) == '-' || in.charAt(pos) == '+';
    }
    private boolean isSign(char ch) {
        return ch == '-' || ch == '+';
    }
    private boolean isDigit() {
        return in.charAt(pos) >= '0' && in.charAt(pos) <= '9';
    }
    private boolean isDigit(char ch) {
        return ch >= '0' && ch <= '9';
    }
    public char read() {
        pos++;
        return in.charAt(pos - 1);
    }
    public void pushBack() {
        pos--;
    }
    public boolean isNextDouble() {
        if (pos == in.length()) return false;
        int ind = pos;
        boolean dot = false;
        States state = States.BEG_MANT;
        while (true)
        {
            switch (state)
            {
                case BEG_MANT://beginning of mantisa
                    if (isSign(in.charAt(ind)))
                    {
                        state = States.ONE_DIG_MANT;
                        ind++;
                    }
                    else if (isDigit(in.charAt(ind)))
                    {
                        state = States.ANY_DIG_MANT;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_SYMBOL_ERROR!!!\n");
                        return false;
                    }
                    break;
                case ONE_DIG_MANT://one digit
                    if (isDigit(in.charAt(ind)))
                    {
                        state = States.ANY_DIG_MANT;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_DIGIT_ERROR!!!\n");
                        return false;
                    }
                    break;
                case DOT_OR_E://dot or exp
                    if (isDot(in.charAt(ind)))
                    {
                        if (dot) {
                            return true;
                        } else {
                            dot = true;
                        }
                        state = States.ONE_DIG_AFTER_DOT;
                        ind++;
                    }
                    else if (isE(in.charAt(ind)))
                    {
                        state = States.BEG_EXP;
                        ind++;
                    }
                    else if (isEnd(in.charAt(ind)))
                    {
                        return true;
                    }
                    else
                    {
//                        System.err.println("\n!!!DIVIDING_ERROR!!!\n(mantisa's integral part consists with only one digit with following dot or exp symbols)\n");
                        return false;
                    }
                    break;
                case ONE_DIG_AFTER_DOT://special for 'n.'
                    if (isDigit(in.charAt(ind)))
                    {
                        state = States.ANY_DIG_MANT;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_DIGIT_AFTER_DOT_ERROR!!!\n");
                        return false;
                    }
                    break;
                case ANY_DIG_MANT://any digits
                    if (isDigit(in.charAt(ind)))
                    {
                        ind++;
                    }
                    else if (isDot(in.charAt(ind)))
                    {
                        state = States.DOT_OR_E;
                    }
                    else if (isEnd(in.charAt(ind)))
                    {
                        return true;
                    }
                    else if (isE(in.charAt(ind)))
                    {
                        state = States.BEG_EXP;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_LAST_DIGITS_ERROR!!!\n");
                        return false;
                    }
                    break;
                case BEG_EXP://exponent
                    if (isSign(in.charAt(ind)))
                    {
                        state = States.ONE_DIG_EXP;
                        ind++;
                    }
                    else if (isDigit(in.charAt(ind)))
                    {
                        state = States.ANY_DIG_EXP;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_FIRST_SYMBOL_ERROR!!!\n");
                        return false;
                    }
                    break;
                case ONE_DIG_EXP://one digit
                    if (isDigit(in.charAt(ind)))
                    {
                        state = States.ANY_DIG_EXP;
                        ind++;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_FIRST_DIGIT_ERROR!!!\n");
                        return false;
                    }
                    break;
                case ANY_DIG_EXP://any digits
                    if (isDigit(in.charAt(ind)))
                    {
                        ind++;
                    }
                    else if (isEnd(in.charAt(ind)))
                    {
                        return true;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_LAST_DIGITS_ERROR!!!\n");
                        return false;
                    }
                    break;
                default://strange situation
//                    System.err.println("\n!!!STRANGE_ERROR!!!\n");
                    break;
            }
        }
    }

    public boolean hasNextDouble() {
        int c = 0;
        while (!isNextDouble() && pos < in.length()) {
            read();
            c++;
        }
        boolean has = isNextDouble();
        while (c != 0) {
            pushBack();
            c--;
        }
        return has;
    }

    public double nextDouble() {
        while (!isNextDouble()) read();
        double res = 0.0;
        double sign = 1;
        double mult = 10.0;
        boolean dot = false;
        States state = States.BEG_MANT;
        while (true)
        {
            switch (state)
            {
                case BEG_MANT://beginning of mantisa
                    if (isSign(in.charAt(pos)))
                    {
                        if (in.charAt(pos) == '-') sign *= -1;
                        state = States.ONE_DIG_MANT;
                        pos++;
                    }
                    else if (isDigit(in.charAt(pos)))
                    {
                        res += (double) in.charAt(pos) - (double) '0';
                        state = States.ANY_DIG_MANT;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_SYMBOL_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case ONE_DIG_MANT://one digit
                    if (isDigit(in.charAt(pos)))
                    {
                        res += (double) in.charAt(pos) - (double) '0';
                        state = States.ANY_DIG_MANT;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_DIGIT_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case DOT_OR_E://dot or exp
                    if (isDot(in.charAt(pos)))
                    {
                        if (dot) {
                            return sign * res;
                        }
                        dot = true;
                        mult = 0.1;
                        state = States.ONE_DIG_AFTER_DOT;
                        pos++;
                    }
                    else if (isE(in.charAt(pos)))
                    {
                        state = States.BEG_EXP;
                        pos++;
                    }
                    else if (isEnd(in.charAt(pos)))
                    {
                        return sign * res;
                    }
                    else
                    {
//                        System.err.println("\n!!!DIVIDING_ERROR!!!\n(mantisa's integral part consists with only one digit with following dot or exp symbols)\n");
                        return sign * res;
                    }
                    break;
                case ONE_DIG_AFTER_DOT://special for 'n.'
                    if (isDigit(in.charAt(pos)))
                    {
                        res += ((double) in.charAt(pos) - (double) '0') * mult;
                        mult *= 0.1;
                        state = States.ANY_DIG_MANT;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_FIRST_DIGIT_AFTER_DOT_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case ANY_DIG_MANT://any digits
                    if (isDigit(in.charAt(pos)))
                    {
                        if (dot) {
                            res += mult * ((double) in.charAt(pos) - (double) '0');
                            mult *= 0.1;
                        } else {
                            res *= 10;
                            res += ((double) in.charAt(pos) - (double) '0');
                        }
                        pos++;
                    }
                    else if (isDot(in.charAt(pos)))
                    {
                        state = States.DOT_OR_E;
                    }
                    else if (isEnd(in.charAt(pos)))
                    {
                        return sign * res;
                    }
                    else if (isE(in.charAt(pos)))
                    {
                        state = States.BEG_EXP;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!MANT_LAST_DIGITS_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case BEG_EXP://exponent
                    if (isSign(in.charAt(pos)))
                    {
                        state = States.ONE_DIG_EXP;
                        pos++;
                    }
                    else if (isDigit(in.charAt(pos)))
                    {
                        state = States.ANY_DIG_EXP;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_FIRST_SYMBOL_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case ONE_DIG_EXP://one digit
                    if (isDigit(in.charAt(pos)))
                    {
                        state = States.ANY_DIG_EXP;
                        pos++;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_FIRST_DIGIT_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                case ANY_DIG_EXP://any digits
                    if (isDigit(in.charAt(pos)))
                    {
                        pos++;
                    }
                    else if (isEnd(in.charAt(pos)))
                    {
                        return sign * res;
                    }
                    else
                    {
//                        System.err.println("\n!!!EXP_LAST_DIGITS_ERROR!!!\n");
                        return sign * res;
                    }
                    break;
                default://strange situation
//                    System.err.println("\n!!!STRANGE_ERROR!!!\n");
                    break;
            }
        }
    }
}
