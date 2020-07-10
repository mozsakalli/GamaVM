using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using dnlib.DotNet;
using dnlib.DotNet.Emit;

namespace csharp
{
    class Program
    {
        static List<string> _userStrings = new List<string>();

        public static void Main(string[] args)
        {
            var ctx = ModuleDef.CreateModuleContext();
            //var module = ModuleDefMD.Load("/Users/mustafa/Work/digitoygames/digiplay-net/OkeyExtra/iOS/bin/iPhone/Debug/OkeyExtra.exe", ctx);
            //var module = ModuleDefMD.Load("/Users/mustafa/Projects/csharp/bin/Debug/csharp.exe", ctx);
            var module = ModuleDefMD.Load("/Users/mustafa/Work/digitoygames/digiplay-net/GinRummyExtra/Android/bin/Debug/GinRummyExtra.dll", ctx);
            CorLibTypes corLibTypes = new CorLibTypes(module);
            CPP(module);
            return;
            var buffer = new StringBuilder();
            foreach (var type in module.GetTypes())
            {
                //if (!type.FullName.StartsWith("Test")) continue;
                
                buffer.Append("Type=" + type.FullName);
                if (type.GenericParameters != null)
                    foreach (var g in type.GenericParameters)
                    {
                        buffer.Append(" Gen=" + g.FullName);
                    }
                buffer.Append("\n");
                foreach(var f in type.Fields)
                {
                    buffer.Append("  field:" + f.Name + " " + f.FieldType + "\n");
                }
                Test(module, type, corLibTypes,  buffer);

                if(type.NestedTypes != null)
                {
                    foreach(var nt in type.NestedTypes)
                    {
                        buffer.Append("Type=" + nt.FullName + "\n");
                        foreach (var f in nt.Fields)
                        {
                            buffer.Append("  field:" + f.Name + " " + f.FieldType + "\n");
                        }
                        Test(module, nt, corLibTypes, buffer);

                    }
                }
            }
            System.IO.File.WriteAllText("il.txt", buffer.ToString());
        }

        static string Esc(string str) => str.Replace(':', '_').Replace(' ', '_').Replace('<', '_').Replace('>', '_')
            .Replace('.', '_').Replace('`', '_').Replace('/','_').Replace('(','_').Replace(')','_').Replace(',','_')
            .Replace('[','_').Replace(']','_');

        static void CPP(ModuleDef module)
        {
            var buf = new Writer();
            foreach (var type in module.GetTypes())
            {
                //if (!type.FullName.StartsWith("Test")) continue;
                Type(type, buf);
                if (type.NestedTypes != null)
                    foreach (var nt in type.NestedTypes)
                        Type(nt, buf);
            }

            foreach (var type in module.GetTypes())
            {
                //if (!type.FullName.StartsWith("Test")) continue;
                foreach (var m in type.Methods)
                {
                    Meth(module, m, buf);
                }
            }

            System.IO.File.WriteAllText("il.txt", buf.buffer.ToString());
        }

        static void Type(TypeDef type, Writer buf)
        {
            var list = new List<FieldDef>();
            var t = type;
            while (t != null)
            {
                foreach (var f in t.Fields)
                    list.Insert(0, f);
                t = t.GetBaseType().ResolveTypeDef();
            }
            //buf.Format("typedef struct {0} ", Esc(type.FullName)).WriteLn("{").Indent();
            //buf.WriteLn("void* $class;");
            //foreach (var f in list)
            //{
            //    if (!f.IsStatic)
            //        buf.FormatLn("{0} {1};", f.FieldType.IsPrimitive ? CppType(f.FieldType) : "void*", Esc(f.FullName));
            //}
            //buf.Undent().Write("} ").FormatLn("{0};", Esc(type.FullName)).Ln();
        }

        static string CppType(TypeSig type)
        {
            if (type.IsPrimitive)
            {
                switch (type.FullName)
                {
                    case "System.Void": return "void";
                    case "System.Int32": return "csint32";
                    case "System.Int64": return "csint64";
                    case "System.Boolean": return "csbool";
                    case "System.Double": return "csdouble";
                    case "System.Single": return "csfloat";
                }
            }
            switch(type.FullName)
            {
                case "System.Void": return "void";
                default: return "o";
            }
        }
        static string StackType(TypeSig type)
        {
            if (type.IsPrimitive)
            {
                switch (type.FullName)
                {
                    case "System.Void": return "v";
                    case "System.Int32": return "i";
                    case "System.Int64": return "l";
                    case "System.Boolean": return "z";
                    case "System.Double": return "d";
                    case "System.Single": return "f";
                }
            }
            switch (type.FullName)
            {
                case "System.Void": return "void";
                default: return "void*";
            }
        }

