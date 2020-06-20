

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

/**
 *
 * @author Mustafa Özsakallı @digitoygames
 */
public class Json {

    public static Object decode(String raw) {
        return new JsonParser(raw).parse();
    }
	
    private static class JsonParser {

        int pos;
        String raw;

        public JsonParser(String raw) {
            this.raw = raw;
        }

        public Object parse() {
            while (pos < raw.length()) {
                char c = raw.charAt(pos++);
                if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
                    continue;
                }
                switch (c) {
                    case '{':
                        Map object = new HashMap();
                        String field = null;
                        while (pos < raw.length()) {
                            c = raw.charAt(pos++);
                            if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
                                continue;
                            }
                            switch (c) {
                                case '}':
                                    return object;

                                case '"':
                                    field = parseString();
                                    break;

                                case ':':
                                    if (field != null) {
                                        object.put(field, parse());
                                        field = null;
                                    }
                                    break;

                                case ',':
                                    break;

                                default:
                                    return null;
                            }
                        }
                        return object;

                    case '[':
                        List list = new ArrayList();
                        while (pos < raw.length()) {
                            c = raw.charAt(pos++);
                            if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
                                continue;
                            }

                            switch (c) {
                                case ']':
                                    return list;
                                case ',':
                                    break;
                                default:
                                    pos--;
                                    list.add(parse());
                            }

                        }
                        return list;

                    case 't':
                        if (test("rue")) {
                            pos += 3;
                            return true;
                        }
                        break;

                    case 'f':
                        if (test("alse")) {
                            pos += 4;
                            return false;
                        }
                        break;

                    case 'n':
                        if (test("ull")) {
                            pos += 3;
                            return null;
                        }
                        break;

                    case '"':
                        return parseString();

                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '-':
                        pos--;
                        return parseNumber();
                        
                    default:
                        throw new RuntimeException("Invalid json "+pos);
                }
            }
            return null;
        }

        private boolean test(String check) {
            int len = raw.length();
            int p = pos;
            for (int i = 0; i < check.length(); i++) {
                if (p >= len || raw.charAt(p) != check.charAt(i)) {
                    return false;
                }
                p++;
            }
            return true;
        }

        private String parseString() {
            StringBuilder buf = new StringBuilder();
            while (pos < raw.length()) {
                char c = raw.charAt(pos++);
                if (c == '"') {
                    break;
                }
                switch (c) {
                    case '\\':
                        if (pos < raw.length()) {
                            c = raw.charAt(pos++);
                            switch (c) {
                                case 'r':
                                    buf.append('\r');
                                    break;
                                case 'n':
                                    buf.append('\n');
                                    break;
                                case 't':
                                    buf.append('\t');
                                    break;
                                case 'b':
                                    buf.append((char) 8);
                                    break;
                                case 'f':
                                    buf.append((char) 12);
                                    break;
                                case '/':
                                case '\\':
                                case '"':
                                    buf.append(c);
                                    break;
                                case 'u':
                                    char code = (char)Integer.parseInt("0x"+raw.substring(pos, pos+4));
                                    buf.append(code);
                                    pos += 4;
                                    break;

                            }
                        } else {
                            return buf.toString();
                        }
                        break;
                        
                    default:
                        buf.append(c);
                }
            }
            return buf.toString();
        }

        private Object parseNumber() {
            int start = pos;
            while(pos < raw.length()) {
                char c = raw.charAt(pos++);
                if(!((c>='0' && c<='9') || c=='.' || c=='E' || c=='e' || c=='-' || c=='+')) break;
            }
            pos--;
            double d = 0;
            String sub = raw.substring(start,pos);
            try {
                d = Double.parseDouble(sub);
            }catch(Exception e){
                throw new RuntimeException("Invalid number at "+start+ " -> "+sub);
            }
            int i = (int)d;
            if(i==d) return i; else return d;
        }

    }

    public static String encode(Object raw) {
        if (raw == null) {
            return "null";
        }
        StringBuilder buffer = new StringBuilder();
        internalEncode(raw, buffer);
        return buffer.toString();
    }

    private static void quote(String str, StringBuilder out) {
        out.append('"');
        for (int i = 0; i < str.length(); i++) {
            char c = str.charAt(i);
            switch (c) {
                case '"':
                    out.append("\\\"");
                    break;
                case '\\':
                    out.append("\\\\");
                    break;
                case '\n':
                    out.append("\\n");
                    break;
                case '\r':
                    out.append("\\r");
                    break;
                case '\t':
                    out.append("\\t");
                    break;
                default:
                    out.append(c);
            }
        }
        out.append('"');
    }

    private static void internalEncode(Object raw, StringBuilder buffer) {
        if (raw == null) {
            buffer.append("null");
            return;
        }

        if (raw instanceof Map) {
            buffer.append('{');
            Map map = (Map) raw;
            Iterator<Map.Entry> it = map.entrySet().iterator();
            int count = 0;
            while (it.hasNext()) {
                if (count++ > 0) {
                    buffer.append(',');
                }
                Map.Entry e = it.next();
                quote(e.getKey().toString(), buffer);
                buffer.append(':');
                internalEncode(e.getValue(), buffer);
            }
            buffer.append('}');
        } else if (raw instanceof List) {
            List list = (List) raw;
            buffer.append('[');
            for (int i = 0; i < list.size(); i++) {
                if (i > 0) {
                    buffer.append(',');
                }
                internalEncode(list.get(i), buffer);
            }
            buffer.append(']');
        } else if (raw instanceof String) {
            quote(raw.toString(), buffer);
        } else {
            buffer.append(raw);
        }

    }
}
