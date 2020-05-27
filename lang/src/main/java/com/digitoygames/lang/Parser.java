package com.digitoygames.lang;

import com.digitoygames.lang.model.*;

import java.io.File;
import java.util.*;

public class Parser {

    File file;
    int ptr;
    Tokenizer tokenizer;
    List<Token> tokens;
    Module module = new Module();

    public Parser(File file) {
        this.file = file;
    }
    public Module parse() throws Exception {
        tokenizer = new Tokenizer(file);
        tokens = tokenizer.tokens;
        using();
        while(ptr < tokens.size()) {
            if(!namespace()) throw error("namespace expected");
        }
        return module;
    }

    RuntimeException error(String msg) {
        Token t = tokens.get(ptr);
        return new RuntimeException(msg+" at "+file.getName()+"@"+t.line);
    }
    void skip(int count) {
        ptr += count;
    }
    String skip() {
        return tokens.get(ptr++).value;
    }
    boolean is(String value, int next) {
        return ptr+next < tokens.size() && tokens.get(ptr+next).value.equals(value);
    }
    boolean is(String value) {
        return is(value,0);
    }
    String is(String[] value) {
        for(String v : value)
            if(is(v)) return v;
        return null;
    }
    int line() {
        return tokens.get(ptr).line;
    }
    String expect(String value) {
        String msg = value+" expected";
        if(ptr < tokens.size()) msg += " found "+tokens.get(ptr).value;
        if(!is(value)) {
            throw error(msg);
        }
        ptr++;
        return value;
    }
    String ident() {
        return ident(false);
    }

    String ident(boolean allowPrim) {
        String s = tokens.get(ptr).value;
        if((!allowPrim && isPrim()) || isReserved())
            throw error("Unexpected "+s);
        Token t = tokens.get(ptr++);
        if(t.type == Token.IDENT) return t.value;
        ptr--;
        throw error("Ident expected");
    }
    String qualified() {
        String str = ident(true);
        while(is(".")) {
            str += ".";
            skip();
            str += ident();
        }
        return str;
    }

    void using() {
        while(is("using")) {
            skip();
            Using u = new Using();
            String n = null;
            u.qualified = qualified();
            if(is("=")) {
                //using S = System
                skip();
                u.name = u.qualified;
                u.qualified = qualified();
            }
            expect(";");
            module.usings.add(u);
        }
    }

    boolean namespace() {
        if(!is("namespace")) return false;
        Namespace n = new Namespace();
        skip();
        n.name = qualified();
        module.namespaces.add(n);
        expect("{");
        while(!is("}")) {
            if(!_class()) throw error("class expected");
        }
        expect("}");
        skip();
        return true;
    }

    Set<String> modifiers(String[] modifiers) {
        Set<String> set = new HashSet();
        while(true) {
            String mod = is(modifiers);
            if(mod == null) break;
            if(set.contains(mod)) throw error("Duplicate modifier "+mod);
            set.add(mod);
            skip();
        }
        return set;
    }

    Type type() {
        Type t = new Type();
        t.line = line();
        t.name = qualified();
        if(is("<")) {
            skip();
            while(true) {
                t.generic.add(type());
                if(is(">")) {
                    skip();
                    break;
                }
                if(is(",")) skip();
                else throw error(", or > expected");
            }
        }
        return t;
    }

    static String[] classModifiers = {"public","static","internal", "unsafe"};
    Set<String> classModifiers() { return modifiers(classModifiers); }
    static String[] fieldModifiers = {"public","static","internal","const","virtual"};
    Set<String> fieldModifiers() { return modifiers(fieldModifiers); }
    static String[] propertyModifiers = {"internal","private"};
    Set<String> propertyModifiers() { return modifiers(propertyModifiers); }
    static String[] methodModifiers = {"public","static","internal", "unsafe","virtual"};
    Set<String> methodModifiers() { return modifiers(methodModifiers); }

    boolean _class() {
        int saved = ptr;
        Set<String> modifiers = classModifiers();
        if(is("class")) {
            ClassSyntax cls = new ClassSyntax();
            cls.modifiers = modifiers;
            cls.line = line();
            skip();
            cls.type = type();
            module.namespaces.get(module.namespaces.size()-1).classes.add(cls);

            expect("{");
            while (!is("}")) {
                if(method(cls)) continue;
                if(field(cls)) continue;
                else {
                    fieldModifiers();
                    methodModifiers();
                    throw error("Invalid field or method definition. Unexpected "+tokens.get(ptr).value);
                }
            }
            return true;
        }
        ptr = saved;
        return false;
    }