        static void Meth(ModuleDef module, MethodDef method, Writer buf)
        {
            Console.WriteLine(method.FullName);
            //if (!method.FullName.Contains("TestMe")) return;
            buf.Format("{0} {1}(", CppType(method.ReturnType),
                Esc(method.FullName));
            for(var i=0; i<method.Parameters.Count; i++)
            {
                var p = method.Parameters[i];
                if (i > 0) buf.Write(",");
                buf.Format("{0} $arg{1}", CppType(p.Type), i);
            }
            buf.WriteLn("){").Indent();
            //if (method.FullName == "System.String digibo.Key::get_Value()")
            //    Console.WriteLine("..");
            if (method.HasBody)
            {
                /*buf.FormatLn("VAR ST[{0}];", method.Body.MaxStack);
                if(method.Body.HasVariables)
                {
                    buf.FormatLn("VAR LOC[{0}];", method.Body.Variables.Count);
                }
                buf.WriteLn("int SP = 0;");*/
                string[] stackTypes = new string[method.Body.MaxStack];
                int sp = 0;
                foreach (var ins in method.Body.Instructions)
                {
                    buf.Format("{0}: ",ins.Offset);
                    switch(ins.OpCode.Code)
                    {
                        case Code.Nop:
                            buf.Write("//nop");
                            break;

                        case Code.Ldc_I4_0:
                        case Code.Ldc_I4_1:
                            buf.Format("ST[SP++].i = {0};", (int)ins.OpCode.Code - (int)Code.Ldc_I4_0);
                            stackTypes[sp++] = "i";
                            break;
                        case Code.Ldc_I4:
                            buf.Format("ST[SP++].i = {0};", (int)ins.Operand);
                            stackTypes[sp++] = "i";
                            break;
                        case Code.Ldc_R8:
                            buf.Format("ST[SP++].d = {0};", (double)ins.Operand);
                            stackTypes[sp++] = "d";
                            break;
                        case Code.Ldloc_0:
                        case Code.Ldloc_1:
                        case Code.Ldloc_2:
                        case Code.Ldloc_3:
                            var type = StackType(method.Body.Variables[(int)ins.OpCode.Code - (int)Code.Ldloc_0].Type);
                            buf.Format("ST[SP++].{0} = LOC[{1}].{2};", type, (int)ins.OpCode.Code - (int)Code.Ldloc_0, type);
                            stackTypes[sp++] = type;
                            break;
                        case Code.Stloc_0:
                        case Code.Stloc_1:
                        case Code.Stloc_2:
                        case Code.Stloc_3:
                            type = stackTypes[--sp];
                            buf.Format("LOC[{0}].{1} = ST[--SP].{2};", (int)ins.OpCode.Code - (int)Code.Stloc_0, type, type);
                            break;
                        case Code.Br_S:
                            buf.Format("goto IL{0};", (ins.Operand as Instruction).Offset);
                            break;
                        case Code.Add:
                            buf.Format("ST[SP-2].{0} = ST[SP-1].{0} + ST[SP-2].{0}; SP--;", stackTypes[sp-1], stackTypes[sp - 1], stackTypes[sp - 1]);
                            sp--;
                            break;
                        case Code.Clt:
                            buf.Format("ST[SP-2].z = ST[SP-2].{0} < ST[SP-1].{1} ? 1 : 0; SP--;",stackTypes[sp-2],stackTypes[sp-1]);
                            stackTypes[sp - 2] = "z";
                            sp--;
                            break;
                        case Code.Brtrue_S:
                            buf.Format("SP--; if(ST[SP].z) goto IL{0};", (ins.Operand as Instruction).Offset);
                            sp--;
                            break;
                        case Code.Conv_R8:
                            buf.Format("ST[SP-1].d = (int)ST[SP-1].{0};", stackTypes[sp - 1]);
                            stackTypes[sp - 1] = "d";
                            break;
                        case Code.Conv_I4:
                            buf.Format("ST[SP-1].i = (int)ST[SP-1].{0};", stackTypes[sp - 1]);
                            stackTypes[sp - 1] = "i";
                            break;
                        case Code.Ret:
                            if (method.HasReturnType)
                                buf.Format("return ST[--SP].{0};", stackTypes[sp-1]);
                            else buf.Write("return;");
                            break;
                            
                        default:
                            throw new Exception("Unknown op:" + ins);
                    }
                    //buf.Write(" //" + ins);
                    buf.Ln();
                    //buf.WriteLn(ins);
                }
            }
            buf.Undent().WriteLn("}").Ln();
        }

        static void Test(ModuleDef module, TypeDef type, CorLibTypes cl, StringBuilder buffer)
        {
            foreach(var g in type.GenericParameters)
            {
                buffer.Append("Generic: " + g + "\n");
            }
            foreach(var m in type.Methods)
            {
                //if (!m.FullName.Contains("TestMe")) continue;
                buffer.Append(m.FullName + "\n");
                if(m.HasBody)
                {
                    foreach(var ins in m.Body.Instructions)
                    {
                        if (ins.OpCode.Code == dnlib.DotNet.Emit.Code.Newobj)
                        {
                            var member = (IMethod)ins.Operand;
                            var method = member.MethodSig;
                            var para = new List<(TypeSig destType, StackEntry src)>();
                            var parasCount = method.Params.Count;
                            //for (int i = parasCount - 1; i >= 0; i--)
                            //    para.Add((method.Params[i], Stack.Pop()));

                            para.Reverse();
                            var genSig = member.DeclaringType.TryGetGenericInstSig();

                        }
                        buffer.Append("   " + ins.OpCode.Code+" : "+ ins.ToString() + "\n");
                    }
                    /*
                    var mem = new MemoryStream();
                    TextWriter text = new StreamWriter(mem, Encoding.UTF8);
                    var importer = new ILImporter(cl, m, text, 2) { UserStrings = _userStrings, ModuleName = TypeUtils.EscapeModuleName(module.Assembly) };
                    importer.ImportNormalBlocks();
                    importer.ImportExceptionBlocks();
                    importer.Gencode();
                    Console.WriteLine(Encoding.UTF8.GetString(mem.ToArray()));*/
                }
            }
        }
    }

    internal static class Extensions
    {
        public static TextWriter Ident(this TextWriter writer, int ident)
        {
            for (int i = 0; i < ident; i++)
                writer.Write("    ");
            return writer;
        }
    }

}
