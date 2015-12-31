/**
 * Created by wbj on 12/30/15.
 */

public class Solution {
    public static class ReadS {
	public static class ReadInt {
	    boolean valid;
	    int val;
	    String rest;
	    ReadInt() {valid = false;}
	    ReadInt(int _val, String _rest) { valid = true; val = _val; rest = _rest;}
	}
	public static class ReadOp {
	    boolean valid;
	    char op;
	    String rest;
	    ReadOp() {valid = false;}
	    ReadOp(char _op, String _rest) {valid = true; op = _op; rest = _rest;}
	}
	private static boolean isDigit(char ch) {
	    if (ch >= '0' && ch <= '9') return true;
	    return false;
	}
	private static int fromDigit(char ch) {
	    assert(isDigit(ch));
	    return (int) (ch - '0');
	}
	private static String lexeme(String s) { /* remove leading spc */
	    int start = 0, len = s.length();
	    for (int i = 0; i < s.length(); i++) {
		if (s.charAt(i) == ' ' || s.charAt(i) == '\t') {
		    ++start;
		    --len;
		}
	    }
	    return s.substring(start);
	}
	public static ReadInt readInt (String s) {
	    String s1 = lexeme(s);
	    boolean valid = false;
	    int r = 0;
	    int len = s1.length();

	    if (len == 0) return new ReadInt();

	    for (int i = 0; i < s1.length(); ++i) {
		char ch = s1.charAt(i);
		if (!isDigit(ch)) {
		    if (!valid) return new ReadInt();
		    else return new ReadInt(r, s1.substring(i));
		}
		valid = true;
		r = 10*r + fromDigit(ch);
	    }

	    return new ReadInt(r, "");
	}
	public static ReadOp readOp(String s) {
	    String s1 = lexeme(s);
	    int len = s1.length();

	    if (len == 0) return new ReadOp();

	    char ch = s.charAt(0);
	    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') return new ReadOp(ch, s1.substring(1));
	    return new ReadOp();
	}
    }

    public static class Eval {
	public static class MaybeResult {
	    boolean valid;
	    int result;
	    MaybeResult() {valid = false;}
	    MaybeResult(int _result) {valid = true; result = _result;}
	}

	private static MaybeResult acc(int left, String s) {
	    ReadS.ReadOp op = ReadS.readOp(s);
	    if (!op.valid) return new MaybeResult(left);

	    if (op.op == '*' || op.op == '/' || op.op == '-') {
		ReadS.ReadInt right = ReadS.readInt(op.rest);
		if (!right.valid) return new MaybeResult();

		if (op.op == '-') {
		    MaybeResult res = acc(-right.val, right.rest);
		    if (!res.valid) return new MaybeResult();
		    return new MaybeResult(left + res.result);
		} else {
		    int rr = 0;
		    if (op.op == '*') rr = left * right.val;
		    else rr = left / right.val;

		    return acc(rr, right.rest);
		}
	    } else if (op.op == '+') {
		MaybeResult res = eval(op.rest);
		if (!res.valid) return new MaybeResult();
		return new MaybeResult(left + res.result);
	    } else {
		assert(true);
	    }
	    return new MaybeResult();
	}
	public static MaybeResult eval(String s) {
	    ReadS.ReadInt i1 = ReadS.readInt(s);
	    if (!i1.valid) return new MaybeResult();
	    return acc(i1.val, i1.rest);
	}
    }


    public int calculate(String s) {
        return Eval.eval(s).result;
    }
}