    Expression fieldArgValue() {
        ptr--;
        Expression expr = statement();
        if(expr instanceof AssignSyntax) {
            AssignSyntax a = (AssignSyntax)expr;
            return a.right;
        } else throw error("Invalid");
    }

    boolean field(ClassSyntax cls) {
        int saved = ptr;
        Set<String> modifiers = fieldModifiers();
        Type type = type();
        String name = ident();

        if(is("=") || is(";") || is("{")) {
            FieldSyntax field = new FieldSyntax();
            field.type = type;
            field.name = name;
            field.modifiers = modifiers;

            //this is a field with value
            if (is("=")) {
                field.value = fieldArgValue();
            } else if(is("{")) {
                skip();
                while(!is("}")) {
                    propertyModifiers();
                    String prop = skip();
                    if(prop.equals("get") || prop.equals("set")) {
                        if(prop.equals("get") && field.getter != null) throw error("get already defined");
                        if(prop.equals("set") && field.setter != null) throw error("set already defined");

                        Expression exp = null;
                        if(is("{") || is("=>") || is(";"))
                            exp = statement();
                        else throw error("Expected { or => or ;");
                        if(prop.equals("get")) field.getter = exp; else field.setter = exp;
                    } else throw error("Unexpected "+prop);
                }
                expect("}");

                if(is("=")) {
                    skip();
                    field.value = expression();
                    expect(";");
                }
            } else skip(); //;

            cls.units.add(field);
            return true;
        }
        ptr = saved;
        return false;
    }

    boolean method(ClassSyntax cls) {
        int saved = ptr;
        Set<String> modifiers = methodModifiers();
        boolean isConstructor = false;
        Type type = null;
        if(is(cls.type.toString()) && is("(",1)) {
            //constructor
            isConstructor = true;
        }
        else type = type();
        Type name = type();

        if(is("(")) {
            MethodSyntax method = new MethodSyntax();
            method.type = type;
            method.name = name;
            method.modifiers = modifiers;
            method.isConstructor = isConstructor;

            skip();
            while (!is(")")) {
                ArgSyntax arg = new ArgSyntax();
                if(is("ref")) {
                    arg.isRef = true;
                    skip();
                }
                arg.type = type();
                arg.name = ident();
                if(is("=")) {
                    skip();
                    arg.value = expression();
                }
                method.args.add(arg);
                if(is(",")) {
                    skip();
                    continue;
                }
                if(is(")")) break;
                throw error("Expected , or )");
            }
            expect(")");

            if(is("where")) {
                skip();
                while (true) {
                    Type generic = type();
                    expect(":");
                    Type constraint = type();
                    Type target = method.name.generic.stream().filter(g -> g.toString().equals(generic.toString())).findFirst().orElse(null);
                    if(target == null) throw error("Constraint type not found "+generic);
                    target.constraint = constraint;
                    if(!is(",")) break;
                    skip();
                }
            }

            if(is("{") || is("=>") || is(";")) {
                method.body = statement();
            } else throw error("Expected { or => or ;");
            cls.units.add(method);

            return true;
        }
        ptr = saved;
        return false;
    }

    Expression statement() {
        if(is(";")) {
            skip();
            return new EmptySyntax();
        }

        if(is("=>")) {
            skip();
            ClosureSyntax c = new ClosureSyntax();
            c.body = statement();
            return c;
        }
        Expression stmt = block();
        if(stmt != null) return stmt;

        stmt = _if();
        if(stmt != null) return stmt;

        if(is("while")) {
            skip();
            expect("(");
            WhileSyntax w = new WhileSyntax();
            w.condition = expression();
            expect(")");
            w.body = statement();
            return w;
        }

        stmt = _switch();
        if(stmt != null) return stmt;

        stmt = var();
        if(stmt != null) return stmt;

        stmt = _for();
        if(stmt != null) return stmt;

        //local definition with type
        if(tokens.get(ptr).isIdent() && tokens.get(ptr+1).isIdent() && !isReserved()) {
            return localDef();
        }
        stmt = expression();
        if(stmt != null) expect(";");
        return stmt;
    }

    Expression block() {
        if(is("{")) {
            BlockSyntax b = new BlockSyntax();
            skip();
            while(!is("}")) {
                if(b.statements.size() > 100)
                    System.out.println("ccc");
                b.statements.add(statement());
            }
            expect("}");
            return b;
        }
        return null;
    }

    Expression var() {
        if(is("var")) {
            skip();
            LocalSyntax def = new LocalSyntax();
            while(true) {
                Local l = new Local();
                def.locals.add(l);
                l.name = ident();
                if(is("=")) {
                    skip();
                    l.value = expression();
                }
                if(is(",")) {
                    skip();
                    continue;
                }
                if(is(";")) break;
                throw error("Expected , or ;");
            }
            expect(";");
            return def;
        }
        return null;
    }

    Expression localDef() {
        Type type = type();
        LocalSyntax def = new LocalSyntax();
        while(true) {
            Local l = new Local();
            def.locals.add(l);
            l.name = ident();
            l.type = type;
            if(is("=")) {
                skip();
                l.value = expression();
            }
            if(is(",")) {
                skip();
                continue;
            }
            if(is(";")) break;
            throw error("Expected , or ;");
        }
        expect(";");
        return def;
    }

    Expression _if() {
        if(line() == 1403)
            System.out.println();
        if(is("if")) {
            skip();
            expect("(");
            IfSyntax i = new IfSyntax();
            i.condition = expression();
            expect(")");
            i.body = statement();
            if(is("else")) {
                skip();
                i.elseBody = statement();
            }
            return i;
        }
        return null;
    }

    Expression _switch() {
        if(is("switch")) {
            skip();
            SwitchSyntax s = new SwitchSyntax();
            expect("(");
            s.condition = expression();
            expect(")");
            expect("{");
            while (!is("}")) {
                SwitchSyntax.Case c = new SwitchSyntax.Case();
                if(is("case")) {
                    skip();
                    c.value = expression();
                } else if(is("default")) {
                    skip();
                } else error("Unexpected "+tokens.get(ptr).value);
                expect(":");
                while(true) {
                    Expression stmt = statement();
                    c.body.add(stmt);
                    if(stmt instanceof BreakSyntax) break;
                }
            }
            expect("}");
            return s;
        }

        return null;
    }

    Expression _for() {
        if(is("for")) {
            skip();
            expect("(");
            ForSyntax f = new ForSyntax();
            f.initializer = statement();
            f.condition = statement();
            if(!is(")")) f.step = expression();
            expect(")");
            f.body = statement();
            return f;
        }
        return null;
    }

    Expression expression() {
        if(is("break")) {
            BreakSyntax b = new BreakSyntax();
            skip();
            if(!is(";") && tokens.get(ptr).isIdent() && !isReserved() && !isPrim()) {
                b.label = tokens.get(ptr++).value;
            }
            return b;
        }

        if(is("return")) {
            skip();
            ReturnSyntax r = new ReturnSyntax();
            if(!is(";")) r.value = expression();
            return r;
        }

        return assign();
    }

    Expression assign() {
        Expression left = ternary();
        if(left == null) return null;
        while(true) {
            if(is("=") || is("|=") || is("+=") || is("-=") || is("*=") || is("/=") || is("&=") || is("%=")) {
                AssignSyntax a = new AssignSyntax();
                a.line = line();
                a.operator = skip();
                a.left = left;
                a.right = expression();
                left = a;
            } else break;
        }
        return left;
    }

    Expression ternary() {
        Expression left = or();
        if(left == null) return null;
        while(true) {
            if(is("?")) {
                TernarySyntax t = new TernarySyntax();
                t.line = line();
                t.condition = left;
                skip();
                t.trueValue = expression();
                expect(":");
                t.falseValue = expression();
                left = t;
            } else break;;
        }
        return left;
    }

    Expression or() {
        Expression left = and();
        if(left == null) return null;
        while (true) {
            if(is("||")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = and();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression and() {
        Expression left = bitOr();
        if(left == null) return null;
        while (true) {
            if(is("&&")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = bitOr();
                left = bin;
            } else break;
        }
        return left;

    }


    Expression bitOr() {
        Expression left = bitAnd();
        if(left == null) return null;
        while (true) {
            if(is("|")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = bitAnd();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression bitAnd() {
        Expression left = eqNeq();
        if(left == null) return null;
        while (true) {
            if(is("&")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = eqNeq();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression eqNeq() {
        Expression left = gtLt();
        if(left == null) return null;
        while (true) {
            if(is("==") || is("!=")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = gtLt();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression gtLt() {
        Expression left = is();
        if(left == null) return null;
        while (true) {
            if(is(">") || is(">=") || is("<") || is("<=")) { //is here
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = is();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression is() {
        Expression left = as();
        if(left == null) return null;
        while(true) {
            if(is("is")) {
                IsSyntax is = new IsSyntax();
                skip();
                is.expression = left;
                is.type = type();
                if(!isReserved() && tokens.get(ptr).isIdent()) {
                    is.local = ident();
                }
                left = is;
            }
            break;
        }
        return left;
    }

    Expression as() {
        Expression left = shift();
        if(left == null) return null;
        while(true) {
            if(is("as")) {
                AsSyntax as = new AsSyntax();
                skip();
                as.expression = left;
                as.type = type();
                left = as;
            }
            break;
        }
        return left;
    }

    Expression shift() {
        Expression left = addSub();
        if(left == null) return null;
        while (true) {
            if(is("<<") || is(">>")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = addSub();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression addSub() {
        Expression left = mulDivMod();
        if(left == null) return null;
        while (true) {
            if(is("+") || is("-")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = mulDivMod();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression mulDivMod() {
        Expression left = array();
        if(left == null) return null;
        while (true) {
            if(is("*") || is("/") || is("%")) {
                BinarySyntax bin = new BinarySyntax();
                bin.left = left;
                bin.line = line();
                bin.operator = skip();
                bin.right = array();
                left = bin;
            } else break;
        }
        return left;
    }

    Expression array() {
        Expression left = _new();
        if(left == null) return null;
        while(true) {
            if(is("[")) {
                ArraySyntax arr = new ArraySyntax();
                arr.line = line();
                skip();
                arr.array = arr;
                left = arr;
                arr.index = expression();
                expect("]");
            } else break;
        }

        if(is("(")) { //call ??
            CallSyntax c = new CallSyntax();
            c.expression = left;
            c.args = args();
            left = c;
        }

        if(is(".")) {
            skip();
            MultiSyntax m = new MultiSyntax();
            m.left = left;
            m.right = array();
            left = m;
        }

        if(is("?.")) {
            skip();
            NullSafeSyntax n = new NullSafeSyntax();
            n.left = left;
            n.right = array();
            left = n;
        }

        if(is("++") || is("--")) {
            PostSyntax p = new PostSyntax();
            p.operator = skip();
            p.expression = left;
            left = p;
        }
        return left;
    }

    Expression _new() {
        if(is("new")) {
            NewSyntax n = new NewSyntax();
            n.line = line();
            skip();
            n.type = type();
            n.args = args();
            return n;
        }
        return identifier();
    }


    Expression identifier() {
        int saved = ptr;
        try {
            return type();
        } catch (Exception e) {}
        ptr = saved;
        if(tokens.get(ptr).type == Token.IDENT) {
            Ident id = new Ident();
            id.line = line();
            id.value = tokens.get(ptr++).value;
            return id;
        }
        return basic();
    }
    Expression basic() {
        if(is("(")) {
            skip();
            ParSyntax p = new ParSyntax();
            p.expression = expression();
            expect(")");

            //cast
            if(p.expression instanceof Type) {
                CheckCastSyntax c = new CheckCastSyntax();
                c.type = (Type)p.expression;
                c.expression = expression();
                return c;
            }
            return p;
        }

        if(is("~") || is("--") || is("++") || is("!") || is("-") || is("+")) {
            PreSyntax p = new PreSyntax();
            p.line = line();
            p.operator = skip();
            p.expression = expression();
            return p;
        }
        Ident id = new Ident();
        id.line = line();
        id.value = tokens.get(ptr++).value;
        return id;
        //return null;
    }


    List<Expression> args() {
        if(!is("(")) return Collections.emptyList();
        List<Expression> result = new ArrayList();
        skip();
        while(!is(")")) {
            result.add(expression());
            if(is(",")) {
                skip();
                continue;
            }
            if(!is(")")) throw error("Expected )");
            break;
        }
        expect(")");
        return result;
    }

    static String[] prims = {
        "void","string","object","int","float","double","long","byte","char","short"
    };
    boolean isPrim(String value) {
        for(String str : prims)
            if(str.equals(value)) return true;
        return false;
    }
    boolean isPrim() {
        return isPrim(tokens.get(ptr).value);
    }

    static String[] reserved = {
        "public","private","virtual","class","new","switch","internal","continue",
        "for","foreach","while","struct","unsafe","case","params","return","is","default","if","using","namespace"
    };
    boolean isReserved(String value) {
        for(String str : reserved)
            if(str.equals(value)) return true;
        return false;
    }
    boolean isReserved() {
        return isReserved(tokens.get(ptr).value);
    }
}
